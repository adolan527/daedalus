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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Button settings = {0};
Button create = {0};
Button open = {0};
const float buttonWidth = 250;
const float buttonHeight = 100;
//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    // TODO: Initialize TITLE screen variables here!
    framesCounter = 0;
    finishScreen = -1;
    create = (Button){"Create New Project",{(screenWidth-buttonWidth)/2,screenHeight/2,buttonWidth,buttonHeight},MAROON,RAYWHITE,false,false};
    open = (Button){"Open Project",{(screenWidth-buttonWidth)/2,screenHeight/2 + 1.5 * buttonHeight,buttonWidth,buttonHeight},MAROON,RAYWHITE,false,false};
    settings = (Button){"Settings",{(screenWidth-buttonWidth)/2,screenHeight/2 + 3 * buttonHeight,buttonWidth,buttonHeight},MAROON,RAYWHITE,false,false};

}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // TODO: Update TITLE screen variables here!

    // Press enter or tap to change to GAMEPLAY screen
    if(IsButtonPressed(&settings)==true){
        finishScreen = SETTINGS;
        return;
    }
    if(IsButtonPressed(&create)==true){
        finishScreen = CREATEPROJECT;
        return;
    }
    if(IsButtonPressed(&open)==true){
        finishScreen = OPENPROJECT;
        return;
    }

}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    // TODO: Draw TITLE screen here!

    DrawRectangleGradientV(0, 0, screenWidth, screenHeight, RAYWHITE,GRAY);

    int fontSize = screenHeight/2;
    int textWidth = MeasureText("Torque Calculator",fontSize);
    while(textWidth+screenWidth/10>screenWidth){
        fontSize-=8;
        textWidth = MeasureText("Torque Calculator",fontSize);
    }
    DrawText("Torque Calculator", screenWidth/2 - textWidth/2,  screenHeight/2 - 1.5 * fontSize, fontSize, DARKGREEN);

    DrawButton(settings);
    DrawButton(create);
    DrawButton(open);
    return;

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