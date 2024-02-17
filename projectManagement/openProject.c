//
// Created by Aweso on 12/21/2023.
//
#include "projectManagement.h"


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
