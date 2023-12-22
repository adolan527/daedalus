//
// Created by Aweso on 12/21/2023.
//
#include "fileManagement.h"

Project openProject(char *name){
    Project proj = {{0}, {0}, {}};
    chdir("projects/");
    if(doesProjectExist(name)!=1) return proj;

    FILE *objFile = fopen("proj.dat", "r+");
    if(objFile == NULL) return proj;

    proj.objects = openCSV(objFile, DEFAULT_SETTINGS);
    fclose(objFile);
    if(proj.objects.rows == NULL) return proj;

    strncpy(proj.name,name,19);
    proj.name[19] = 0;


    return proj;
}