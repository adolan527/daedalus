#include <stdio.h>
#include "projectManagement/projectManagement.h"
#include "../csvLib/csv.h"
#include "../csvLib/csvUtils.h"
#include "display/drawMain.h"
#include "objectManagement/tqcObjects.h"

int projectCount = 0;

int main(){
    /*
    Polynomial temp = {{2,0,3},4};
    char buffer[50] = {0};
    stringifyPolynomial(&temp,buffer);
    printf("%s\n",buffer);
    printf("Integrated over 0 to 10 is: %f",integratePolynomial(&temp,0,10));
     */

    if(initProgram()==1){
        printf("Init failed");
        return 0;
    }
    if(initDraw()==1){
        printf("Init draw failed");
        return 0;
    }
    if(drawMain(LOGO)==1){
        if(initDraw()==1){
            printf("Init draw failed");
            return 0;
        }
        while(drawMain(SETTINGS)==1){
            if(initDraw()==1){
                printf("Init draw failed");
                return 0;
            }
        }
    }

    return 0;
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
        else if(name[0]=='p'){
            printf("Project count: %d",projectCount);
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
