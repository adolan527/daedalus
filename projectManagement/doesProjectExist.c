//
// Created by Aweso on 12/22/2023.
//
#include "projectManagement.h"

int doesProjectExist(char *name){
    chdir("projects");
    system("dir /b/a:d > projects.dat");

    FILE *projects = fopen("projects.dat", "rb");
    if(projects == NULL){
        return 0;
    }

    while(!feof(projects)){
        char buffer[50] = {0};
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