//
// Created by Aweso on 12/30/2023.
//
#include "projectManagement.h"

void previewProjectInfo(char *dest, int destSize, char *name){
    if(doesProjectExist(name)!=1) {
        sprintf(dest,"Project does not exist");
        return;
    }
    char filename[100] = {0};
    sprintf(filename,"projects/%s/info.dat",name);
    FILE *infoFile = fopen(filename,"r");
    if(infoFile == NULL){
        sprintf(dest,"No/corrupted file");
        return;
    }
    fread(dest,1,destSize-1,infoFile);
    fclose(infoFile);


}
