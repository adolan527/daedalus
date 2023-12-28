/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
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

#include "raylib.h"
#include "../drawMain.h"
#include <stdio.h>
//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
typedef struct{
    Vector2 v1,v2,v3,c;
    int xDir,yDir,spinDir,speed,omega;
    float d;
}TITLE_Triangle;

static int framesCounter = 0;
static int finishScreen = 0;
static Button settingsBut = {0};
static Button createBut = {0};
static Button openBut = {0};
static float buttonHeight = 100;
static float buttonWidth = 250;


#define triangleCount 10
TITLE_Triangle triangles[triangleCount];
//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = -1;
    buttonHeight = screenHeight/9;
    buttonWidth = buttonHeight * 2.5;
    createBut = (Button){"Create New Project", {(screenWidth - buttonWidth*1.25) / 2, screenHeight / 2 - 0.25 * buttonHeight, buttonWidth*1.25, buttonHeight*1.25}, theme.accent2, theme.white, false, false, false};
    openBut = (Button){"Open Project", {(screenWidth-buttonWidth)/2,screenHeight/2 + 1.5 * buttonHeight,buttonWidth,buttonHeight}, theme.accent2, theme.white, false, false, false};
    settingsBut = (Button){"Settings", {(screenWidth - buttonWidth) / 2, screenHeight / 2 + 3 * buttonHeight, buttonWidth, buttonHeight}, theme.accent2, theme.white, false, false, false};

    for(int i = 0;i<triangleCount;i++){
        triangles[i].d = GetRandomValue(screenWidth/45,screenWidth/15);
        triangles[i].c.y = GetRandomValue(triangles[i].d,screenHeight-triangles[i].d);
        triangles[i].c.x = GetRandomValue(triangles[i].d,screenWidth-triangles[i].d);
        triangles[i].xDir=0;
        triangles[i].yDir=0;
        triangles[i].spinDir=0;
        while(triangles[i].xDir==0)triangles[i].xDir = GetRandomValue(-1,1);
        while(triangles[i].yDir==0)triangles[i].yDir = GetRandomValue(-1,1);
        while(triangles[i].spinDir==0)triangles[i].spinDir = GetRandomValue(-1,1);

        triangles[i].speed= GetRandomValue(1,5);
        triangles[i].omega= GetRandomValue(2,10);

        int offset = GetRandomValue(0,700);

        triangles[i].v1.x = cosf(triangles[i].spinDir*(float)offset/100 + PI/2) * triangles[i].d + triangles[i].c.x;
        triangles[i].v1.y = sinf(triangles[i].spinDir*(float)offset/100+ PI/2) * triangles[i].d + triangles[i].c.y;

        triangles[i].v2.x = cosf(triangles[i].spinDir*(float)offset/100 + 7 *PI/6) * triangles[i].d + triangles[i].c.x;
        triangles[i].v2.y = sinf(triangles[i].spinDir*(float)offset/100 + 7 *PI/6) * triangles[i].d + triangles[i].c.y;

        triangles[i].v3.x = cosf(triangles[i].spinDir*(float)offset/100 + 11 *PI/6) * triangles[i].d + triangles[i].c.x;
        triangles[i].v3.y = sinf(triangles[i].spinDir*(float)offset/100 + 11 *PI/6) * triangles[i].d + triangles[i].c.y;
    }



}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!
    const Vector2 tl = {0,0};
    const Vector2 tr = { screenWidth,0};
    const Vector2 bl = {0,screenHeight};
    const Vector2 br = {screenWidth,screenHeight};

    for(int i = 0;i<triangleCount;i++){
        triangles[i].c.x += triangles[i].xDir*triangles[i].speed;
        triangles[i].c.y += triangles[i].yDir*triangles[i].speed;

        triangles[i].v1.x = cosf(triangles[i].spinDir*(float)framesCounter/100 * triangles[i].omega + PI/2) * triangles[i].d + triangles[i].c.x;
        triangles[i].v1.y = sinf(triangles[i].spinDir*(float)framesCounter/100 * triangles[i].omega + PI/2) * triangles[i].d + triangles[i].c.y;

        triangles[i].v2.x = cosf(triangles[i].spinDir*(float)framesCounter/100 * triangles[i].omega + 7 *PI/6) * triangles[i].d + triangles[i].c.x;
        triangles[i].v2.y = sinf(triangles[i].spinDir*(float)framesCounter/100 * triangles[i].omega + 7 *PI/6) * triangles[i].d + triangles[i].c.y;

        triangles[i].v3.x = cosf(triangles[i].spinDir*(float)framesCounter/100 * triangles[i].omega+ 11 *PI/6) * triangles[i].d + triangles[i].c.x;
        triangles[i].v3.y = sinf(triangles[i].spinDir*(float)framesCounter/100 * triangles[i].omega + 11 *PI/6) * triangles[i].d + triangles[i].c.y;


        if(     CheckCollisionLines(triangles[i].v1,triangles[i].v2,tl,tr,NULL)||
                CheckCollisionLines(triangles[i].v1,triangles[i].v2,br,bl,NULL)||
                CheckCollisionLines(triangles[i].v2,triangles[i].v3,tl,tr,NULL)||
                CheckCollisionLines(triangles[i].v2,triangles[i].v3,br,bl,NULL)||
                CheckCollisionLines(triangles[i].v3,triangles[i].v1,tl,tr,NULL)||
                CheckCollisionLines(triangles[i].v3,triangles[i].v1,br,bl,NULL)){
            triangles[i].yDir *= -1;
        }

        if(     CheckCollisionLines(triangles[i].v1,triangles[i].v2,tr,br,NULL)||
                CheckCollisionLines(triangles[i].v1,triangles[i].v2,bl,tl,NULL)||
                CheckCollisionLines(triangles[i].v2,triangles[i].v3,tr,br,NULL)||
                CheckCollisionLines(triangles[i].v2,triangles[i].v3,bl,tl,NULL)||
                CheckCollisionLines(triangles[i].v3,triangles[i].v1,tr,br,NULL)||
                CheckCollisionLines(triangles[i].v3,triangles[i].v1,bl,tl,NULL)){
            triangles[i].xDir *= -1;
        }
    }







    // Press enter or tap to change to GAMEPLAY screen
    if(IsButtonPressed(&settingsBut) == true){
        finishScreen = SETTINGS;
        return;
    }
    if(IsButtonPressed(&createBut) == true){
        finishScreen = CREATEPROJECT;
        return;
    }
    if(IsButtonPressed(&openBut)==true){
        finishScreen = OPENPROJECT;
        return;
    }
    framesCounter++;

}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!

    DrawRectangle(0, 0, screenWidth, screenHeight, theme.white);
    for(int i = 0; i<triangleCount;i++){

        DrawLineEx(triangles[i].v1,triangles[i].v2,5,theme.light);
        DrawLineEx(triangles[i].v2,triangles[i].v3,5,theme.light);
        DrawLineEx(triangles[i].v3,triangles[i].v1,5,theme.light);
    }
    int fontSize = screenHeight/2;
    int textWidth = MeasureText("Torque Calculator",fontSize);
    while(textWidth+screenWidth/10>screenWidth){
        fontSize-=8;
        textWidth = MeasureText("Torque Calculator",fontSize);
    }
    DrawText("Torque Calculator", screenWidth/2 - textWidth/2,  screenHeight/2 - 1.5 * fontSize, fontSize, theme.accent1);

    DrawButton(&settingsBut);
    DrawButton(&createBut);
    DrawButton(&openBut);



}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{
    // TODO: Unload TITLE screen variables here!
}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}