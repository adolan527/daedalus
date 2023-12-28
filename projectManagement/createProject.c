//
// Created by Aweso on 12/15/2023.
//

#include "projectManagement.h"




int createProject(char *name, char *notes){
    if(getProjectCount() >= MAX_PROJECT_COUNT){
        printf("Maximum amount of projects reached");
        return 1;
    }
    if(doesProjectExist(name) == 1){
        //project already exists
        printf("Already exists");
        return 1;
    }
    chdir("projects");

    //make project folder
    mkdir(name);
    chdir(name);
    //make info file
    FILE *info = fopen("info.dat","w");
    if(info == NULL){
        return 1;
    }
    fputs("Name: ",info);
    fputs(name,info);
    fputc('\n',info);
    fputs("Notes: ",info);
    fputs(notes,info);
    fclose(info);

    //make objects file
    FILE *objects = fopen("objects.dat","w");
    if(objects == NULL){
        return 1;
    }
    fputs("name,startC,startM,endC,endM,density,shape,xlength,ywidth,zheight,thickness,face,hole\n",objects);
    fclose(objects);

    chdir("..");
    system("dir /b/a:d > projects.dat");
    chdir("..");

    projectCount++;
    return 0;
}

