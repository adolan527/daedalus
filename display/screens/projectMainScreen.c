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
#include "../../objectManagement/calculations.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static Camera camera;


static float crosshairSize;
extern bool doesMouseUpdateCamera; //Added in rcamera.h. Changes behavior of UpdateCamera function.

static Button NewObjBut, NewObjSave, NewObjCanc, BackButton, MaterialButton;
static bool IsNewObjectScreeenOpen;

static TextBox *name, *xPosC, *xPosM, *yPos, *zPos, *xLength, *yHeight, *zDepth, *thickness, *material;

//----------------------------------------------------------------------------------
// ProjectMain Screen Functions Definition
//----------------------------------------------------------------------------------
static float parameter = 0;
static int index = 0;


// ProjectMain Screen Initialization logic
void InitProjectMainScreen(void)
{
    // TODO: Initialize ProjectMain screen variables here!

    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    crosshairSize = screenHeight/250;
    framesCounter = 0;
    finishScreen = -1;
    doesMouseUpdateCamera = true;
    IsNewObjectScreeenOpen = false;


    name = InitTextBox((Rectangle){screenWidth*.795,screenHeight*.03,screenWidth*.19,screenHeight*.05},20);
    strcpy(name->text,"Name");
    name->textIndex+=4;

    //Position elements

    xPosC = InitTextBox((Rectangle){screenWidth*.795,screenHeight*.1125,screenWidth*.04,screenHeight*.025},6);
    strcpy(xPosC->text,"X C");
    xPosC->textIndex+=3;

    xPosM = InitTextBox((Rectangle){screenWidth*.84,screenHeight*.1125,screenWidth*.04,screenHeight*.025},6);
    strcpy(xPosM->text,"X M");
    xPosM->textIndex+=3;

    yPos = InitTextBox((Rectangle){screenWidth*.885,screenHeight*.1125,screenWidth*.04,screenHeight*.025},6);
    strcpy(yPos->text,"Y");
    yPos->textIndex+=1;

    zPos = InitTextBox((Rectangle){screenWidth*.93,screenHeight*.1125,screenWidth*.04,screenHeight*.025},6);
    strcpy(zPos->text,"Z");
    zPos->textIndex+=1;

    //Size elements

    xLength = InitTextBox((Rectangle){screenWidth*.795,screenHeight*.175,screenWidth*.04,screenHeight*.025},6);
    strcpy(xLength->text,"X");
    xLength->textIndex+=1;

    yHeight = InitTextBox((Rectangle){screenWidth*.84,screenHeight*.175,screenWidth*.04,screenHeight*.025},6);
    strcpy(yHeight->text,"Y");
    yHeight->textIndex+=1;

    zDepth = InitTextBox((Rectangle){screenWidth*.885,screenHeight*.175,screenWidth*.04,screenHeight*.025},6);
    strcpy(zDepth->text,"Z");
    zDepth->textIndex+=1;

    //Other

    thickness = InitTextBox((Rectangle){screenWidth*.795 + MeasureTextEx(globalFont,"Thickness:  ",screenHeight/32, GETSPACING(screenHeight/32)).x,
                                        screenHeight*.175 + MeasureTextEx(globalFont,"Thickness:  ",screenHeight/32, GETSPACING(screenHeight/32)).y,
                                        screenWidth*.075,screenHeight*.025},10);
    strcpy(thickness->text,"T");
    thickness->textIndex+=1;

    material = InitTextBox((Rectangle){screenWidth*.885,screenHeight*.24,screenWidth*.08,screenHeight*.05},20);
    strcpy(material->text,"M");
    material->textIndex+=1;


    NewObjBut = (Button){
            "New Object",
            (Rectangle){screenWidth*.025,screenHeight*.025,screenWidth*.08,screenHeight*0.1},
            theme.light,
            theme.white,
            false,
            false,
            false
    };

    NewObjCanc = (Button){
            "Cancel",
            (Rectangle){screenWidth*.9,screenHeight*.5,screenWidth*.08,screenHeight*0.08},
            theme.dark,
            theme.white,
            false,
            false,
            false
    };

    MaterialButton = (Button){
        "Material",
        (Rectangle){screenWidth*.795,screenHeight*.24, screenWidth*.085,screenHeight*0.05},
        theme.accent2,
        theme.white,
        false,
        false,
        true
    };

    NewObjSave = (Button){
            "Save",
            (Rectangle){screenWidth*.8,screenHeight*.5,screenWidth*.08,screenHeight*0.08},
            theme.accent1,
            theme.white,
            false,
            false,
            false
    };

    BackButton = (Button){
            "Back",
            (Rectangle){screenWidth*0.89,screenHeight*0.875,screenWidth*.1,screenHeight*0.1},
            theme.dark,
            theme.white,
            false,
            false,
            false
    };




    for(ObjectNode *obj = currentProject.objList.head; obj != NULL; obj = obj->next){
        ModelObject(obj->data);
    }

}
// ProjectMain Screen Update logic
void UpdateProjectMainScreen(void)
{
    // TODO: Update ProjectMain screen variables here!
    if(!IsTextBoxActive(name) &&
       !IsTextBoxActive(xPosC) &&
       !IsTextBoxActive(xPosM) &&
       !IsTextBoxActive(yPos) &&
       !IsTextBoxActive(zPos) &&
       !IsTextBoxActive(xLength) &&
       !IsTextBoxActive(yHeight) &&
       !IsTextBoxActive(zDepth) &&
       !IsTextBoxActive(material)){
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

    }
    framesCounter++;
    if(IsButtonPressed(&NewObjBut)){
        IsNewObjectScreeenOpen = true;
    }
    if(IsNewObjectScreeenOpen){
        if(IsButtonPressed(&NewObjSave)) IsNewObjectScreeenOpen = false;
        if(IsButtonPressed(&NewObjCanc)) IsNewObjectScreeenOpen = false;
        if(IsButtonPressed(&MaterialButton)){
            if(MaterialButton.isPressed==true){
                memset(MaterialButton.text,0,20);
                strcpy(MaterialButton.text,"Weight");
            }
            else{
                memset(MaterialButton.text,0,20);
                strcpy(MaterialButton.text,"Material");
            }
        }
    }

    if(IsButtonPressed(&BackButton) || IsMouseButtonPressed(MOUSE_BUTTON_SIDE)){
        finishScreen = OPENPROJECT;
    }


    if(IsKeyDown(KEY_LEFT_SHIFT) || IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){
        if(!IsCursorHidden()){
            HideCursor();
            SetMousePosition(screenWidth/2,screenHeight/2);
        }

        doesMouseUpdateCamera = true;
    }
    else{
        if(IsCursorHidden()){
            ShowCursor();
            SetMousePosition(screenWidth/2,screenHeight/2);
        }

        doesMouseUpdateCamera = false;
    }




}

// ProjectMain Screen Draw logic
void DrawProjectMainScreen(void)
{
    // TODO: Draw ProjectMain screen here!
    BeginMode3D(camera);
    for(ObjectNode *node = currentProject.objList.head;node!=NULL;node = node->next){

        DrawObject(node->data,parameter);

    }


    DrawGrid(15, 1.0f);

    EndMode3D();

    DrawButton(&NewObjBut);
    DrawButton(&BackButton);

    if(IsNewObjectScreeenOpen){

        DrawRectangle(screenWidth*.79,screenHeight*.025,screenWidth*.20,screenHeight*.5725,theme.light);
        DrawRectangleLines(screenWidth*.79,screenHeight*.025,screenWidth*.20,screenHeight*.5725,theme.black);

        DrawTextBox(name);

        DrawTextEx(globalFont,"Position XYZ:",(Vector2){screenWidth*.795,screenHeight*.0825},screenHeight/32,GETSPACING(screenHeight/24),theme.black);

        DrawTextBox(xPosC);
        DrawTextBox(xPosM);
        DrawTextBox(yPos);
        DrawTextBox(zPos);

        DrawTextEx(globalFont,"Size XYZ:",(Vector2){screenWidth*.795,screenHeight*.14},screenHeight/32,GETSPACING(screenHeight/24),theme.black);


        DrawTextBox(xLength);
        DrawTextBox(yHeight);
        DrawTextBox(zDepth);

        DrawTextEx(globalFont,"Thickness:",(Vector2){screenWidth*.795,screenHeight*.2025},screenHeight/32,GETSPACING(screenHeight/24),theme.black);
        DrawTextBox(thickness);

        DrawTextEx(globalFont,"Material:",(Vector2){screenWidth*.795,screenHeight*.265},screenHeight/32,GETSPACING(screenHeight/24),theme.black);
        DrawTextBox(material);

        DrawButton(&NewObjSave);
        DrawButton(&NewObjCanc);
        DrawButton(&MaterialButton);


    }


    DrawRectangle(screenWidth*0.49,screenHeight*0.4975,screenWidth*0.02,crosshairSize,BLACK);
    DrawRectangle((screenWidth-crosshairSize)/2,screenHeight*0.485,crosshairSize,screenHeight*0.03,BLACK);
    //DrawCircle(screenWidth/2,screenHeight/2,5,BLUE);
}

// ProjectMain Screen Unload logic
void UnloadProjectMainScreen(void)
{
    // TODO: Unload ProjectMain screen variables here!
    closeProject();
}

// ProjectMain Screen should finish?
int FinishProjectMainScreen(void)
{
    return finishScreen;
}