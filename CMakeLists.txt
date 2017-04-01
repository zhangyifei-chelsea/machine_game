CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(machine_game)

include_directories(.)

set(CMAKE_CXX_STANDARD 11)

SET(SOURCE_FILES machine_game.ino PS2X_lib.cpp MyServo.cpp fix.cpp Adafruit_PWMServoDriver.cpp)

add_executable(machine_game ${SOURCE_FILES})