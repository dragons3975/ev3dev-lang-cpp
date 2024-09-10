#pragma once

#include "ceserial.h"
#include "RobotProtocol.h"

class Arduino
{
    private:
        ceSerial mComPort;
        void set(uint8_t key, uint8_t value);
        void get(uint8_t* buffer, uint8_t key, uint8_t size);
        RobotProtocol *mRobotProtocol;

    public:
        Arduino(RobotProtocol *iRobotProtocol);
        ~Arduino();
        void run();
        void stop();
};
