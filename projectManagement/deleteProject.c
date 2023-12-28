//
// Created by Aweso on 12/16/2023.
//

#include "projectManagement.h"

int deleteProject(char *name){
    int retVal = 0;

    chdir("projects");
    char buffer[25];
    snprintf(buffer,25,"rmdir /S/Q %s\\",name);
    retVal = system(buffer);
    system("dir /b/a:d > projects.dat");
    projectCount--;

    return retVal;
}
