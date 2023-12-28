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
        fgets(&names[i*20],20,projects);
    }
    chdir("../");
    return names;
}