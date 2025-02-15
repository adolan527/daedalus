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
Vector3 getObjectCOM(Object *source, float t){
    //gets the object's center of mass
    Vector3 com = {0,0,0};
    switch(source->type){
        case sRectangle:{
            com.x = cmpPmt(source->xPos, t) + source->data.xLength/2;
            com.y = source->yPos + source->data.yHeight/2;
            com.z = source->zPos + source->data.zDepth/2;
            break;
        }
        case sCylinder:{
            switch(source->data.facing){
                case 'x':{
                    com.x = cmpPmt(source->xPos, t) + source->data.xLength/2;
                    com.y = source->yPos;
                    com.z = source->zPos;
                    break;
                }
                case 'y':{
                    com.x = cmpPmt(source->xPos, t);
                    com.y = source->yPos + source->data.yHeight/2;
                    com.z = source->zPos;
                    break;
                }
                case 'z':{
                    com.x = cmpPmt(source->xPos, t);
                    com.y = source->yPos;
                    com.z = source->zPos + source->data.zDepth/2;
                    break;
                }
            }
            break;
        }
        case sSphere:{
            com.x = cmpPmt(source->xPos, t);
            com.y = source->yPos;
            com.z = source->zPos;
            break;
        }
    }
    return com;
}


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

double getObjectVolume(Object *source){
    double volume = 0;

    switch(source->type){
        case sRectangle:{
            if(source->data.thickness==0){
                volume = source->data.xLength * source->data.yHeight * source->data.zDepth;
            }
            else{
                switch(source->data.facing){
                    case 'x':{
                        volume = 2*source->data.thickness * (source->data.yHeight + source->data.zDepth - 2 * source->data.thickness) * source->data.xLength;
                        break;
                    }
                    case 'y':{
                        volume = 2*source->data.thickness * (source->data.xLength + source->data.zDepth - 2 * source->data.thickness) * source->data.yHeight;
                        break;
                    }
                    case 'z':{
                        volume = 2*source->data.thickness * (source->data.xLength + source->data.yHeight - 2 * source->data.thickness) * source->data.zDepth;
                        break;
                    }
                }
            }
            break;
        }
        case sCylinder:{
            if(source->data.thickness==0){
                volume = M_PI * source->data.xLength * source->data.xLength * source->data.zDepth;
            }
            else{
                // pi*h*t*(2r+t)
                switch(source->data.facing){
                    case 'x':{
                        volume = M_PI * source->data.thickness *(source->data.thickness + 2 * source->data.yHeight)*source->data.xLength;
                        break;
                    }
                    case 'y':{
                        volume = M_PI * source->data.thickness *(source->data.thickness + 2 * source->data.zDepth)*source->data.yHeight;

                        break;
                    }
                    case 'z':{
                        volume = M_PI * source->data.thickness *(source->data.thickness + 2 * source->data.xLength)*source->data.zDepth;
                        break;
                    }
                }
            }
            break;
        }
        case sSphere:{
            volume = (4.0/3.0) * M_PI * source->data.xLength * source->data.xLength * source->data.xLength;
            break;
        }
    }
    return volume;
}

inline double getObjectTorque(Object *source, float t){

    Vector3 com = getObjectCOM(source, t);
    return com.x * getObjectWeight(source);
}

inline double getObjectTorqueCOM(Object *source, Vector3 com){
    return com.x * getObjectWeight(source);
}

inline double getObjectWeight(Object *source){
    if(strcmp(source->material.name,WEIGHTMATERIAL)!=0){
        double volume = getObjectVolume(source);
        return volume * source->material.density;
    }
    else{
        //printf("Object Weight: %.2f\n",source->material.density);
        return source->material.density;
    }
}

Vector4 getAverageCOM(ObjectList *list, float t, float *weightDestination){
    Vector3 com = {0};
    Vector4 returnValue;
    float weight = 0, totalWeight = 0;
    ObjectNode *ptr = list->head;
    while(ptr){
        weight = (float)getObjectWeight(ptr->data);
        totalWeight += weight;
        com = Vector3Add(com, Vector3Scale(getObjectCOM(ptr->data,t), weight));
        ptr = ptr->next;
    }
    returnValue.w = com.x;
    com = Vector3Scale(com, 1/totalWeight);
    returnValue.x = com.x;
    returnValue.y = com.y;
    returnValue.z = com.z;
    *weightDestination = totalWeight;
    return returnValue;
}
