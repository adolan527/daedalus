//
// Created by Aweso on 2/13/2024.
//
#include "drawMain.h"

typedef enum{
    mgName,
    mgDensity,
    mgR,
    mgG,
    mgB
}MATERIALGUITEXTBOXES;

void DefaultMGUI(MaterialGUI *source){
    for(int i = 0; i < MATERIALGUITBCOUNT; i++){
        source->tb[i]->isTyping = false;
        memset(source->tb[i]->text, 0, sizeof(source->tb[i]->textSize));
        source->tb[i]->textIndex = 0;
    }
    strcpy(source->tb[mgName]->text, "Name");
    source->tb[mgName]->textIndex+=4;


    strcpy(source->tb[mgDensity]->text, "Density lbs/in^3");
    source->tb[mgDensity]->textIndex+=15;


    strcpy(source->tb[mgR]->text, "R");
    source->tb[mgR]->textIndex+=1;


    strcpy(source->tb[mgG]->text, "G");
    source->tb[mgG]->textIndex+=1;


    strcpy(source->tb[mgB]->text, "B");
    source->tb[mgB]->textIndex+=1;
    source->companion = NULL;
}

MaterialGUI* InitMGUI(void){
    MaterialGUI* gui = calloc(1, sizeof(MaterialGUI));
    gui->pos = (Vector2){(float)screenWidth * .79f, (float)screenHeight * .025f};

    gui->companion = NULL;

    gui->tb[mgName] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .005, screenWidth * .19, screenHeight * .05}, 20);
    strcpy(gui->tb[mgName]->text, "Name");
    gui->tb[mgName]->textIndex+=4;

    gui->tb[mgDensity] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .065, screenWidth * .19, screenHeight * .05}, 20);
    strcpy(gui->tb[mgDensity]->text, "Density lbs/in^3");
    gui->tb[mgDensity]->textIndex+=15;

    gui->tb[mgR] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .125, screenWidth * .19, screenHeight * .05}, 20);
    strcpy(gui->tb[mgR]->text, "R");
    gui->tb[mgR]->textIndex+=1;

    gui->tb[mgG] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .185, screenWidth * .19, screenHeight * .05}, 20);
    strcpy(gui->tb[mgG]->text, "G");
    gui->tb[mgG]->textIndex+=1;

    gui->tb[mgB] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .245, screenWidth * .19, screenHeight * .05}, 20);
    strcpy(gui->tb[mgB]->text, "B");
    gui->tb[mgB]->textIndex+=1;


    //Buttons
    gui->cancelBut = InitButton((Rectangle){gui->pos.x + screenWidth * .105, gui->pos.y + screenHeight * .475, screenWidth * .08, screenHeight * 0.08}, "Cancel", theme.black);
    gui->saveBut = InitButton((Rectangle){gui->pos.x + screenWidth * .01, gui->pos.y + screenHeight * .475, screenWidth * .08, screenHeight * 0.08}, "Save", theme.accent1);
    gui->deleteBut = InitButton((Rectangle){gui->pos.x + screenWidth * .105, gui->pos.y + screenHeight * .375, screenWidth * .08, screenHeight * 0.08}, "Delete", theme.dark);
    return gui;
}

void DrawMGUI(MaterialGUI *source){
    //x .79, y .025
    DrawRectangle(source->pos.x,source->pos.y,screenWidth*.20,screenHeight*.5725,theme.light);
    DrawRectangleLines(source->pos.x,source->pos.y,screenWidth*.20,screenHeight*.5725,theme.black);

    for(int i = 0; i < MATERIALGUITBCOUNT; i++){
        DrawTextBox(source->tb[i]);
    }

    DrawButton(source->saveBut);
    DrawButton(source->cancelBut);
    DrawButton(source->deleteBut);


}

void CloseMGUI(MaterialGUI *source){
    for(int i = 0; i < MATERIALGUITBCOUNT; i++){
        CloseTextBox(source->tb[i]);
    }
    source->companion = NULL;
    CloseButton(source->saveBut);
    CloseButton(source->cancelBut);
    CloseButton(source->deleteBut);



    free(source);


}

GUIRET UpdateMGUI(MaterialGUI *source){

    for(int i = 0; i < MATERIALGUITBCOUNT; i++){
        if(IsTextBoxActive(source->tb[i])){
            if(IsKeyPressed(KEY_TAB)){
                source->tb[i]->isTyping = false;
                source->tb[i]->text[--source->tb[i]->textIndex] = 0;
                source->tb[(i+1)%MATERIALGUITBCOUNT]->isTyping = true;
                return ISTYPING;
            }
            return ISTYPING;
        }
    }

    if(IsKeyPressed(KEY_TAB)){
        source->tb[mgName]->isTyping = true;
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

    return DONOTHING;

}

void GetMatFromMGUI(MaterialGUI *source, MaterialList *list){

    char *end = NULL;
    bool appendToList = false;
    if(source->companion == NULL){
        source->companion = calloc(1, sizeof(tqcMaterial));
        appendToList = true;
    }

    memset(source->companion, 0, sizeof(tqcMaterial));

    strcpy(source->companion->name, source->tb[mgName]->text);

    source->companion->density = strtod(source->tb[mgDensity]->text, &end);
    if(end==source->tb[mgDensity]->text){
        source->companion->density = 1;
    }


    source->companion->color.r = strtol(source->tb[mgR]->text, &end,10);
    if(end==source->tb[mgR]->text){
        source->companion->color.r = 0;
    }

    source->companion->color.g = strtol(source->tb[mgG]->text, &end,10);
    if(end==source->tb[mgG]->text){
        source->companion->color.g = 0;
    }

    source->companion->color.b = strtol(source->tb[mgB]->text, &end,10);
    if(end==source->tb[mgB]->text){
        source->companion->color.b = 0;
    }

    if(appendToList){
        appendMaterial(list, source->companion);
    }

}

void GetMGUIFromMat(MaterialGUI *source){

    strcpy(source->tb[mgName]->text, source->companion->name);
    source->tb[mgName]->textIndex = strlen(source->companion->name);
    sprintf(source->tb[mgDensity]->text, "%.2f", source->companion->density);
    source->tb[mgDensity]->textIndex = strlen(source->tb[mgDensity]->text);
    sprintf(source->tb[mgR]->text, "%d", source->companion->color.r);
    source->tb[mgR]->textIndex = strlen(source->tb[mgR]->text);
    sprintf(source->tb[mgG]->text, "%d", source->companion->color.g);
    source->tb[mgG]->textIndex = strlen(source->tb[mgG]->text);
    sprintf(source->tb[mgB]->text, "%d", source->companion->color.b);
    source->tb[mgB]->textIndex = strlen(source->tb[mgB]->text);


}
