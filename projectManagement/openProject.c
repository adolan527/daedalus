//
// Created by Aweso on 12/21/2023.
//
#include "projectManagement.h"

Project openProject(char *name){
    Project proj = {{0}, NULL,{0}};
    if(doesProjectExist(name)!=1) return proj;

    //load objects
    char filename[100];
    sprintf(filename, "projects/%s/objects.dat", name);

    FILE *objFile = fopen(filename, "r+");
    if(objFile == NULL) return proj;

    proj.objCSV = openCSV(objFile, DEFAULT_SETTINGS);
    fclose(objFile);
    if(proj.objCSV.rows == NULL){
        return proj;
    }

    //check for info.dat
    memset(filename,0,100);
    sprintf(filename,"projects/%s/info.dat",name);

    FILE *infoFile = fopen(filename,"r");
    if(infoFile == NULL) return proj;

    proj.info = infoFile;

    //assign name
    strncpy(proj.name,name,19);
    proj.name[19] = 0;


    return proj;
}