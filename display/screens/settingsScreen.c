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

#include "raylib.h"
#include "../drawMain.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;


//----------------------------------------------------------------------------------
// Settings Screen Functions Definition
//----------------------------------------------------------------------------------

// Settings Screen Initialization logic
void InitSettingsScreen(void)
{
    // TODO: Initialize Settings screen variables here!
    framesCounter = 0;
    finishScreen = -1;
}

// Settings Screen Update logic
void UpdateSettingsScreen(void)
{
    // TODO: Update Settings screen variables here!

}

// Settings Screen Draw logic
void DrawSettingsScreen(void)
{
    // TODO: Draw Settings screen here!
    DrawRectangle(100,100,100,100,RED);
}

// Settings Screen Unload logic
void UnloadSettingsScreen(void)
{
    // TODO: Unload Settings screen variables here!
}

// Settings Screen should finish?
int FinishSettingsScreen(void)
{
    return finishScreen;
}