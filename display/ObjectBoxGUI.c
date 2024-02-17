//
// Created by Aweso on 1/16/2024.
//
#include "drawMain.h"

typedef enum{
    obgName,
    obgXPosC,
    obgXPosM,
    obgYPos,
    obgZPos,
    obgXLength,
    obgYHeight,
    obgZDepth,
    obgThickness,
    obgMaterial //10 total
}OBGUITEXTBOXES;

ObjectBoxGUI* InitOBGUI(void){
    ObjectBoxGUI* gui = calloc(1, sizeof(ObjectBoxGUI));
    //printf("%llu bytes allocated for obg\n",sizeof(ObjectBoxGUI ));
    gui->pos = (Vector2){(float)screenWidth * .79f, (float)screenHeight * .025f};

    gui->companion = NULL;

    gui->tb[obgName] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .005, screenWidth * .19, screenHeight * .05}, 20);
    strcpy(gui->tb[obgName]->text, "Name");
    gui->tb[obgName]->textIndex+=4;

    //Position elements

    gui->tb[obgXPosC] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .0875, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgXPosC]->text, "0");
    gui->tb[obgXPosC]->textIndex=0;

    gui->tb[obgXPosM] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .05, gui->pos.y + screenHeight * .0875, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgXPosM]->text, "0");
    gui->tb[obgXPosM]->textIndex=0;

    gui->tb[obgYPos] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .095, gui->pos.y + screenHeight * .0875, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgYPos]->text, "0");
    gui->tb[obgYPos]->textIndex=0;

    gui->tb[obgZPos] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .14, gui->pos.y + screenHeight * .0875, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgZPos]->text, "0");
    gui->tb[obgZPos]->textIndex=0;

    //Size elements

    gui->tb[obgXLength] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .15, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgXLength]->text, "1");
    gui->tb[obgXLength]->textIndex=0;

    gui->tb[obgYHeight] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .05, gui->pos.y + screenHeight * .15, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgYHeight]->text, "1");
    gui->tb[obgYHeight]->textIndex=0;

    gui->tb[obgZDepth] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .095, gui->pos.y + screenHeight * .15, screenWidth * .04, screenHeight * .025}, 6);
    strcpy(gui->tb[obgZDepth]->text, "1");
    gui->tb[obgZDepth]->textIndex=0;

    //Other

    gui->tb[obgThickness] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005 + MeasureTextEx(globalFont, "Thickness:  ", screenHeight / 32, GETSPACING(screenHeight / 32)).x,
                                                    gui->pos.y + screenHeight * .15 + MeasureTextEx(globalFont, "Thickness:  ", screenHeight / 32, GETSPACING(screenHeight / 32)).y,
        screenWidth*.075,screenHeight*.025}, 10);
    strcpy(gui->tb[obgThickness]->text, "0");


    gui->tb[obgMaterial] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .095, gui->pos.y + screenHeight * .215, screenWidth * .08, screenHeight * .05}, 20);
    strcpy(gui->tb[obgMaterial]->text, "M");
    gui->tb[obgMaterial]->textIndex+=1;

    //Buttons
    gui->cancelBut = InitButton((Rectangle){gui->pos.x + screenWidth * .105, gui->pos.y + screenHeight * .475, screenWidth * .08, screenHeight * 0.08}, "Cancel", theme.black);
    gui->materialBut = InitButton((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .215, screenWidth * .085, screenHeight * 0.05}, "Material", theme.accent2);
    gui->facingBut = InitButton((Rectangle){gui->pos.x + screenWidth * .095, gui->pos.y + screenHeight * .27, screenWidth * .08, screenHeight * 0.06}, "X", theme.accent2);
    gui->saveBut = InitButton((Rectangle){gui->pos.x + screenWidth * .01, gui->pos.y + screenHeight * .475, screenWidth * .08, screenHeight * 0.08}, "Save", theme.accent1);
    gui->typeBut = InitButton((Rectangle){gui->pos.x + screenWidth * .01, gui->pos.y + screenHeight * .375, screenWidth * .08, screenHeight * 0.08}, "Rectangle", theme.accent2);
    gui->deleteBut = InitButton((Rectangle){gui->pos.x + screenWidth * .105, gui->pos.y + screenHeight * .375, screenWidth * .08, screenHeight * 0.08}, "Delete", theme.dark);
    return gui;
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

    DrawButton(source->saveBut);
    DrawButton(source->cancelBut);
    DrawButton(source->materialBut);
    DrawButton(source->facingBut);
    DrawButton(source->typeBut);
    DrawButton(source->deleteBut);


}

void CloseOBGUI(ObjectBoxGUI *source){
    for(int i = 0; i < OBGUITBCOUNT; i++){
        CloseTextBox(source->tb[i]);
    }
    source->companion = NULL;
    CloseButton(source->saveBut);
    CloseButton(source->cancelBut);
    CloseButton(source->materialBut);
    CloseButton(source->facingBut);
    CloseButton(source->typeBut);
    CloseButton(source->deleteBut);



    free(source);
    //printf("%llu bytes de-allocated for obg\n",sizeof(ObjectBoxGUI ));


}

GUIRET UpdateOBGUI(ObjectBoxGUI *source){
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

    if(IsKeyPressed(KEY_TAB)){
        source->tb[obgName]->isTyping = true;
        return ISTYPING;
    }


    if(IsButtonPressed(source->saveBut) || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))) {
        return DOSAVE;

    }
    if(IsButtonPressed(source->cancelBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_A))){
        return DOCANCEL;
    }

    if(IsButtonPressed(source->deleteBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D))){
        return DODELETE;
    }

    if(IsButtonPressed(source->typeBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_T))){
        if(source->typeBut->text[0] == 'R'){
            memset(source->typeBut->text,0,20);
            strcpy(source->typeBut->text,"Cylinder");
        }
        else if(source->typeBut->text[0] == 'C'){
            memset(source->typeBut->text,0,20);
            strcpy(source->typeBut->text,"Sphere");
        }
        else{
            memset(source->typeBut->text,0,20);
            strcpy(source->typeBut->text,"Rectangle");
        }
        return DONOTHING;
    }

    if(IsButtonPressed(source->materialBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_M))){
        if(strcmp(source->materialBut->text,WEIGHTMATERIAL)==0){
            memset(source->materialBut->text,0,20);
            strcpy(source->materialBut->text,"Material");

        }
        else{
            memset(source->materialBut->text,0,20);
            strcpy(source->materialBut->text,"Weight");

        }
    }
    if(IsButtonPressed(source->facingBut)|| (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F))){
        if(source->facingBut->text[0]=='X'){
            source->facingBut->text[0]='Y';
        }
        else if(source->facingBut->text[0]=='Y'){
            source->facingBut->text[0]='Z';
        }
        else{
            source->facingBut->text[0]='X';
        }
        return OBG_DOFACING;
    }

    return DONOTHING;
}

void GetObjFromOBGUI(ObjectBoxGUI *source){

    int x = 0;
    char *end = NULL;
    printf("%d\n",x++);
    memset(source->companion, 0, sizeof(Object));

    strcpy(source->companion->name, source->tb[obgName]->text);
    source->companion->xPos.constant = strtod(source->tb[obgXPosC]->text, &end);
    if(end==source->tb[obgXPosC]->text){
        source->companion->xPos.constant = 0;
    }
    source->companion->xPos.meter = strtod(source->tb[obgXPosM]->text, &end);
    if(end==source->tb[obgXPosM]->text){
        source->companion->xPos.meter = 0;
    }
    source->companion->yPos = strtod(source->tb[obgYPos]->text, &end);
    if(end==source->tb[obgYPos]->text){
        source->companion->yPos = 0;
    }
    source->companion->zPos = strtod(source->tb[obgZPos]->text, &end);
    if(end==source->tb[obgZPos]->text){
        source->companion->zPos = 0;
    }
    source->companion->data.xLength = strtod(source->tb[obgXLength]->text, &end);
    if(end==source->tb[obgXLength]->text || source->companion->data.xLength <= 0){
        source->companion->data.xLength = 1;
    }
    source->companion->data.yHeight = strtod(source->tb[obgYHeight]->text, &end);
    if(end==source->tb[obgYHeight]->text || source->companion->data.yHeight <= 0){
        source->companion->data.yHeight = 1;
    }
    source->companion->data.zDepth = strtod(source->tb[obgZDepth]->text, &end);
    if(end==source->tb[obgZDepth]->text || source->companion->data.zDepth <= 0){
        source->companion->data.zDepth = 1;
    }
    source->companion->data.thickness = strtod(source->tb[obgThickness]->text, &end);
    if(end==source->tb[obgThickness]->text){
        source->companion->data.thickness = 0;
    }
    printf("%d\n",x++);

    if(source->typeBut->text[0] == 'R'){
        source->companion->type = sRectangle;
    }
    else if(source->typeBut->text[0] == 'C'){
        source->companion->type = sCylinder;
    }
    else{
        source->companion->type = sSphere;
    }

    switch(source->facingBut->text[0]){
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

    if(source->materialBut->text[0]=='W'){
        //weight
        printf("W%d\n",x++);

        source->companion->material.color = BLUE;
        source->companion->material.texture = (Texture2D){0};
        strcpy(source->companion->material.name, WEIGHTMATERIAL);

        source->companion->material.density = strtod(source->tb[obgMaterial]->text, NULL) / getObjectVolume(source->companion);
    }
    else{
        //material
        printf("M%d\n",x++);
        MaterialNode *ptr = tqcMaterials.head;
        while(ptr){
            printf("M%d\n",x++);

            if(ptr->data->name[0]==0){
                printf("End of materials list\n");
                source->companion->material = *tqcMaterials.head->data;
                return;

            }
            if(strcmp(ptr->data->name,source->tb[obgMaterial]->text)==0){
                source->companion->material = *ptr->data;
                printf("Successful match:  %s with %s\n",source->tb[obgMaterial]->text,ptr->data->name);
                return;
            }
            printf("Failed match:  %s with %s\n",source->tb[obgMaterial]->text,ptr->data->name);

            ptr = ptr->next;
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
            strcpy(source->typeBut->text, "Rectangle");
            break;
        case sCylinder:
            strcpy(source->typeBut->text, "Cylinder");
            break;
        case sSphere:
            strcpy(source->typeBut->text, "Sphere");
            break;
    }

    switch(source->companion->data.facing){
        default:
            printf("Unknown facing button value\n");
        case 'x':
            source->facingBut->text[0] = 'X';
            break;
        case 'y':
            source->facingBut->text[0] = 'Y';
            break;
        case 'z':
            source->facingBut->text[0] = 'Z';
            break;
    }

    if(strcmp(source->companion->material.name,WEIGHTMATERIAL)==0){
        //weight
        strcpy(source->materialBut->text, WEIGHTMATERIAL);
        sprintf(source->tb[obgMaterial]->text, "%.2f", source->companion->material.density * getObjectVolume(source->companion));
    }
    else{
        //material
        strcpy(source->materialBut->text, "Material");
        strcpy(source->tb[obgMaterial]->text, source->companion->material.name);

    }

}