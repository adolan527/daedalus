cmake_minimum_required(VERSION 3.26)
project(GeneralizedRobotArm C)

set(CMAKE_C_STANDARD 17)

add_executable(GeneralizedRobotArm main.c
        structs.c
        objectManipulation/createNewObject.c
        objectManipulation/createNewObject.h

)
