#include "Arduino.h"

#include <iostream>

#define GET 0x0
#define SET 0x1
#define MOTOR_PORT 0x2
#define MOTOR_SPEED 0x3
#define MOTOR_UPDATE 0x4
#define MOTOR_TACHO_0 0x5
// 6, 7, 8
#define SERVO_PORT 0x9
#define SERVO_POSITION 0xA
#define SERVO_UPDATE 0xB
#define BATTERY 0xC

Arduino::Arduino(RobotProtocol *iRobotProtocol)
    : mComPort("/dev/ttyUSB0", 115200, 8, 'N', 1)
    , mRobotProtocol(iRobotProtocol)
{
    printf("Opening port %s.\n", mComPort.GetPort().c_str());
	if (mComPort.Open() != 0)
    {
		std::cout << "Error opening Arduino Port" << std::endl;
	}
}

Arduino::~Arduino()
{
    mComPort.Close();
}

void Arduino::run()
{
    char wArduinoSensorValue[8] = {};

    set(MOTOR_PORT, 0);
    set(MOTOR_SPEED, (uint8_t)mRobotProtocol->getArduinoMotorSpeed()[0]);
    set(MOTOR_UPDATE, (uint8_t)1);
    
    uint8_t tacho[4] = {};
    get(tacho, MOTOR_TACHO_0, 4);
    wArduinoSensorValue[0] = tacho[3] & 0xFF;
    wArduinoSensorValue[1] = tacho[2] & 0xFF;
    wArduinoSensorValue[2] = tacho[1] & 0xFF;
    wArduinoSensorValue[3] = tacho[0] & 0xFF;

    set(MOTOR_PORT, 1);
    set(MOTOR_SPEED, (uint8_t)mRobotProtocol->getArduinoMotorSpeed()[1]);
    set(MOTOR_UPDATE, (uint8_t)1);

    get(tacho, MOTOR_TACHO_0, 4);
    wArduinoSensorValue[4] = tacho[3] & 0xFF;
    wArduinoSensorValue[5] = tacho[2] & 0xFF;
    wArduinoSensorValue[6] = tacho[1] & 0xFF;
    wArduinoSensorValue[7] = tacho[0] & 0xFF;


    set(SERVO_PORT, 0);
    set(SERVO_POSITION, (uint8_t)mRobotProtocol->getArduinoMotorSpeed()[2]);
    set(SERVO_UPDATE, (uint8_t)1);

    set(SERVO_PORT, 1);
    set(SERVO_POSITION, (uint8_t)mRobotProtocol->getArduinoMotorSpeed()[3]);
    set(SERVO_UPDATE, (uint8_t)1);

    set(SERVO_PORT, 2);
    set(SERVO_POSITION, (uint8_t)mRobotProtocol->getArduinoMotorSpeed()[4]);
    set(SERVO_UPDATE, (uint8_t)1);

    mRobotProtocol->setArduinoSensorValue((char*)wArduinoSensorValue, sizeof(wArduinoSensorValue));
    
}

void Arduino::set(uint8_t key, uint8_t value)
{
    uint8_t buffer[] = {SET, key, value};
    mComPort.Write((const char*)buffer, sizeof(buffer));
}

void Arduino::get(uint8_t* buffer, uint8_t key, uint8_t size)
{
    uint8_t writeBuffer[] = {GET, key};
    mComPort.Write((const char*)writeBuffer, sizeof(writeBuffer));
    bool successFlag;
    for (int i = 0; i < size ; i++)
    {
        buffer[i] = (uint8_t)mComPort.ReadChar(successFlag);
    }
}

void Arduino::stop()
{
}
