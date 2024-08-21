#include "Robot.h"

#include <iostream>

Robot::Robot(RobotProtocol *iRobotProtocol)
    : mRobotProtocol(iRobotProtocol)
    , mMotorA()
    , mMotorB()
    , mMotorC()
    , mMotorD()
    , mTouchSensor()
    , mColorSensor()
    , mUltrasonicSensor()
    , mGyroSensor()
{
}

void Robot::run()
{
    int wDutyCycle = 100 * ((mRobotProtocol->getEv3MotorSpeed()[0] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorA: " << wDutyCycle << std::endl;
    if (mMotorA.connected()) mMotorA.set_duty_cycle_sp(wDutyCycle).run_direct();

    wDutyCycle = 100 * ((mRobotProtocol->getEv3MotorSpeed()[1] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorB: " << wDutyCycle << std::endl;
    if (mMotorB.connected()) mMotorB.set_duty_cycle_sp(wDutyCycle).run_direct();

    wDutyCycle = 100 * ((mRobotProtocol->getEv3MotorSpeed()[2] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorC: " << wDutyCycle << std::endl;
    if (mMotorC.connected()) mMotorC.set_duty_cycle_sp(wDutyCycle).run_direct();
    
    wDutyCycle = 100 * ((mRobotProtocol->getEv3MotorSpeed()[3] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorD: " << wDutyCycle << std::endl;
    if (mMotorD.connected()) mMotorD.set_duty_cycle_sp(wDutyCycle).run_direct();
    
    char wEv3SensorValue[8] = {};
    wEv3SensorValue[0] = mMotorA.connected() ? mMotorA.position() & 0xFF : 0;
    wEv3SensorValue[1] = mMotorB.connected() ? mMotorB.position() & 0xFF : 0;
    wEv3SensorValue[2] = mMotorC.connected() ? mMotorC.position() & 0xFF : 0;
    wEv3SensorValue[3] = mMotorD.connected() ? mMotorD.position() & 0xFF : 0;
    wEv3SensorValue[4] = mTouchSensor.connected() ? mTouchSensor.is_pressed() & 0xFF : 0;
    wEv3SensorValue[5] = mColorSensor.connected() ? mColorSensor.color() & 0xFF : 0;
    wEv3SensorValue[6] = mUltrasonicSensor.connected() ? mUltrasonicSensor.distance_centimeters() & 0xFF : 0;
    wEv3SensorValue[7] = mGyroSensor.connected() ? mGyroSensor.angle() & 0xFF : 0;

    mRobotProtocol->setEv3SensorValue(wEv3SensorValue, sizeof(wEv3SensorValue));

    char wArduinoSensorValue[3] = {};

    mRobotProtocol->setArduinoSensorValue(wArduinoSensorValue, sizeof(wArduinoSensorValue));
}
