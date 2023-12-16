//
// Created by Aweso on 12/16/2023.
//

#include "fileManagement.h"

int deleteProject(char *name){
    int retVal = 0;
    chdir("projects/");
    char buffer[25];
    snprintf(buffer,25,"rmdir /s/q %s",name);
    retVal = system(buffer);
    system("dir /b/a:d > projects.dat");

    return retVal;
}
