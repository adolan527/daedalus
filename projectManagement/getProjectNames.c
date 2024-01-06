//
// Created by Aweso on 12/24/2023.
//
#include "projectManagement.h"

char * getProjectNames(){
    char *names =calloc(getProjectCount(), 20 * sizeof(char));
    chdir("projects");
    system("dir /b/a:d > projects.dat");

    FILE *projects = fopen("projects.dat", "r");
    if(projects == NULL){
        return 0;
    }
    for(int i = 0;i<projectCount;i++){
        fscanf_s(projects,"%s",&names[i*20],20);
    }
    chdir("../");
    return names;
}