//
// Created by Aweso on 11/2/2023.
//

#include "calculations.h"



/*
 * Was only used in the CLI prototype
void removeWhitespace(char *srcString, char *destString){
    int destIndex = 0;
    for(int i = 0;i<1000;i++){
        if(isspace(srcString[i])==0){
            destString[destIndex]=srcString[i];
            destIndex++;
        }
        if(srcString[i]==0){
            destString[destIndex] = 0;
            return;
        }
    }
}
*/
double computePolynomial(Polynomial *function, double input){
    double sum = 0;
    for(int i = 0; i < POLYNOMIAL_COEFF_COUNT; i++){
        if(function->coefficients[i]!=0){
            sum += function->coefficients[i] * pow(input,(function->order - i));
        }
    }
    if(sum==NAN)return 0;
    return sum;
}


double integratePolynomial(Polynomial *function, double a, double b){
    //a and b are bounds
    //does not support 1/x (that would require ln)
    Polynomial antiDerivative = {{0}, function->order + 1};
    for(int i = 0; i < POLYNOMIAL_COEFF_COUNT; i++){
        if((antiDerivative.order - i)==0){
            antiDerivative.coefficients[i] = 0;
        }
        else{
            double coeff = function->coefficients[i];
            double order = (antiDerivative.order - i) ? (antiDerivative.order - i) : 1;
            antiDerivative.coefficients[i] = coeff/order;
        }

    }
    char buffer[50] = {0};
    stringifyPolynomial(&antiDerivative,buffer);
    printf("%s\n",buffer);
    double top = computePolynomial(&antiDerivative,b);
    double bot = computePolynomial(&antiDerivative,a);
    return top - bot;
}

void stringifyParametric(Parametric *function, char *destString) {
    char buffer[30] = "";
    char meterSign = '+';
    double meterModifier = 1;
    if(function->meter<0) {meterSign = '-'; meterModifier = -1;}
    unsigned long long offset = 0;
    if (function->meter != 0) {
        snprintf(buffer, 30,"%.2lf %c ", function->constant,meterSign);
        strcpy(destString, buffer);
        offset = strlen(buffer);
        snprintf(buffer, 30, "%.2lft", meterModifier * function->meter);
        strcpy(destString+offset, buffer);

    }

    else{
        sprintf(destString, "%.2lf", function->constant);
    }
}

void stringifyPolynomial(Polynomial *function,char *destString){
    unsigned long long offset = 0;
    for(int i = 0; i < POLYNOMIAL_COEFF_COUNT; i++){
        char buffer[30] = "";
        if(function->coefficients[i]!=0){
            if((function->order)-i == 0){
                sprintf(buffer,"%.2lf + ",function->coefficients[i]);

            }
            else if(function->coefficients[i]==1){
                sprintf(buffer,"x^%d + ",(function->order)-i);

            }
            else{
                sprintf(buffer,"%.2lfx^%d + ",function->coefficients[i],(function->order)-i);

            }
            strcpy(destString+offset,buffer);
            offset += strlen(buffer);
        }
    }
    if(offset>0){
        strcpy(&destString[offset-3],"\0\0\0");
    }
}

void nullifyPolynomial(Polynomial *dest){
    for(int i = 0; i < POLYNOMIAL_COEFF_COUNT; i++){
        dest->coefficients[i] = 0;
    }
}

double computeObject(Object *source, float t){
    // TODO All of the integrals are lacking the term (h-x) where h is the center of mass of the object)
    // TODO Luckily, the simple shapes that this program supports all have very easy to calculate -
    // TODO centers of mass.
    Polynomial areaFunction = {0};
    double xPosition = cmpPmt(source->xPos,t);
    double xEnd = xPosition + source->data.xLength;
    double integral = 0;
    switch(source->type){
        case sRectangle:{
            if(source->data.thickness == 0){
                areaFunction.order = 1;
                areaFunction.coefficients[0] = source->data.yHeight * source->data.zDepth;
                integral = integratePolynomial(&areaFunction, xPosition, xEnd);
                return integral * source->material.density;
            }
            else{
                switch(source->data.facing){
                    case 'x':{
                        areaFunction.order = 1;
                        areaFunction.coefficients[0] = 2 * source->data.thickness * (source->data.yHeight + source->data.zDepth - 2);
                        integral = integratePolynomial(&areaFunction, xPosition, xEnd);
                        return integral * source->material.density;
                    }
                    case 'y':{
                        areaFunction.order = 1;
                        areaFunction.coefficients[0] = source->data.yHeight * source->data.zDepth;
                        integral = integratePolynomial(&areaFunction, xPosition, xEnd + source->data.thickness);
                        integral += integratePolynomial(&areaFunction, xEnd - source->data.thickness,xEnd);
                        areaFunction.coefficients[0] = 2 * source->data.yHeight * source->data.thickness;
                        integral += integratePolynomial(&areaFunction, xPosition + source->data.thickness, xEnd - source->data.thickness);
                        return integral * source->material.density;
                    }
                    case 'z':{
                        areaFunction.order = 1;
                        areaFunction.coefficients[0] = source->data.yHeight * source->data.zDepth;
                        integral = integratePolynomial(&areaFunction, xPosition, xEnd + source->data.thickness);
                        integral += integratePolynomial(&areaFunction, xEnd - source->data.thickness,xEnd);
                        areaFunction.coefficients[0] = 2 * source->data.zDepth * source->data.thickness;
                        integral += integratePolynomial(&areaFunction, xPosition + source->data.thickness, xEnd - source->data.thickness);
                        return integral * source->material.density;
                    }
                }
            }
            break;
        }
        case sCylinder:{
            switch(source->data.facing){
                case 'x':{
                    areaFunction.order = 2;
                    areaFunction.coefficients[0] = 2 * M_PI * source->data.zDepth;
                    integral = integratePolynomial(&areaFunction, xPosition, xEnd);
                    return integral * source->material.density;
                }
                case 'y':{

                }
                case 'z':{

                }
            }
        }
            break;
        case sSphere:{
            float xCenter = cmpPmt(source->xPos, t);
            areaFunction.coefficients[0] = -1;
            areaFunction.coefficients[1] = 2 * xCenter;
            areaFunction.coefficients[2] = (source->data.xLength * source->data.xLength) - (xCenter * xCenter);
            areaFunction.order = 2;
            integral = integratePolynomial(&areaFunction,xCenter - source->data.xLength, xCenter + source->data.xLength);
            integral *= M_PI;
            integral *= source->material.density;
            return integral;
        }
    }
}