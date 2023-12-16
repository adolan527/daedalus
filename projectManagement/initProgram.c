//
// Created by Aweso on 12/15/2023.
//

#include "fileManagement.h"


#define HEADERSIZE 17
const char HEADER[HEADERSIZE] = "torqueCalculator";

int doesConfigExist(){
    FILE *config = fopen("config.dat","r");
    if(config == NULL){
        return 1;
    }
    char buffer[17];
    fgets(buffer,16,config);
    buffer[16] = 0;
    if(strcmp(buffer,HEADER)!=0){
        fclose(config);
        return 1;
    }
    fclose(config);
    return 0;
}

int makeConfig(){
    FILE *config = fopen("config.dat","w");
    if(config == NULL){
        return 1;
    }
    fputs(HEADER,config);
    //Other config stuff
    //To be implemented

    fclose(config);
    return 0;
}

int initProgram() {
    if (doesConfigExist() == 0) {
        //program is already initialized
        return 0;
    }
    int retVal = 0;
    retVal += makeConfig();
    FILE *error = fopen("error.log","w");
    if(error == NULL){
        return 1;
    }
    fclose(error);
    retVal += mkdir("projects/");
    retVal += system("dir /b/a:d projects\\ > projects/projects.dat");

    return retVal;
}