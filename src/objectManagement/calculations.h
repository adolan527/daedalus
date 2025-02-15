//
// Created by Aweso on 11/2/2023.
//

#ifndef DAEDALUS_STRUCTS_H
#define DAEDALUS_STRUCTS_H


#include "../main.h"

#define POLYNOMIAL_COEFF_COUNT 3
typedef struct{
    double coefficients[POLYNOMIAL_COEFF_COUNT];
    int order;
}Polynomial;



//void removeWhitespace(char *srcString, char *destString);//src and dst can be the same and it still works

double computePolynomial(Polynomial *function, double input);

double integratePolynomial(Polynomial *function, double a, double b);

void stringifyPolynomial(Polynomial *function,char *destString);






#endif //DAEDALUS_STRUCTS_H
