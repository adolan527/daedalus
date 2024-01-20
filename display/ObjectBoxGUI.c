//
// Created by Aweso on 1/16/2024.
//
#include "drawMain.h"



void InitOBGUI(ObjectBoxGUI *source){
    source->companion = NULL;
    
    source->tb[obgName] = InitTextBox((Rectangle){source->pos.x + screenWidth*.005,source->pos.y + screenHeight*.005,screenWidth*.19,screenHeight*.05},20);
    strcpy(source->tb[obgName]->text,"Name");
    source->tb[obgName]->textIndex+=4;

    //Position elements

    source->tb[obgXPosC] = InitTextBox((Rectangle){source->pos.x + screenWidth*.005,source->pos.y + screenHeight*.0875,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgXPosC]->text,"X");
    source->tb[obgXPosC]->textIndex+=1;

    source->tb[obgXPosM] = InitTextBox((Rectangle){source->pos.x + screenWidth*.05,source->pos.y + screenHeight*.0875,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgXPosM]->text,"X P");
    source->tb[obgXPosM]->textIndex+=3;

    source->tb[obgYPos] = InitTextBox((Rectangle){source->pos.x + screenWidth*.095,source->pos.y + screenHeight*.0875,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgYPos]->text,"Y");
    source->tb[obgYPos]->textIndex+=1;

    source->tb[obgZPos] = InitTextBox((Rectangle){source->pos.x + screenWidth*.14,source->pos.y + screenHeight*.0875,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgZPos]->text,"Z");
    source->tb[obgZPos]->textIndex+=1;

    //Size elements

    source->tb[obgXLength] = InitTextBox((Rectangle){source->pos.x + screenWidth*.005,source->pos.y + screenHeight*.15,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgXLength]->text,"X");
    source->tb[obgXLength]->textIndex+=1;

    source->tb[obgYHeight] = InitTextBox((Rectangle){source->pos.x + screenWidth*.05,source->pos.y + screenHeight*.15,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgYHeight]->text,"Y");
    source->tb[obgYHeight]->textIndex+=1;

    source->tb[obgZDepth] = InitTextBox((Rectangle){source->pos.x + screenWidth*.095,source->pos.y + screenHeight*.15,screenWidth*.04,screenHeight*.025},6);
    strcpy(source->tb[obgZDepth]->text,"Z");
    source->tb[obgZDepth]->textIndex+=1;

    //Other

    source->tb[obgThickness] = InitTextBox((Rectangle){source->pos.x + screenWidth*.005 + MeasureTextEx(globalFont,"Thickness:  ",screenHeight/32, GETSPACING(screenHeight/32)).x,
        source->pos.y + screenHeight*.15 + MeasureTextEx(globalFont,"Thickness:  ",screenHeight/32, GETSPACING(screenHeight/32)).y,
        screenWidth*.075,screenHeight*.025},10);
    strcpy(source->tb[obgThickness]->text,"T");
    source->tb[obgThickness]->textIndex+=1;

    source->tb[obgMaterial] = InitTextBox((Rectangle){source->pos.x + screenWidth*.095,source->pos.y + screenHeight*.215,screenWidth*.08,screenHeight*.05},20);
    strcpy(source->tb[obgMaterial]->text,"M");
    source->tb[obgMaterial]->textIndex+=1;



    source->cancelBut = (Button){
            "Cancel",
            (Rectangle){source->pos.x + screenWidth*.105,source->pos.y + screenHeight*.475,screenWidth*.08,screenHeight*0.08},
            theme.black,
            theme.white,
            false,
            false,
            false
    };

    source->materialBut = (Button){
            "Material",
            (Rectangle){source->pos.x + screenWidth*.005,source->pos.y + screenHeight*.215, screenWidth*.085,screenHeight*0.05},
            theme.accent2,
            theme.white,
            false,
            false,
            false
    };

    source->facingBut = (Button){
            "X",
            (Rectangle){source->pos.x + screenWidth*.095,source->pos.y + screenHeight*.27,screenWidth*.08,screenHeight*0.06},
            theme.accent2,
            theme.white,
            false,
            false,
            false
    };

    source->saveBut = (Button){
            "Save",
            (Rectangle){source->pos.x + screenWidth*.01,source->pos.y + screenHeight*.475,screenWidth*.08,screenHeight*0.08},
            theme.accent1,
            theme.white,
            false,
            false,
            false
    };

    source->typeBut = (Button){
            "Rectangle",
            (Rectangle){source->pos.x + screenWidth*.01,source->pos.y + screenHeight*.375,screenWidth*.08,screenHeight*0.08},
            theme.accent2,
            theme.white,
            false,
            false,
            false
    };

    source->deleteBut = (Button){
            "Delete",
            (Rectangle){source->pos.x + screenWidth*.105,source->pos.y + screenHeight*.375,screenWidth*.08,screenHeight*0.08},
            theme.dark,
            theme.white,
            false,
            false,
            false
    };
}

void DrawOBGUI(ObjectBoxGUI *source){
    //x .79, y .025
    DrawRectangle(source->pos.x,source->pos.y,screenWidth*.20,screenHeight*.5725,theme.light);
    DrawRectangleLines(source->pos.x,source->pos.y,screenWidth*.20,screenHeight*.5725,theme.black);

    for(int i = 0; i < OBGUITBCOUNT; i++){
        DrawTextBox(source->tb[i]);
    }

    DrawTextEx(globalFont,"Position XPYZ:",(Vector2){source->pos.x+screenWidth*.005,source->pos.y + screenHeight*.0575},(float)screenHeight/32,GETSPACING(screenHeight/24),theme.black);


    DrawTextEx(globalFont,"Size XYZ:",(Vector2){source->pos.x+screenWidth*.005,source->pos.y + screenHeight*.115},(float)screenHeight/32,GETSPACING(screenHeight/24),theme.black);


    DrawTextEx(globalFont,"Thickness:",(Vector2){source->pos.x+screenWidth*.005,source->pos.y + screenHeight*.1775},(float)screenHeight/32,GETSPACING(screenHeight/24),theme.black);

    DrawTextEx(globalFont,"Facing:",(Vector2){source->pos.x + screenWidth*.005,source->pos.y + screenHeight*.27},(float)screenHeight/22,GETSPACING(screenHeight/14),theme.black);

    DrawButton(&source->saveBut);
    DrawButton(&source->cancelBut);
    DrawButton(&source->materialBut);
    DrawButton(&source->facingBut);
    DrawButton(&source->typeBut);
    DrawButton(&source->deleteBut);


}

void CloseOBGUI(ObjectBoxGUI *source){
    for(int i = 0; i < OBGUITBCOUNT; i++){
        CloseTextBox(source->tb[i]);
    }
    source->companion = NULL;
}

OBGUIRET UpdateOBGUI(ObjectBoxGUI *source){
    for(int i = 0; i < OBGUITBCOUNT; i++){
        if(IsTextBoxActive(source->tb[i])){
            if(IsKeyPressed(KEY_TAB)){
                source->tb[i]->isTyping = false;
                source->tb[i]->text[--source->tb[i]->textIndex] = 0;
                source->tb[(i+1)%OBGUITBCOUNT]->isTyping = true;
                return ISTYPING;
            }
            return ISTYPING;
        }
    }


    if(IsButtonPressed(&source->saveBut) || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))) {
        return DOSAVE;

    }
    if(IsButtonPressed(&source->cancelBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A))){
        return DOCANCEL;
    }

    if(IsButtonPressed(&source->deleteBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D))){
        return DODELETE;
    }

    if(IsButtonPressed(&source->typeBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_T))){
        if(source->typeBut.text[0] == 'R'){
            memset(source->typeBut.text,0,20);
            strcpy(source->typeBut.text,"Cylinder");
        }
        else if(source->typeBut.text[0] == 'C'){
            memset(source->typeBut.text,0,20);
            strcpy(source->typeBut.text,"Sphere");
        }
        else{
            memset(source->typeBut.text,0,20);
            strcpy(source->typeBut.text,"Rectangle");
        }
        return DONOTHING;
    }

    if(IsButtonPressed(&source->materialBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_M))){
        if(source->materialBut.text[0]=='W'){
            memset(source->materialBut.text,0,20);
            strcpy(source->materialBut.text,"Material");

        }
        else{
            memset(source->materialBut.text,0,20);
            strcpy(source->materialBut.text,"Weight");

        }
    }
    if(IsButtonPressed(&source->facingBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F))){
        if(source->facingBut.text[0]=='X'){
            source->facingBut.text[0]='Y';
        }
        else if(source->facingBut.text[0]=='Y'){
            source->facingBut.text[0]='Z';
        }
        else{
            source->facingBut.text[0]='X';
        }
        return DOFACING;
    }

    return DONOTHING;
}

void GetObjFromOBGUI(ObjectBoxGUI *source){

    int x = 0;
    printf("%d\n",x++);
    memset(source->companion, 0, sizeof(Object));

    strcpy(source->companion->name, source->tb[obgName]->text);
    source->companion->xPos.constant = strtod(source->tb[obgXPosC]->text, NULL);
    source->companion->xPos.meter = strtod(source->tb[obgXPosM]->text, NULL);
    source->companion->yPos = strtod(source->tb[obgYPos]->text, NULL);
    source->companion->zPos = strtod(source->tb[obgZPos]->text, NULL);
    source->companion->data.xLength = strtod(source->tb[obgXLength]->text, NULL);
    source->companion->data.yHeight = strtod(source->tb[obgYHeight]->text, NULL);
    source->companion->data.zDepth = strtod(source->tb[obgZDepth]->text, NULL);
    source->companion->data.thickness = strtod(source->tb[obgThickness]->text, NULL);
    printf("%d\n",x++);

    if(source->typeBut.text[0] == 'R'){
        source->companion->type = sRectangle;
    }
    else if(source->typeBut.text[0] == 'C'){
        source->companion->type = sCylinder;
    }
    else{
        source->companion->type = sSphere;
    }

    switch(source->facingBut.text[0]){
        default:
            printf("Unknown facing button value\n");
        case 'X':
            source->companion->data.facing = 'x';
            break;
        case 'Y':
            source->companion->data.facing = 'y';
            break;
        case 'Z':
            source->companion->data.facing = 'z';
            break;
    }
    printf("%d\n",x++);

    if(source->materialBut.text[0]=='W'){
        //weight
        printf("W%d\n",x++);

        source->companion->material.color = BLUE;
        source->companion->material.texture = (Texture2D){0};
        strcpy(source->companion->material.name, "Weight");

        source->companion->material.density = strtod(source->tb[obgMaterial]->text, NULL) / getObjectVolume(source->companion);
    }
    else{
        //material
        printf("M%d\n",x++);

        for(int i = 0; i < TQCMATERIALS_COUNT;i++){
            printf("M%d\n",x++);

            if(tqcMaterials[i].name[0]==0){
                printf("End of materials list\n");
                source->companion->material = tqcMaterials[0];
                return;

            }
            if(strcmp(tqcMaterials[i].name,source->tb[obgMaterial]->text)==0){
                source->companion->material = tqcMaterials[i];
                printf("Successful match:  %s with %s\n",source->tb[obgMaterial]->text,tqcMaterials[i].name);
                return;
            }
            printf("Failed match:  %s with %s\n",source->tb[obgMaterial]->text,tqcMaterials[i].name);

        }
        printf("M%d\n",x++);

    }
}

void GetOBGUIFromObj(ObjectBoxGUI *source){

    strcpy(source->tb[obgName]->text, source->companion->name);
    source->tb[obgName]->textIndex = strlen(source->companion->name);
    sprintf(source->tb[obgXPosC]->text, "%.2f", source->companion->xPos.constant);
    source->tb[obgXPosC]->textIndex = strlen(source->tb[obgXPosC]->text);
    sprintf(source->tb[obgXPosM]->text, "%.2f", source->companion->xPos.meter);
    source->tb[obgXPosM]->textIndex = strlen(source->tb[obgXPosM]->text);
    sprintf(source->tb[obgYPos]->text, "%.2f", source->companion->yPos);
    source->tb[obgYPos]->textIndex = strlen(source->tb[obgYPos]->text);
    sprintf(source->tb[obgZPos]->text, "%.2f", source->companion->zPos);
    source->tb[obgZPos]->textIndex = strlen(source->tb[obgZPos]->text);
    sprintf(source->tb[obgXLength]->text, "%.2f", source->companion->data.xLength);
    source->tb[obgXLength]->textIndex = strlen(source->tb[obgXLength]->text);
    sprintf(source->tb[obgYHeight]->text, "%.2f", source->companion->data.yHeight);
    source->tb[obgYHeight]->textIndex = strlen(source->tb[obgYHeight]->text);
    sprintf(source->tb[obgZDepth]->text, "%.2f", source->companion->data.zDepth);
    source->tb[obgZDepth]->textIndex = strlen(source->tb[obgZDepth]->text);
    sprintf(source->tb[obgThickness]->text, "%.2f", source->companion->data.thickness);
    source->tb[obgThickness]->textIndex = strlen(source->tb[obgThickness]->text);


    //TEMPORARY
    switch(source->companion->type){
        case sRectangle:
            strcpy(source->typeBut.text, "Rectangle");
            break;
        case sCylinder:
            strcpy(source->typeBut.text, "Cylinder");
            break;
        case sSphere:
            strcpy(source->typeBut.text, "Sphere");
            break;
    }

    switch(source->companion->data.facing){
        default:
            printf("Unknown facing button value\n");
        case 'x':
            source->facingBut.text[0] = 'X';
            break;
        case 'y':
            source->facingBut.text[0] = 'Y';
            break;
        case 'z':
            source->facingBut.text[0] = 'Z';
            break;
    }

    if(source->companion->material.name[0] == 'W'){
        //weight
        strcpy(source->materialBut.text, "Weight");
        sprintf(source->tb[obgMaterial]->text, "%.2f", source->companion->material.density * getObjectVolume(source->companion));
    }
    else{
        //material
        strcpy(source->materialBut.text, "Material");
        strcpy(source->tb[obgMaterial]->text, source->companion->material.name);

    }

}