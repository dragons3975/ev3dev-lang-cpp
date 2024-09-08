#include <chrono>
#include <thread>
#include <stdexcept>

#include <ev3dev.h>

#include "Serveur.h"
#include "RobotProtocol.h"
#include "Robot.h"

typedef enum {
    Reset,
    Init,
    Run
} State;

int main() {

    Serveur wServeur;
    RobotProtocol wRobotProtocol;
    Robot wRobot(&wRobotProtocol);
    
    ev3dev::sound::speak("Hello");
    
    State state = Run;
    
    char buffer[1024];

    while ( ! ev3dev::button::enter.pressed() )
    {
        wServeur.receive(buffer);

        switch(state)
        {
            case Reset:
                break;
            case Init:
                break;
            case Run:
                wRobotProtocol.decodeMotors(buffer);
                wRobot.run();
                wRobotProtocol.encodeSensors(buffer);
                break;
            default:
                break;
        }

        wServeur.send(buffer);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    ev3dev::led::all_off();
    return 0;
}
