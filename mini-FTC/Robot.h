#pragma once

#include <ev3dev.h>

#include "RobotProtocol.h"

class Robot
{
    private:
        ev3dev::large_motor mMotorA, mMotorB, mMotorC, mMotorD;
        ev3dev::touch_sensor mTouchSensor;
        ev3dev::color_sensor mColorSensor;
        ev3dev::ultrasonic_sensor mUltrasonicSensor;
        ev3dev::gyro_sensor mGyroSensor;
        RobotProtocol *mRobotProtocol;

    public:
        Robot(RobotProtocol *iRobotProtocol);
        void run();
};
