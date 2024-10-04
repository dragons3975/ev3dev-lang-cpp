#include "RobotProtocol.h"

#include <iostream>
#include <stdexcept>

RobotProtocol::RobotProtocol()
{
}

void RobotProtocol::decodeMotors(const char *buffer)
{
    if (buffer[0] != 15)
    {
        throw std::runtime_error("Expected size 15 (buffer size + ev3Motor size + 2*arduinoMotor size).");
    }

    for (int i = 0; i < 4; i++)
    {
        mEv3MotorSpeed[i] = buffer[i+1] & 0xFF;
    }
    for (int i = 0; i < 5; i++)
    {
        mArduinoMotorSpeed[i] = buffer[i+5] & 0xFF;
    }
    for (int i = 0; i < 5; i++)
    {
        mArduinoMotorMode[i] = buffer[i+10] & 0xFF;
    }
}

char* RobotProtocol::getEv3MotorSpeed()
{
    return mEv3MotorSpeed;
}

char* RobotProtocol::getArduinoMotorSpeed()
{
    return mArduinoMotorSpeed;
}

char* RobotProtocol::getArduinoMotorMode()
{
    return mArduinoMotorMode;
}

void RobotProtocol::encodeSensors(char *buffer)
{
    buffer[0] = 39; // buffer size + ev3Sensor size + arduinoSensor size
    for (int i = 0; i < 29; i++)
    {
        buffer[i+1] = mEv3SensorValue[i];
    }
    for (int i = 0; i < 9; i++)
    {
        buffer[i+30] = mArduinoSensorValue[i];
    }
}

void RobotProtocol::setEv3SensorValue(char *iEv3SensorValue, int size)
{
    if (size != sizeof(mEv3SensorValue))
    {
        throw std::runtime_error("setEv3SensorValue: wrong size");
    }
    for (int i = 0; i < size; i++)
    {
        mEv3SensorValue[i] = iEv3SensorValue[i];
    }
}

void RobotProtocol::setArduinoSensorValue(char *iArduinoSensorValue, int size)
{
    if (size != sizeof(mArduinoSensorValue))
    {
        throw std::runtime_error("setArduinoSensorValue: wrong size");
    }
    for (int i = 0; i < size; i++)
    {
        mArduinoSensorValue[i] = iArduinoSensorValue[i];
    }
}
