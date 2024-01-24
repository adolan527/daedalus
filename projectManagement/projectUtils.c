//
// Created by Aweso on 1/6/2024.
//
#include "projectManagement.h"

int doesProjectExist(char *name){
    chdir("projects");
    system("dir /b/a:d > projects.dat");

    FILE *projects = fopen("projects.dat", "r");
    if(projects == NULL){
        return 0;
    }

    while(!feof(projects)){
        char buffer[NAMESIZE+1] = {0};
        int bufferIndex = 0;
        for(int buf = fgetc(projects); buf != '\n' && buf != '\r'; buf=fgetc(projects)){
            if(buf == -1){
                fclose(projects);
                chdir("../");
                return 0;
            }
            buffer[bufferIndex] = (char)buf;
            bufferIndex ++;
        }
        buffer[bufferIndex] = 0;
        if(strcmp(buffer,name)==0){
            fclose(projects);
            chdir("../");
            return 1;
        }

    }
    chdir("../");
    return 0;
}

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

char * getProjectNames(){
    char *names =calloc(getProjectCount(), NAMESIZE * sizeof(char));
    chdir("projects");
    system("dir /b/a:d > projects.dat");

    FILE *projects = fopen("projects.dat", "r");
    if(projects == NULL){
        return 0;
    }
    for(int i = 0;i<projectCount;i++){
        //read up to NAMESIZE characters from projects until you reach a newline, then don't read the newline
        for(int j = 0; j<NAMESIZE;j++){
            char buf = fgetc(projects);
            if(buf == '\n'||buf=='\r'){
                break;
            }
            names[i*NAMESIZE+j] = buf;
        }
    }
    chdir("../");
    return names;
}

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
