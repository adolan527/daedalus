//
// Created by Aweso on 12/23/2023.
//
/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   OpenProject Screen Functions Definitions (Init, Update, Draw, Unload)
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
static int finishScreen = -1;
static Button projectButtons[MAX_PROJECT_COUNT] = {0};
static char * projectNames;
static float buttonHeight = 100;
static float buttonWidth = 250;
static float bigButtonHeight = 100;
static float bigButtonWidth = 250;
static Button deleteBut, newBut, backBut, confirmDeleteBut, cancelDeleteBut, confirmNewBut, cancelNewBut;
static int cursorCounter = 0;

static int tooltipIndex = 0;
#define MAXTOOLTIPTEXTSIZE 300
static char tooltipText[MAXTOOLTIPTEXTSIZE] = {0};
const static int tooltipWait = 50;
static float tooltipHeight = 200, tooltipWidth = 500;
static int tooltipRows = 6;
static bool inDeleteMode = false;
static float deleteCrosshairDistance, deleteCrosshairThickness;
static bool inConfirmDeleteMode = false;
static int deleteIndex = 0;

static bool inNewProjectMode = false;
static TextBox *newProjectName =NULL, *newProjectNotes=NULL;





void initProjectButtons(){
    projectNames = getProjectNames();
   for(int i = 0;i < projectCount;i++){
        strncpy(projectButtons[i].text,&projectNames[i*NAMESIZE],NAMESIZE);
        projectButtons[i].color = theme.dark;
        projectButtons[i].textColor = theme.white;
        projectButtons[i].isSelected = false;
        projectButtons[i].isPressed = false;
        projectButtons[i].isToggle = false;
        projectButtons[i].rect.x = screenWidth*0.05 + (buttonWidth + screenWidth* 9.0f/320.0f)*(i%5);
        projectButtons[i].rect.y = screenHeight*0.05 + (i/5) * (buttonHeight*1.25);
        projectButtons[i].rect.width = buttonWidth;
        projectButtons[i].rect.height = buttonHeight;
        //printf("x:%f, y:%f, w:%f, h:%f\n",projectButtons[i].rect.x,projectButtons[i].rect.y,projectButtons[i].rect.width,projectButtons[i].rect.height);
    }

}
//----------------------------------------------------------------------------------
// OpenProject Screen Functions Definition
//----------------------------------------------------------------------------------

// OpenProject Screen Initialization logic
void InitOpenProjectScreen(void)
{
    // TODO: Initialize OpenProject screen variables here!
    inNewProjectMode = false;
    inDeleteMode = false;
    inConfirmDeleteMode = false;
    cursorCounter = 0;
    tooltipIndex = 0;
    deleteIndex = -1;
    memset(tooltipText,0,MAXTOOLTIPTEXTSIZE);
    framesCounter = 0;
    finishScreen = -1;
    buttonHeight = screenHeight/9;
    buttonWidth = screenWidth * 63.0f/400.0f;
    tooltipHeight = buttonHeight * 2;
    tooltipWidth = buttonWidth * 2;
    tooltipRows = (int)(tooltipHeight * (6.0f/170.0f));
    deleteCrosshairDistance = screenHeight/50;
    deleteCrosshairThickness = deleteCrosshairDistance/4;
    initProjectButtons();
    bigButtonHeight = 2 * buttonHeight;
    bigButtonWidth = screenWidth * 67/240;

    newBut = (Button){
        "New Project",
        (Rectangle){screenWidth*0.05,screenHeight*0.75,bigButtonWidth,bigButtonHeight},
        theme.accent1,
        theme.white,
        false,
        false,
        false

    };
    deleteBut = (Button){
            "Delete Project",
            (Rectangle){screenWidth*0.05 + bigButtonWidth + screenWidth/32,screenHeight*0.75,bigButtonWidth,bigButtonHeight},
            theme.accent2,
            theme.white,
            false,
            false,
            false
    };
    backBut = (Button){
            "Back",
            (Rectangle){screenWidth*0.05 + 2*(bigButtonWidth + screenWidth/32),screenHeight*0.75,bigButtonWidth,bigButtonHeight},
            theme.black,
            theme.white,
            false,
            false,
            false
    };
    confirmDeleteBut = (Button){
        "Confirm Delete",
        (Rectangle){screenWidth*.49 - bigButtonWidth,screenHeight*0.5 - bigButtonHeight/2,bigButtonWidth,bigButtonHeight},
        theme.accent1,
        theme.white,
        false,
        false,
        false
    };
    cancelDeleteBut = (Button){
            "Cancel Delete",
            (Rectangle){screenWidth*.51,screenHeight*0.5 - bigButtonHeight/2,bigButtonWidth,bigButtonHeight},
            theme.accent2,
            theme.white,
            false,
            false,
            false
    };

    confirmNewBut = (Button){
            "Confirm New",
            (Rectangle){screenWidth*.49 - bigButtonWidth,screenHeight*0.55,bigButtonWidth,bigButtonHeight},
            theme.accent1,
            theme.white,
            false,
            false,
            false
    };

    cancelNewBut = (Button){
            "Cancel New",
            (Rectangle){screenWidth*.51,screenHeight*0.55,bigButtonWidth,bigButtonHeight},
            theme.accent2,
            theme.white,
            false,
            false,
            false
    };
}

// OpenProject Screen Update logic
void UpdateOpenProjectScreen(void)
{
    // TODO: Update OpenProject screen variables here!

    bool isAButtonSelected = false;
    if(inConfirmDeleteMode){
        if(IsButtonPressed(&confirmDeleteBut)){
            printf("Deleting: %s. %d\n",projectButtons[deleteIndex].text,deleteProject(projectButtons[deleteIndex].text));


            inConfirmDeleteMode = false;
            inDeleteMode = false;
            deleteIndex = -1;
            initProjectButtons();
        }
        if(IsButtonPressed(&cancelDeleteBut)){
            inConfirmDeleteMode = false;
            inDeleteMode = false;
            deleteIndex = -1;
        }
        return;
    }

    if(inNewProjectMode){
        IsTextBoxActive(newProjectName);
        IsTextBoxActive(newProjectNotes);
        if(IsButtonPressed(&cancelNewBut) == true){
            inNewProjectMode = false;
            CloseTextBox(newProjectName);
            CloseTextBox(newProjectNotes);
        }
        if(IsButtonPressed(&confirmNewBut) == true){
            if(createProject(newProjectName->text,newProjectNotes->text)==1){
                printf("Failed to create project\n");
            }
            else{
                initProjectButtons();
                inNewProjectMode = false;
                CloseTextBox(newProjectName);
                CloseTextBox(newProjectNotes);
            }


        }
        return;

    }

    for(int i = 0;i<projectCount;i++){
        if(IsButtonPressed(&projectButtons[i])){
            if(inDeleteMode){
                inConfirmDeleteMode = true;
                inDeleteMode = false;
                deleteIndex = i;
            }
            else{
                finishScreen = PROJECTMAIN;
                openProject(projectButtons[i].text);
            }

        }
        if(projectButtons[i].isSelected){
            isAButtonSelected = true;
            tooltipIndex = i;
        }
    }
    if(isAButtonSelected)cursorCounter++;
    else {cursorCounter = 0;}

    if(cursorCounter>=tooltipWait && tooltipText[0] == 0){
        previewProjectInfo(tooltipText,MAXTOOLTIPTEXTSIZE,projectButtons[tooltipIndex].text);
    }
    else if(cursorCounter < tooltipWait){
        memset(tooltipText,0,MAXTOOLTIPTEXTSIZE);
    }

    if(IsButtonPressed(&newBut) && inNewProjectMode == false){
        inNewProjectMode = true;
        newProjectName = InitTextBox((Rectangle){screenWidth * .2, screenHeight * .225, screenWidth*0.6,screenHeight*0.15},NAMESIZE);
        newProjectNotes = InitTextBox((Rectangle){screenWidth * .2, screenHeight * .375, screenWidth*0.6,screenHeight*0.15},500);
    }



    if(IsButtonPressed(&deleteBut)){
        if(inDeleteMode){
            inDeleteMode = false;
        }
        else{
            inDeleteMode = true;
        }
    }
    if(IsButtonPressed(&backBut) || IsMouseButtonPressed(MOUSE_BUTTON_SIDE)){
        finishScreen = TITLE;
    }
}

// OpenProject Screen Draw logic
void DrawOpenProjectScreen(void)
{
    // TODO: Draw OpenProject screen here!
    DrawRectangle(0,0,screenWidth,screenHeight,theme.light);
    for(int i = 0;i<projectCount;i++){
        DrawButton(&projectButtons[i]);
    }

    DrawButton(&newBut);
    DrawButton(&deleteBut);
    DrawButton(&backBut);

    if(inConfirmDeleteMode){
        DrawRectangle(screenWidth*.15,screenHeight*.2,screenWidth*.7,screenHeight*.6,theme.black);
        DrawRectangleLines(screenWidth*.15,screenHeight*.2,screenWidth*.7,screenHeight*.6,theme.white);
        DrawText("Are you sure you want to delete this project?",screenWidth/2 - MeasureText("Are you sure you want to delete this project?",screenWidth/40)/2,screenHeight*.25,screenWidth/40,theme.white);
        DrawText(projectButtons[deleteIndex].text,screenWidth/2 - MeasureText(projectButtons[deleteIndex].text,screenWidth/30)/2,screenHeight*.325,screenWidth/30,theme.white);
        DrawButton(&confirmDeleteBut);
        DrawButton(&cancelDeleteBut);
    }

    if(inNewProjectMode){
        DrawRectangle(screenWidth*0.15,screenHeight*0.2,screenWidth*0.7,screenHeight*0.6,theme.black);
        DrawButton(&confirmNewBut);
        DrawButton(&cancelNewBut);
        DrawTextBox(newProjectName);
        DrawTextBox(newProjectNotes);

    }


    if(cursorCounter>=tooltipWait || inDeleteMode){
        HideCursor();
        if(cursorCounter>=tooltipWait){
            if(GetMouseX() + tooltipWidth > screenWidth){
                DrawTextInRectangle(tooltipText,(Rectangle){GetMouseX()- tooltipWidth,GetMouseY(),tooltipWidth,tooltipHeight},tooltipRows,theme.black,theme.white,theme.black);

            }
            else{
                DrawTextInRectangle(tooltipText,(Rectangle){GetMouseX(),GetMouseY(),tooltipWidth,tooltipHeight},tooltipRows,theme.black,theme.white,theme.black);
            }
        }
        if(inDeleteMode){
            DrawLineEx((Vector2){GetMouseX()-deleteCrosshairDistance,GetMouseY()-deleteCrosshairDistance},
                       (Vector2){GetMouseX()+deleteCrosshairDistance,GetMouseY()+deleteCrosshairDistance},
                       deleteCrosshairThickness,theme.accent1);
            DrawLineEx((Vector2){GetMouseX()+deleteCrosshairDistance,GetMouseY()-deleteCrosshairDistance},
                       (Vector2){GetMouseX()-deleteCrosshairDistance,GetMouseY()+deleteCrosshairDistance},
                       deleteCrosshairThickness,theme.accent1);

        }
        else{
            if(IsCursorHidden())ShowCursor();

        }
    }
    else{
        if(IsCursorHidden())ShowCursor();
    }



}

// OpenProject Screen Unload logic
void UnloadOpenProjectScreen(void)
{
    // TODO: Unload OpenProject screen variables here!
    if(IsCursorHidden())ShowCursor();
    if(inNewProjectMode){
        CloseTextBox(newProjectName);
        CloseTextBox(newProjectNotes);
    }
}

// OpenProject Screen should finish?
int FinishOpenProjectScreen(void)
{
    return finishScreen;
}