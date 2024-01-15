//
// Created by Aweso on 12/21/2023.
//
#include "projectManagement.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
int openProject(char *name){
    if(currentProject.name[0]!=0){
        closeProject();
    }
    if(doesProjectExist(name)!=1) return 1;

    //assign name
    strncpy(currentProject.name,name,NAMESIZE);

    //load objects
    if(readObjects()!=0) return 1;



    return 0;
}
#pragma clang diagnostic pop