#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "structs.h"
#include "objectManipulation/createNewObject.h"



Object *globalObjects[100];//within this project, holds all malloc-ed data.


int saveObject();
int quit();


void closeProgram(){//frees all data
    for(int i = 0;i<100;i++){
        if(globalObjects[i]!=NULL){
            free(globalObjects[i]->shapeData);
            free(globalObjects[i]);
        }
    }
}



int main() {




    globalObjects[0] = createNewObject();

    printObject(globalObjects[0]);
    char hold;
    scanf("%c",&hold);


    char string[20] = "3t";
    Parametric blank;
    decodeParametric(string,&blank);
    stringifyParametric(&blank,string);
    printf("%s",string);

    closeProgram();
    return 0;


}


double integrateConstantArea(double lowerBound, double upperBound, double constant){
    double upperCompute = (pow(upperBound,2)/2);
    double lowerCompute = (pow(lowerBound,2)/2);

    return constant*(upperCompute-lowerCompute);

}


