//
// Created by Aweso on 12/23/2023.
//
#include "projectManagement.h"

int getProjectCount(){
    chdir("projects");
    system("dir /b/a:d > projects.dat");

    FILE *projects = fopen("projects.dat", "r");
    if(projects == NULL){
        return 0;
    }
    projectCount = 0;
    for(int buf = fgetc(projects); buf != -1; buf=fgetc(projects)){
        if(buf == '\n'||buf=='\r'){
            projectCount++;
        }
    }

    chdir("../");

    return projectCount;
}