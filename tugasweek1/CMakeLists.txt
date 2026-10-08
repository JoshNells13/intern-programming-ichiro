cmake_minimum_required(VERSION 3.10)
project(MainanRobotSoccer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Simulasi Utama
add_executable(main
    src/Main.cpp
    src/Ball.cpp
    src/CameraSensor.cpp
    src/ConfigLoader.cpp
    src/Field.cpp
    src/Robot.cpp
    src/Simulator.cpp
    src/Striker.cpp
    src/StrikerState.cpp
)

# Unit Testing
add_executable(unit_test
    src/UnitTest.cpp
    src/Ball.cpp
)
