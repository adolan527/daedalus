//
// Created by Aweso on 11/2/2023.
//

#ifndef GENERALIZEDROBOTARM_STRUCTS_H
#define GENERALIZEDROBOTARM_STRUCTS_H

#include <stdbool.h>

#ifndef _INC_STRING
#include <string.h>
#endif

#ifndef _INC_STDLIB
#include <stdlib.h>
#endif

#ifndef _MATH_H_
#include <math.h>
#endif

#ifndef _INC_STDIO
#include <stdio.h>
#endif

#ifndef _INC_CTYPE
#include <ctype.h>
#endif


#define POLYNOMIAL_COEFF_COUNT 3
typedef struct{
    double coefficients[POLYNOMIAL_COEFF_COUNT];
    int order;
}Polynomial;

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

typedef struct {
    char name[20];
    Parametric x_start; //in inches
    Parametric x_end; //in inches
    double yPos; //position is defined as the bottom left corner for rectangles, center for spheres, and center of bottom left face circle.
    double zPos;
    double density; //lb/in
    ShapeType type;
    tqcShape data;
}Object;

typedef struct ObjectNode{
    Object *data;
    struct ObjectNode *next;
}ObjectNode;

typedef struct{
    ObjectNode *head;
    ObjectNode *tail;
}ObjectList;


#define cmpPmt(_parameter_literal,_parameter_meter) (_parameter_literal.constant + _parameter_literal.meter * _parameter_meter)

//void removeWhitespace(char *srcString, char *destString);//src and dst can be the same and it still works

double computePolynomial(Polynomial *function, double input);

double integratePolynomial(Polynomial *function, double a, double b);

void stringifyParametric(Parametric *function, char *destString);

void stringifyPolynomial(Polynomial *function,char *destString);



ObjectList initObjectList();

void appendObject(ObjectList *source, Object *data);

void closeObjectList(ObjectList *source);

Object * getObjectPointer(ObjectList *source, int index);

void deleteObject(ObjectList *source, int index);

void insertObject(ObjectList *source, Object *data, int index);





#endif //GENERALIZEDROBOTARM_STRUCTS_H
