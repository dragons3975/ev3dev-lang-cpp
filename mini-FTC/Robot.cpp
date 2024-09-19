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
    // 4*4 (int) moteur + 1 (bool) touch + 1 (uint8) color + 4 (float) ultrasonic + 4 (int) gyro
    char wEv3SensorValue[26] = {};

    int wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[0] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorA: " << wSpeed << std::endl;
    if (mMotorA.connected())
    {
        mMotorA.set_speed_sp(wSpeed).run_forever();
        int pos = mMotorA.position();
        wEv3SensorValue[0] = (pos >> 24) & 0xFF;
        wEv3SensorValue[1] = (pos >> 16) & 0xFF;
        wEv3SensorValue[2] = (pos >> 8) & 0xFF;
        wEv3SensorValue[3] = pos & 0xFF;
    }

    wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[1] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorB: " << wSpeed << std::endl;
    if (mMotorB.connected())
    {
        mMotorB.set_speed_sp(wSpeed).run_forever();
        int pos = mMotorB.position();
        wEv3SensorValue[4] = (pos >> 24) & 0xFF;
        wEv3SensorValue[5] = (pos >> 16) & 0xFF;
        wEv3SensorValue[6] = (pos >> 8) & 0xFF;
        wEv3SensorValue[7] = pos & 0xFF;
    }

    wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[2] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorC: " << wSpeed << std::endl;
    if (mMotorC.connected())
    {
        mMotorC.set_speed_sp(wSpeed).run_forever();
        int pos = mMotorC.position();
        wEv3SensorValue[8] = (pos >> 24) & 0xFF;
        wEv3SensorValue[9] = (pos >> 16) & 0xFF;
        wEv3SensorValue[10] = (pos >> 8) & 0xFF;
        wEv3SensorValue[11] = pos & 0xFF;
    }

    wSpeed = 900 * ((mRobotProtocol->getEv3MotorSpeed()[3] & 0xFF)/255.0*2-1);
    //std::cout << "mMotorD: " << wSpeed << std::endl;
    if (mMotorD.connected())
    {
        mMotorD.set_speed_sp(wSpeed).run_forever();
        int pos = mMotorD.position();
        wEv3SensorValue[12] = (pos >> 24) & 0xFF;
        wEv3SensorValue[13] = (pos >> 16) & 0xFF;
        wEv3SensorValue[14] = (pos >> 8) & 0xFF;
        wEv3SensorValue[15] = pos & 0xFF;
    }
    
    wEv3SensorValue[16] = mTouchSensor.connected() ? mTouchSensor.is_pressed() & 0xFF : 0;
    wEv3SensorValue[17] = mColorSensor.connected() ? mColorSensor.color() & 0xFF : 0;

    if (mUltrasonicSensor.connected())
    {
        int pos = mUltrasonicSensor.distance_centimeters();
        wEv3SensorValue[18] = (pos >> 24) & 0xFF;
        wEv3SensorValue[19] = (pos >> 16) & 0xFF;
        wEv3SensorValue[20] = (pos >> 8) & 0xFF;
        wEv3SensorValue[21] = pos & 0xFF;
    }
    if (mGyroSensor.connected())
    {
        int pos = mGyroSensor.angle();
        wEv3SensorValue[22] = (pos >> 24) & 0xFF;
        wEv3SensorValue[23] = (pos >> 16) & 0xFF;
        wEv3SensorValue[24] = (pos >> 8) & 0xFF;
        wEv3SensorValue[25] = pos & 0xFF;
    }

    mRobotProtocol->setEv3SensorValue(wEv3SensorValue, sizeof(wEv3SensorValue));

    mArduino.run();
}

void Robot::stop()
{
    if (mMotorA.connected()) mMotorA.stop();
    if (mMotorB.connected()) mMotorB.stop();
    if (mMotorC.connected()) mMotorC.stop();
    if (mMotorD.connected()) mMotorD.stop();
}
