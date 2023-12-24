#include <stdio.h>
#include "projectManagement/projectManagement.h"
#include "../csvLib/csv.h"
#include "../csvLib/csvUtils.h"
#include "display/drawMain.h"

int main(){
    //drawMain();

    initProgram();
    char name[20];
    char notes[20];
    Project current;
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
            if(doesProjectExist(name)==1){
                printf("That projects exists\n");
                current = openProject(name);
                char buf = fgetc(current.info);
                while(buf!=-1){
                    fputc(buf,stdout);
                    buf = fgetc(current.info);
                }

                displayCSV(&current.objects,0,0,1,stdout);
                closeProject(&current);
            }
            else{
                printf("\nEnter some notes:");
                scanf("%s",notes);
                createProject(name,notes);
            }

        }


    }
    return 0;
}
