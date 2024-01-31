//
// Created by Aweso on 12/31/2023.
//

#ifndef TORQUECALCULATOR_MAIN_H
#define TORQUECALCULATOR_MAIN_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <ctype.h>

#define NAMESIZE 32

//////////////////////////////////////////////////////////////
//------------------------<Color Palette>----------------------------//
//////////////////////////////////////////////////////////////



typedef struct{
    Color white;
    Color black;
    Color light;
    Color dark;
    Color accent1;
    Color accent2;
}ColorPalette;

#define PALETTE_COUNT 10
extern ColorPalette theme;
extern ColorPalette palettes[PALETTE_COUNT];


//////////////////////////////////////////////////////////////
//------------------------<Materials>----------------------------//
//////////////////////////////////////////////////////////////
typedef struct{
    char name[NAMESIZE];
    double density;
    Color color;
    Texture2D texture; // lb/in^3
}tqcMaterial;

typedef enum{
    ALUMINUM6061,
    ALUMINUM6063,
    STEEL,
    PINEWOOD,
    POLYCARBONATE
}tqcMaterialIndex;

#define TQCMATERIALS_COUNT 15
extern tqcMaterial tqcMaterials[TQCMATERIALS_COUNT];

//////////////////////////////////////////////////////////////
//------------------------<Shapes>----------------------------//
//////////////////////////////////////////////////////////////
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


//////////////////////////////////////////////////////////////
//------------------------<Parametric>----------------------------//
//////////////////////////////////////////////////////////////

typedef struct{
    double constant;
    double meter;
}Parametric;

void stringifyParametric(Parametric *function, char *destString);

#define cmpPmt(_parameter_literal,_parameter_meter) (_parameter_literal.constant + _parameter_literal.meter * _parameter_meter)

//////////////////////////////////////////////////////////////
//------------------------<Objects and Object Lists>----------------------------//
//////////////////////////////////////////////////////////////

typedef struct {
    char name[NAMESIZE]; //32
    Parametric xPos; //in inches  //8
    double yPos; //position is defined as the bottom left corner for rectangles, center for spheres, and center of bottom left face circle.
    double zPos; //8
    tqcShape data;
    ShapeType type; //4
    tqcMaterial material;
    Model *model;
    //BoundingBox box;
}Object;

typedef struct ObjectNode{
    Object *data;
    struct ObjectNode *next;
}ObjectNode;

typedef struct{
    ObjectNode *head;
    ObjectNode *tail;
}ObjectList;

double computeObject(Object *source, float t);//gets torque with parametric

ObjectList initObjectList();

void appendObject(ObjectList *source, Object *data);

void closeObjectList(ObjectList *source);

Object * getObjectPointer(ObjectList *source, int index);

double getObjectVolume(Object *source);

void deleteObject(ObjectList *source, int index);

void insertObject(ObjectList *source, Object *data, int index);

int isObjectInList(ObjectList *list, Object *source);



//////////////////////////////////////////////////////////////
//------------------------<Projects>----------------------------//
//////////////////////////////////////////////////////////////

#define MAX_PROJECT_COUNT 25

#define CONFIG_HEADER_SIZE 17

typedef struct{
    char name[NAMESIZE];
    ObjectList objList;
}Project;


extern int projectCount;

extern Project currentProject;

void previewProjectInfo(char *dest,int destSize, char *name);

int createProject(char *name, char *notes);

int initProgram();

int deleteProject(char *name);

int openProject(char *name);

int closeProject();

int getProjectCount();

char * getProjectNames();

int makeConfig(int width, int height,char wMode, char doLogo);

//////////////////////////////////////////////////////////////
//------------------------<Resources>----------------------------//
//////////////////////////////////////////////////////////////
int writeColors();

int writeMaterials();

int writeObjects(ObjectList *objectsList);

int readObjects();

#endif //TORQUECALCULATOR_MAIN_H
