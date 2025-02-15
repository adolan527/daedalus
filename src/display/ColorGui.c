//
// Created by Aweso on 2/18/2024.
//
#include "drawMain.h"

typedef enum{
//white rgb, black rgb, light rgb, dark rgb, accent1 rgb, accent2 rgb
    wR,
    wG,
    wB,
    bR,
    bG,
    bB,
    lR,
    lG,
    lB,
    dR,
    dG,
    dB,
    a1R,
    a1G,
    a1B,
    a2R,
    a2G,
    a2B
}COLORGUITEXTBOXES;
/*
void DefaultMGUI(MaterialGUI *source){
    for(int i = 0; i < COLORGUICOUNT; i++){
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


}*/

ColorGUI* InitCGUI(void){
    ColorGUI* gui = calloc(1, sizeof(ColorGUI));
    gui->pos = (Vector2){(float)screenWidth * .7f, (float)screenHeight * .05f};

    gui->companion = NULL;

    //Textboxes
    for(int i = 0; i < COLORGUICOUNT; i++){
        gui->tb[i] = InitTextBox((Rectangle){gui->pos.x + screenWidth * .005 + (i%3)*screenWidth*0.085, gui->pos.y + screenHeight * .05 + (i/3 * screenHeight * .1), screenWidth * .08, screenHeight * .05}, 4);
        switch(i%3){
            case 0:
                strcpy(gui->tb[i]->text, "R");
                break;
            case 1:
                strcpy(gui->tb[i]->text, "G");
                break;
            case 2:
                strcpy(gui->tb[i]->text, "B");
                break;
        }

    }


    //Buttons
    gui->cancelBut = InitButton((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .625, screenWidth * .1225, screenHeight * 0.08}, "Cancel", theme.black);
    gui->saveBut = InitButton((Rectangle){gui->pos.x + screenWidth * .1325, gui->pos.y + screenHeight * .625, screenWidth * .1225, screenHeight * 0.08}, "Save", theme.accent1);
    gui->deleteBut = InitButton((Rectangle){gui->pos.x + screenWidth * .005, gui->pos.y + screenHeight * .71, screenWidth * .1225, screenHeight * 0.08}, "Delete", theme.dark);
    gui->selectBut = InitButton((Rectangle){gui->pos.x + screenWidth * .1325, gui->pos.y + screenHeight * .71, screenWidth * .1225, screenHeight * 0.08}, "Select", theme.dark);

    return gui;
}

void DrawCGUI(ColorGUI *source){

    DrawRectangle(source->pos.x,source->pos.y,screenWidth*.26,screenHeight*.8,theme.light);
    DrawRectangleLines(source->pos.x,source->pos.y,screenWidth*.26,screenHeight*.8,theme.black);

    for(int i = 0; i < COLORGUICOUNT; i++){
        DrawTextBox(source->tb[i]);
    }
    DrawTextEx(globalFont, "White", (Vector2){source->pos.x + screenWidth * .005, source->pos.y + screenHeight * .005}, screenWidth * .02, 1, theme.black);
    DrawTextEx(globalFont, "Black", (Vector2){source->pos.x + screenWidth * .005, source->pos.y + screenHeight * .105}, screenWidth * .02, 1, theme.black);
    DrawTextEx(globalFont, "Light", (Vector2){source->pos.x + screenWidth * .005, source->pos.y + screenHeight * .205}, screenWidth * .02, 1, theme.black);
    DrawTextEx(globalFont, "Dark", (Vector2){source->pos.x + screenWidth * .005, source->pos.y + screenHeight * .305}, screenWidth * .02, 1, theme.black);
    DrawTextEx(globalFont, "Accent 1", (Vector2){source->pos.x + screenWidth * .005, source->pos.y + screenHeight * .405}, screenWidth * .02, 1, theme.black);
    DrawTextEx(globalFont, "Accent 2", (Vector2){source->pos.x + screenWidth * .005, source->pos.y + screenHeight * .505}, screenWidth * .02, 1, theme.black);

    DrawButton(source->saveBut);
    DrawButton(source->cancelBut);
    DrawButton(source->deleteBut);
    DrawButton(source->selectBut);

}

void CloseCGUI(ColorGUI *source){
    for(int i = 0; i < COLORGUICOUNT; i++){
        CloseTextBox(source->tb[i]);
    }
    source->companion = NULL;
    CloseButton(source->saveBut);
    CloseButton(source->cancelBut);
    CloseButton(source->deleteBut);
    CloseButton(source->selectBut);
    free(source);


}

GUIRET UpdateCGUI(ColorGUI *source){

    for(int i = 0; i < COLORGUICOUNT; i++){
        if(IsTextBoxActive(source->tb[i])){
            if(IsKeyPressed(KEY_TAB)){
                source->tb[i]->isTyping = false;
                source->tb[i]->text[--source->tb[i]->textIndex] = 0;
                source->tb[(i+1)%COLORGUICOUNT]->isTyping = true;
                return ISTYPING;
            }
            return ISTYPING;
        }
    }

    if(IsKeyPressed(KEY_TAB)){
        source->tb[0]->isTyping = true;
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

    if(IsButtonPressed(source->selectBut)){
        return COL_DOCHANGETHEME;
    }
    return DONOTHING;

}

void GetCGUIFromColor(ColorGUI *source){

    sprintf( source->tb[wR]->text, "%d", source->companion->white.r);

    sprintf( source->tb[wG]->text, "%d", source->companion->white.g);

    sprintf( source->tb[wB]->text, "%d", source->companion->white.b);

    sprintf( source->tb[bR]->text, "%d", source->companion->black.r);

    sprintf( source->tb[bG]->text, "%d", source->companion->black.g);

    sprintf( source->tb[bB]->text, "%d", source->companion->black.b);

    sprintf( source->tb[lR]->text, "%d", source->companion->light.r);

    sprintf( source->tb[lG]->text, "%d", source->companion->light.g);

    sprintf( source->tb[lB]->text, "%d", source->companion->light.b);

    sprintf( source->tb[dR]->text, "%d", source->companion->dark.r);

    sprintf( source->tb[dG]->text, "%d", source->companion->dark.g);

    sprintf( source->tb[dB]->text, "%d", source->companion->dark.b);

    sprintf(source->tb[a1R]->text, "%d", source->companion->accent1.r);

    sprintf(source->tb[a1G]->text, "%d", source->companion->accent1.g);

    sprintf(source->tb[a1B]->text, "%d", source->companion->accent1.b);

    sprintf(source->tb[a2R]->text, "%d", source->companion->accent2.r);

    sprintf(source->tb[a2G]->text, "%d", source->companion->accent2.g);

    sprintf(source->tb[a2B]->text, "%d", source->companion->accent2.b);

    for(int i = 0; i < COLORGUICOUNT; i++){
        source->tb[i]->textIndex = (int)strlen(source->tb[i]->text);
    }

}

void GetColorFromCGUI(ColorGUI *source){
    char *ptr = NULL;
    memset(source->companion, 0, sizeof(ColorPalette));

    source->companion->white.r = strtol(source->tb[wR]->text, &ptr,10);
    if(ptr==source->tb[wR]->text){
        source->companion->white.r = 0;
    }
    source->companion->white.g = strtol(source->tb[wG]->text, &ptr,10);
    if(ptr==source->tb[wG]->text){
        source->companion->white.g = 0;
    }
    source->companion->white.b = strtol(source->tb[wB]->text, &ptr,10);
    if(ptr==source->tb[wB]->text){
        source->companion->white.b = 0;
    }

    source->companion->black.r = strtol(source->tb[bR]->text, &ptr,10);
    if(ptr==source->tb[bR]->text){
        source->companion->black.r = 0;
    }
    source->companion->black.g = strtol(source->tb[bG]->text, &ptr,10);
    if(ptr==source->tb[bG]->text){
        source->companion->black.g = 0;
    }
    source->companion->black.b = strtol(source->tb[bB]->text, &ptr,10);
    if(ptr==source->tb[bB]->text){
        source->companion->black.b = 0;
    }

    source->companion->light.r = strtol(source->tb[lR]->text, &ptr,10);
    if(ptr==source->tb[lR]->text){
        source->companion->light.r = 0;
    }
    source->companion->light.g = strtol(source->tb[lG]->text, &ptr,10);
    if(ptr==source->tb[lG]->text){
        source->companion->light.g = 0;
    }
    source->companion->light.b = strtol(source->tb[lB]->text, &ptr,10);
    if(ptr==source->tb[lB]->text){
        source->companion->light.b = 0;
    }

    source->companion->dark.r = strtol(source->tb[dR]->text, &ptr,10);
    if(ptr==source->tb[dR]->text){
        source->companion->dark.r = 0;
    }
    source->companion->dark.g = strtol(source->tb[dG]->text, &ptr,10);
    if(ptr==source->tb[dG]->text){
        source->companion->dark.g = 0;
    }
    source->companion->dark.b = strtol(source->tb[dB]->text, &ptr,10);
    if(ptr==source->tb[dB]->text){
        source->companion->dark.b = 0;
    }

    source->companion->accent1.r = strtol(source->tb[a1R]->text, &ptr,10);
    if(ptr==source->tb[a1R]->text){
        source->companion->accent1.r = 0;
    }
    source->companion->accent1.g = strtol(source->tb[a1G]->text, &ptr,10);
    if(ptr==source->tb[a1G]->text){
        source->companion->accent1.g = 0;
    }
    source->companion->accent1.b = strtol(source->tb[a1B]->text, &ptr,10);
    if(ptr==source->tb[a1B]->text){
        source->companion->accent1.b = 0;
    }

    source->companion->accent2.r = strtol(source->tb[a2R]->text, &ptr,10);
    if(ptr==source->tb[a2R]->text){
        source->companion->accent2.r = 0;
    }
    source->companion->accent2.g = strtol(source->tb[a2G]->text, &ptr,10);
    if(ptr==source->tb[a2G]->text){
        source->companion->accent2.g = 0;
    }
    source->companion->accent2.b = strtol(source->tb[a2B]->text, &ptr,10);
    if(ptr==source->tb[a2B]->text){
        source->companion->accent2.b = 0;
    }

    //make all of the alpha values 255
    source->companion->white.a = 255;
    source->companion->black.a = 255;
    source->companion->light.a = 255;
    source->companion->dark.a = 255;
    source->companion->accent1.a = 255;
    source->companion->accent2.a = 255;



}
