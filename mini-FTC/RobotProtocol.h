#pragma once

class RobotProtocol
{
    private:
        char mEv3MotorSpeed[4] = {};
        char mArduinoMotorSpeed[5] = {};
        char mArduinoMotorMode[5] = {};
        char mEv3SensorValue[29] = {};
        char mArduinoSensorValue[9] = {};

    public:
        RobotProtocol();
        void decodeMotors(const char *buffer);
        void encodeSensors(char *buffer);
        char* getEv3MotorSpeed();
        char* getArduinoMotorSpeed();
        char* getArduinoMotorMode();
        void setEv3SensorValue(char *iEv3SensorValue, int size);
        void setArduinoSensorValue(char *iArduinoSensorValue, int size);
};
