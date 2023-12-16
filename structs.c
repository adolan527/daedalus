//
// Created by Aweso on 11/2/2023.
//

#include "structs.h"




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

void stringifyRectangle(Rectangle *rectangle, char *destString){
    char buffer[75] = "";

    sprintf(buffer,"Length (x): %.2f | Width (y): %.2f | Height (z): %.2f"
            ,rectangle->xLength,rectangle->yWidth,rectangle->zHeight);

    strncpy(destString,buffer,75);
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
    for(int i = 0;i<COEFF_COUNT;i++){
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

int decodeParametric(char *string, Parametric *destFunction){
    char cleanString[50];
    char *dummy;
    int offset = 0;
    double value = 0;
    double meterSign = 1;

    removeWhitespace(string, cleanString);

    destFunction->constant = 0;
    destFunction->meter = 0;

    for(int i = 0;i<100;i++){
        if(cleanString[i]=='+' || cleanString[i]=='-'){
            if(cleanString[i]== '-' && i !=0) meterSign = -1;
            dummy = cleanString + i - 1;
            value = strtod(cleanString,&dummy);
            if(value == 0){
                return 1;
            }
            destFunction->constant = value;
            offset = i + 1;


        }
        else if(cleanString[i]==0){
            dummy = cleanString + i;
            value = strtod(cleanString,&dummy);
            if(value == 0 && i>1){
                return 1;
            }
            destFunction->constant = value;
            destFunction->meter = 0;
            i=100;
        }
        else if(cleanString[i]=='t'){
            if(cleanString[i-1]=='+'){
                value = 1;
            }
            else if(cleanString[i-1]=='-'){
                value = -1;
            }
            else{
                dummy = cleanString + i - 1;
                value = strtod(cleanString+offset,&dummy);
                if(value == 0){
                    return 1;
                }

            }
            destFunction->meter = value * meterSign;
            i=100;
        }
    }
    //printf("Constant: %lf, Meter: %lf\n",destFunction->constant,destFunction->meter);
    return 0;
}

int decodePolynomial(char *string, Polynomial *destFunction){



}

double computePolynomial(Polynomial *function, double input){
    double sum = 0;
    for(int i = 0;i<COEFF_COUNT;i++){
        if(function->coefficients[i]!=0){
            sum += function->coefficients[i] * pow(input,(function->order - i));
        }
    }
    if(sum==NAN)return 0;
    return sum;
}

void printObject(Object *current){
    char buffer[75];
    printf("%s:\n",current->name);
    stringifyParametric(&current->x_start,buffer);
    printf("Start: %s | ",buffer);
    stringifyParametric(&current->x_end,buffer);
    printf("End: %s\n",buffer);
    printf("Density: %.2lf\n",current->density);
    stringifyPolynomial(&current->area,buffer);
    printf("Area: %s\n",buffer);
    switch(current->shape){
        case Rect:
            stringifyRectangle(current->shapeData,buffer);
            printf("Rectangle:\n%s",buffer);
            break;
        case RectTube:
            break;
        default:
            break;
    }

}


