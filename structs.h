//
// Created by Aweso on 11/2/2023.
//

#ifndef GENERALIZEDROBOTARM_STRUCTS_H
#define GENERALIZEDROBOTARM_STRUCTS_H

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


#define COEFF_COUNT 5
typedef struct{
    double coefficients[COEFF_COUNT];
    int order;
}Polynomial;


typedef struct{
    double constant;
    double meter;
}Parametric;

typedef enum{
    sRectangle,
    sRectangleTube,
    sSphere,
    sCylinder,
    sTriangle,
}Shape;

struct ShapeRectangle{
    double xLength;
    double yWidth;
    double zHeight;
    double thickness;//thickness of 0 = solidbody
};

struct ShapeRectangleTube{
    double xLength;
    double yWidth;
    double zHeight;
    double thickness;
    char holeFace; //x,y, or z to denote which face has the hole through it.
    //If x then atlas arm, if y then atlas claw, if z then atlas bevel gearbox,
};


struct ShapeSphere{
    double radius;
    double thickness;//thickness of 0 = solidbody
};

struct ShapeCylinder{
    double radius;
    double height;
    double thickness;//thickness of 0 = solidbody
};

struct ShapeTriangularPrism{
    double xLength;
    double yWidth;
    double zHeight;
    double thickness;//thickness of 0 = solidbody
};


typedef struct {
    char name[20];
    Parametric x_start; //in inches
    Parametric x_end; //in inches
    double density; //lb/in
    Shape shape;
    void *shapeData;

}Object;

void removeWhitespace(char *srcString, char *destString);//src and dst can be the same and it still works

void stringifyRectangle(struct ShapeRectangle *shape, char *destString);

void stringifyParametric(Parametric *function, char *destString);

void stringifyPolynomial(Polynomial *function,char *destString);

int decodeParametric(char *string, Parametric *destFunction);

int decodePolynomial(char *string, Polynomial *destFunction);

double computePolynomial(Polynomial *function, double input);

void printObject(Object *current);


#endif //GENERALIZEDROBOTARM_STRUCTS_H
