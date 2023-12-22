#include <stdio.h>
#include "projectManagement/fileManagement.h"
#ifndef CSV_CSV_H
#include "../csvLib/csv.h"
#include "../csvLib/csvUtils.h"
#endif



int main() {
    initProgram();
    char name[20];
    char notes[20];
    while(1){
        printf("Enter a name:");
        scanf("%s",name);
        if(name[0]=='q')return 0;
        if(name[0]=='d'){
            printf("Enter a name to delete:");
            scanf("%s",name);
            deleteProject(name);
        }
        else{
            printf("\nEnter some notes:");
            scanf("%s",notes);
            createProject(name,notes);
        }


    }
    return 0;
}
