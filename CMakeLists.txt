cmake_minimum_required(VERSION 3.27)
project(torqueCalculator C)

set(CMAKE_C_STANDARD 17)

add_executable(torqueCalculator main.c
        projectManagement/createProject.c
        objectManipulation/createNewObject.c
        structs.c
        projectManagement/initProgram.c
        projectManagement/fileManagement.h
        projectManagement/deleteProject.c)
