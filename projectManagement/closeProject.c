//
// Created by Aweso on 12/22/2023.
//
#include "projectManagement.h"

int closeProject(){
    writeObjects(&currentProject.objList);
    closeObjectList(&currentProject.objList);
    memset(&currentProject,0,sizeof(Project));

    return 0;
}