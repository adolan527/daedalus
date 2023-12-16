//
// Created by Aweso on 11/2/2023.
//

#include "createNewObject.h"
#define GETINPUT {fflush(stdin);fgets(buffer,20,stdin);}


Rectangle* newRectangle(){
    char buffer[20];

    Rectangle *tempRectangle = malloc(sizeof(Rectangle));
    printf("  Rectangle:\n");
    printf("    Length (x): ");
    GETINPUT
    tempRectangle->xLength = atof(buffer);

    printf("    Width (y): ");
    GETINPUT
    tempRectangle->yWidth = atof(buffer);

    printf("    Height (z): ");
    GETINPUT
    tempRectangle->zHeight = atof(buffer);

    printf("    Thickness if hollow (0 for solid-body): ");
    GETINPUT
    tempRectangle->thickness = atof(buffer);
    return tempRectangle;
}

RectangleTube* newRectangleTube(){


    return NULL;
}


Object* createNewObject() {
    char buffer[20] = "";
    int numBuffer = 0;
    Object *tempObject = malloc(sizeof(Object));


    printf("Name: ");
    GETINPUT
    removeWhitespace(buffer,buffer);
    while(strlen(buffer)==0){
        printf("Invalid entry\n");
        printf("Name: ");
        GETINPUT
        removeWhitespace(buffer,buffer);
    }
    strncpy(tempObject->name, buffer, 20);

    printf("  Start position: ");
    GETINPUT

    while (decodeParametric(buffer, &tempObject->x_start) == 1) {
        printf("  Invalid entry\n");
        printf("  Start position: ");
        GETINPUT
    }

    printf("  End position: ");
    GETINPUT

    while (decodeParametric(buffer, &tempObject->x_end) == 1) {
        printf("  Invalid entry\n");
        printf("  End position: ");
        GETINPUT
    }

    printf("  Density: ");
    GETINPUT
    tempObject->density = atof(buffer);

    printf("  Select a shape:\n   %s\n  ", SHAPE_LIST_STRING);
    GETINPUT
    numBuffer = atoi(buffer);

    while (numBuffer > MAX_SHAPE_INDEX) {
        printf("  Invalid entry\n");
        printf("  Select a shape:\n%s", SHAPE_LIST_STRING);
        GETINPUT
        numBuffer = atoi(buffer);
    }

    switch(numBuffer){
        case Rect:
            tempObject->shape = Rect;
            tempObject->shapeData = newRectangle();
            break;
        case RectTube:
            tempObject->shape = RectTube;
            tempObject->shapeData = newRectangleTube();
            break;
        default:
            break;


    }


    tempObject->area.order = 0;
    for (int i = 0; i < COEFF_COUNT; i++) {
        tempObject->area.coefficients[i] = 0;
    }
    tempObject->area.coefficients[0] = 1;



    return tempObject;

}

