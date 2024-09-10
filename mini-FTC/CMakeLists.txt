set(SOURCE_FILES
    Arduino.cpp
    mini-ftc.cpp
    Robot.cpp
    RobotProtocol.cpp
    Serveur.cpp)

add_executable(mini-ftc ${SOURCE_FILES})
target_link_libraries(mini-ftc ev3dev)
