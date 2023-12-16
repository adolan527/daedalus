//
// Created by Aweso on 12/15/2023.
//

#include "fileManagement.h"


int duplicateCheck(char *name){
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

int createProject(char *name, char *notes){
    chdir("projects/");
    if(duplicateCheck(name)==1){
        //project already exists
        printf("Already exists");
        return 1;
    }
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


    return 0;
}

