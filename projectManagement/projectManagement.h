//
// Created by Aweso on 12/16/2023.
//

#ifndef TORQUECALCULATOR_FILEMANAGEMENT_H
#define TORQUECALCULATOR_FILEMANAGEMENT_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


#include "../../csvLib/csv.h"
#include "../../csvLib/csvUtils.h"

#define MAX_PROJECT_COUNT 25

#define CONFIG_HEADER_SIZE 17

extern int projectCount;



typedef struct{
    char name[20];
    FILE *info;
    CSV objects;
}Project;


int createProject(char *name, char *notes);

int initProgram();

int deleteProject(char *name);

Project openProject(char *name);

int doesProjectExist(char *name);

int closeProject(Project *source);

int getProjectCount();

char * getProjectNames();

int makeConfig(int width, int height,char wMode, char doLogo);


#endif //TORQUECALCULATOR_FILEMANAGEMENT_H
