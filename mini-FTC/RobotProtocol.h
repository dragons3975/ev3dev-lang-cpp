#pragma once

class RobotProtocol
{
    private:
        char mEv3MotorSpeed[4] = {};
        char mArduinoMotorSpeed[5] = {};
        char mEv3SensorValue[8] = {};
        char mArduinoSensorValue[2] = {};

    public:
        RobotProtocol();
        void decodeMotors(const char *buffer);
        void encodeSensors(char *buffer);
        char* getEv3MotorSpeed();
        char* getArduinoMotorSpeed();
        void setEv3SensorValue(char *iEv3SensorValue, int size);
        void setArduinoSensorValue(char *iArduinoSensorValue, int size);
};
