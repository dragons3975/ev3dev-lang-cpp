#include "Robot.h"

#include <iostream>

Robot::Robot(RobotProtocol *iRobotProtocol)
    : mRobotProtocol(iRobotProtocol)
    , mMotorA(ev3dev::OUTPUT_A)
    , mMotorB(ev3dev::OUTPUT_B)
    , mMotorC(ev3dev::OUTPUT_C)
    , mMotorD(ev3dev::OUTPUT_D)
    , mTouchSensor()
    , mColorSensor()
    , mUltrasonicSensor()
    , mGyroSensor()
    , mArduino(iRobotProtocol)
{
}

Robot::~Robot()
{
    stop();
}

void Robot::run()
{
    int wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[0] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorA: " << wSpeed << std::endl;
    if (mMotorA.connected()) mMotorA.set_speed_sp(wSpeed).run_forever();

    wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[1] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorB: " << wSpeed << std::endl;
    if (mMotorB.connected()) mMotorB.set_speed_sp(wSpeed).run_forever();

    wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[2] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorC: " << wSpeed << std::endl;
    if (mMotorC.connected()) mMotorC.set_speed_sp(wSpeed).run_forever();

    wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[3] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorD: " << wSpeed << std::endl;
    if (mMotorD.connected()) mMotorD.set_speed_sp(wSpeed).run_forever();
    
    char wEv3SensorValue[8] = {};
    wEv3SensorValue[0] = mMotorA.connected() ? mMotorA.position() & 0xFF : 0;
    wEv3SensorValue[1] = mMotorB.connected() ? mMotorB.position() & 0xFF : 0;
    wEv3SensorValue[2] = mMotorC.connected() ? mMotorC.position() & 0xFF : 0;
    wEv3SensorValue[3] = mMotorD.connected() ? mMotorD.position() & 0xFF : 0;
    wEv3SensorValue[4] = mTouchSensor.connected() ? mTouchSensor.is_pressed() & 0xFF : 0;
    wEv3SensorValue[5] = mColorSensor.connected() ? mColorSensor.color() & 0xFF : 0;
    wEv3SensorValue[6] = mUltrasonicSensor.connected() ? (int)mUltrasonicSensor.distance_centimeters() & 0xFF : 0;
    wEv3SensorValue[7] = mGyroSensor.connected() ? mGyroSensor.angle() & 0xFF : 0;

    mRobotProtocol->setEv3SensorValue(wEv3SensorValue, sizeof(wEv3SensorValue));

    mArduino.run();

    //char wArduinoSensorValue[2] = {};

    //mRobotProtocol->setArduinoSensorValue(wArduinoSensorValue, sizeof(wArduinoSensorValue));
}

void Robot::stop()
{
    if (mMotorA.connected()) mMotorA.stop();
    if (mMotorB.connected()) mMotorB.stop();
    if (mMotorC.connected()) mMotorC.stop();
    if (mMotorD.connected()) mMotorD.stop();
}
