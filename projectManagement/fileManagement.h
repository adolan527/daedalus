//
// Created by Aweso on 12/16/2023.
//

#ifndef TORQUECALCULATOR_FILEMANAGEMENT_H
#define TORQUECALCULATOR_FILEMANAGEMENT_H

#endif //TORQUECALCULATOR_FILEMANAGEMENT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifndef CSV_CSV_H
#include "../../csvLib/csv.h"
#include "../../csvLib/csvUtils.h"
#endif

typedef struct{
    char name[20];
    CSV objects;
}Project;


int createProject(char *name, char *notes);

int initProgram();

int deleteProject(char *name);

Project openProject(char *name);

int doesProjectExist(char *name){
    FILE *projects = fopen("projects.dat", "r");
    if(projects == NULL){
        return 1;
    }
    while(!feof(projects)){
        fseek(projects, 39, SEEK_CUR);
        char buffer[50];
        int bufferIndex = 0;
        for(char buf = fgetc(projects); buf != '\n'; buf=fgetc(projects)){
            if(buf == -1){
                fclose(projects);
                return 0;
            }
            buffer[bufferIndex] = buf;
            bufferIndex ++;
        }
        buffer[bufferIndex] = 0;
        if(strcmp(buffer,name)==0){
            fclose(projects);
            return 1;
        }

    }
    return 0;
}