/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   ProjectMain Screen Functions Definitions (Init, Update, Draw, Unload)
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
// ProjectMain Screen Functions Definition
//----------------------------------------------------------------------------------

// ProjectMain Screen Initialization logic
void InitProjectMainScreen(void)
{
    // TODO: Initialize ProjectMain screen variables here!
    framesCounter = 0;
    finishScreen = -1;
}

// ProjectMain Screen Update logic
void UpdateProjectMainScreen(void)
{
    // TODO: Update ProjectMain screen variables here!
}

// ProjectMain Screen Draw logic
void DrawProjectMainScreen(void)
{
    // TODO: Draw ProjectMain screen here!
}

// ProjectMain Screen Unload logic
void UnloadProjectMainScreen(void)
{
    // TODO: Unload ProjectMain screen variables here!
}

// ProjectMain Screen should finish?
int FinishProjectMainScreen(void)
{
    return finishScreen;
}