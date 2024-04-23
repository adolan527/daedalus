/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Settings Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "../drawMain.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
//make the above buttons into pointers
static Button *resolutionBut, *fullscreenBut, *windowBut, *borderlessBut, *applyBut, *backBut, *doLogoBut, *materialsBut;
static const int resolutionPresetCount = 7;
static const int presetResolutions[] = {720,768,900,1080,1152,2160,2304};
static int resolutionIndex = 0;
static char newWM = 0;
static char newDoLogo = 't';
//----------------------------------------------------------------------------------
// Settings Screen Functions Definition
//----------------------------------------------------------------------------------

// Settings Screen Initialization logic
void InitSettingsScreen(void)
{
    // TODO: Initialize Settings screen variables here!
    framesCounter = 0;
    finishScreen = -1;
    newWM = windowMode;
    newDoLogo = drawLogo;
    for(int i = 0;i<resolutionPresetCount;i++){
        if(screenHeight == presetResolutions[i]){
            resolutionIndex = i;
            break;
        }
        else{
            resolutionIndex = 2;
        }
    }
    doLogoBut = InitButton((Rectangle){screenWidth*0.05 + MeasureTextEx(globalFont,"Do Logo Animation: ",screenHeight/16,GETSPACING(screenHeight/24)).x, (screenHeight * .49), screenHeight/12, screenHeight/12},
               "",
               theme.dark);
    doLogoBut->isToggle = true;

    backBut = InitButton((Rectangle){screenWidth*0.95 - screenWidth/6, screenHeight*0.825,screenWidth/6,screenHeight*0.125},
                         "Back",
                         theme.black);


    applyBut = InitButton((Rectangle){screenWidth*0.95 - screenWidth/3 - screenWidth/60, screenHeight*0.825,screenWidth/6,screenHeight*0.125},
                          "Apply",
                          theme.accent2);

    resolutionBut = InitButton((Rectangle){screenWidth*0.05 + MeasureTextEx(globalFont,"Resolution: ",screenHeight/12,GETSPACING(screenHeight/12)).x, screenHeight/12, screenWidth/4, screenHeight/8},
                               "Resolution",
                               theme.dark);

    snprintf(resolutionBut->text,15,"%dx%d",screenWidth,screenHeight);

    fullscreenBut = InitButton((Rectangle){screenWidth * 0.05, screenWidth/6, screenWidth * 23/80, screenHeight/8},
                               "Fullscreen",
                               theme.accent1);
    fullscreenBut->isToggle = true;

    windowBut = InitButton((Rectangle){screenWidth * 0.05 + screenWidth * 23/80 + screenWidth/30, screenWidth/6, screenWidth/4, screenHeight/8},
                           "Windowed",
                           theme.accent1);
    windowBut->isToggle = true;

    borderlessBut = InitButton((Rectangle){screenWidth * 0.05 + screenWidth * 23/40 + screenWidth/30, screenWidth/6, screenWidth/4, screenHeight/8},
                               "Borderless",
                               theme.accent1);
    borderlessBut->isToggle = true;

    materialsBut = InitButton((Rectangle){screenWidth * 0.05, screenHeight * 0.6, screenWidth * 0.15, screenHeight*0.15},
                              "Materials",theme.accent1);

    switch(windowMode){
        case 'f': PressButton(fullscreenBut); break;
        case 'w': PressButton(windowBut); break;
        case 'b': PressButton(borderlessBut);{} break;
    }
    if(newDoLogo == 't')PressButton(doLogoBut);
}

// Settings Screen Update logic
void UpdateSettingsScreen(void)
{
    // TODO: Update Settings screen variables here!
    if(IsButtonPressed(doLogoBut)){
        if(newDoLogo == 't')newDoLogo = 'f';
        else{newDoLogo = 't';}
    }
    if(IsButtonPressed(resolutionBut)){
        if(resolutionIndex == resolutionPresetCount-1){
            resolutionIndex = 0;
        }
        else{
            resolutionIndex++;
        }
        snprintf(resolutionBut->text,15,"%dx%d",presetResolutions[resolutionIndex] * 16/9,presetResolutions[resolutionIndex]);

    }
    if(IsButtonPressed(fullscreenBut)){
        if(newWM =='f' && fullscreenBut->isPressed == false){
            PressButton(fullscreenBut);
        }
        else{
            newWM = 'f';
            if(windowBut->isPressed)UnPressButton(windowBut);
            if(borderlessBut->isPressed)UnPressButton(borderlessBut);
        }

    }
    else if(IsButtonPressed(windowBut)){
        if(newWM =='w' && windowBut->isPressed == false){
            PressButton(windowBut);
        }
        else {
            newWM = 'w';
            if (fullscreenBut->isPressed)UnPressButton(fullscreenBut);
            if (borderlessBut->isPressed)UnPressButton(borderlessBut);
        }
    }
    else if(IsButtonPressed(borderlessBut)){
        if(newWM =='b' && borderlessBut->isPressed == false){
            PressButton(borderlessBut);
        }
        else {
            newWM = 'b';
            if (windowBut->isPressed)UnPressButton(windowBut);
            if (fullscreenBut->isPressed)UnPressButton(fullscreenBut);

        }
    }
    if(IsButtonPressed(backBut) || IsMouseButtonPressed(MOUSE_BUTTON_SIDE))finishScreen = TITLE;



    if(IsButtonPressed(applyBut)){
        if(presetResolutions[resolutionIndex] != screenHeight || newWM != windowMode || newDoLogo != drawLogo){
            if(newWM == 'b'){
                makeConfig(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()),newWM,newDoLogo,themeIndex);
            }
            else{
                makeConfig(presetResolutions[resolutionIndex]*16/9,presetResolutions[resolutionIndex],newWM,newDoLogo,themeIndex);

            }
            finishScreen = REINIT;
        }

    }

    if(IsButtonPressed(materialsBut)){
        finishScreen = MATERIALS;
    }

}

// Settings Screen Draw logic
void DrawSettingsScreen(void)
{
    // TODO: Draw Settings screen here!
    DrawRectangleGradientV(0,0,screenWidth,screenHeight,theme.light,theme.white);

    DrawButton(resolutionBut);
    DrawButton(fullscreenBut);
    DrawButton(borderlessBut);
    DrawTextEx(globalFont,"Do Logo Animation:",(Vector2){screenWidth*0.05,screenHeight*0.5},screenHeight/16,GETSPACING(screenHeight/24),theme.accent1);
    DrawButton(doLogoBut);
    DrawButton(materialsBut);
    if(doLogoBut->isPressed == false){
        DrawRectangle(doLogoBut->rect.x + doLogoBut->rect.width * 0.1,
                      doLogoBut->rect.y + doLogoBut->rect.height * 0.1,
                      doLogoBut->rect.width * 0.8,
                      doLogoBut->rect.height * 0.8,
                      theme.white);
    }

    DrawButton(windowBut);
    DrawButton(backBut);
    DrawButton(applyBut);
    switch(newWM){
        case 'f': DrawRectangleLinesEx(fullscreenBut->rect,5,theme.accent2); break;
        case 'w': DrawRectangleLinesEx(windowBut->rect,5,theme.accent2); break;
        case 'b': DrawRectangleLinesEx(borderlessBut->rect,5,theme.accent2); break;
        default: break;
    }
    DrawTextEx(globalFont,"Resolution:",(Vector2){screenWidth*0.05,screenHeight*0.1},screenHeight/12,GETSPACING(screenHeight/12),theme.accent1);

}

// Settings Screen Unload logic
void UnloadSettingsScreen(void)
{
    // TODO: Unload Settings screen variables here!
    CloseButton(resolutionBut);
    CloseButton(fullscreenBut);
    CloseButton(windowBut);
    CloseButton(borderlessBut);
    CloseButton(applyBut);
    CloseButton(backBut);
    CloseButton(doLogoBut);
    CloseButton(materialsBut);

}

// Settings Screen should finish?
int FinishSettingsScreen(void)
{
    return finishScreen;
}