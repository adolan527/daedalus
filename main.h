//
// Created by Aweso on 12/31/2023.
//

#ifndef TORQUECALCULATOR_MAIN_H
#define TORQUECALCULATOR_MAIN_H
#include <stdbool.h>
#include "raylib.h"


typedef struct{
    double constant;
    double meter;
}Parametric;

typedef enum{
    sRectangle,
    sSphere,
    sCylinder,
}ShapeType;

typedef struct{
    double xLength;//radius for sphere
    double yHeight;//for cylinders, the dimensions not in the facing direction are the radius
    double zDepth;
    double thickness; //0 == solidbody
    char facing;// x, y, or z
    bool isHole;
}tqcShape;

typedef struct{
    char name[20];
    double density;
    Color color;
    Texture2D texture; // lb/in^3
}tqcMaterial;

typedef struct {
    char name[20];
    Parametric xPos; //in inches
    double yPos; //position is defined as the bottom left corner for rectangles, center for spheres, and center of bottom left face circle.
    double zPos;
    ShapeType type;
    tqcShape data;
    tqcMaterial material;
    Model *model;
}Object;

typedef struct ObjectNode{
    Object *data;
    struct ObjectNode *next;
}ObjectNode;

typedef struct{
    ObjectNode *head;
    ObjectNode *tail;
}ObjectList;





#endif //TORQUECALCULATOR_MAIN_H
