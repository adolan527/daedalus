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

static Rectangle torqueBox = {0};
static Vector2 pmtSlider = {0};
static Rectangle pmtLine = {0};
static float pmtScalar = 0;
static float parameter = 0;
static float pmtMin, pmtMax;
static TextBox *pmtBox;


static ObjectBoxGUI *box = NULL;

static float crosshairSize;
extern bool doesMouseUpdateCamera; //Added in rcamera.h. Changes behavior of UpdateCamera function.
static bool IsObjectScreenOpen;
static Button backBut, newObjBut;



//----------------------------------------------------------------------------------
// ProjectMain Screen Functions Definition
//----------------------------------------------------------------------------------
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

    crosshairSize = (float)screenHeight/250;
    framesCounter = 0;
    finishScreen = -1;
    doesMouseUpdateCamera = true;
    IsObjectScreenOpen = false;

    torqueBox = (Rectangle){screenWidth*.28,screenHeight*.825,screenWidth*.5,screenHeight*.15};

    pmtLine = (Rectangle){screenWidth*0.5,screenHeight*0.875,screenWidth*0.25,screenHeight*0.05};
    pmtSlider = (Vector2){pmtLine.x+pmtLine.width/2,screenHeight*0.9};
    pmtMin = pmtLine.x + pmtLine.height/2;
    pmtMax = pmtLine.x + pmtLine.width - pmtLine.height/2;
    pmtBox = InitTextBox((Rectangle){screenWidth*.35,screenHeight*.85,screenWidth*.2,screenHeight*.05},6);
    pmtScalar = (pmtMax-pmtMin)/200;


    box = InitOBGUI();


    newObjBut = (Button){
            "New Object",
            (Rectangle){(float)screenWidth*.025f,(float)screenHeight*.025f,(float)screenWidth*.08f,(float)screenHeight*0.1f},
            theme.light,
            theme.white,
            false,
            false,
            false
    };



    backBut = (Button){
            "Back",
            (Rectangle){(float)screenWidth*0.89f,(float)screenHeight*0.875f,(float)screenWidth*.1f,(float)screenHeight*0.1f},
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

    framesCounter++;
    if(IsButtonPressed(&newObjBut)){
        IsObjectScreenOpen = true;
        box = InitOBGUI();

    }

    if(IsObjectScreenOpen){
        switch(UpdateOBGUI(box)){
            case DOCANCEL:
                IsObjectScreenOpen = false;
                CloseOBGUI(box);
                break;
            case DOSAVE:{
                if(box->companion==NULL){
                    box->companion = calloc(1,sizeof(Object));
                    GetObjFromOBGUI(box);
                    ModelObject(box->companion);
                    appendObject(&currentProject.objList,box->companion);
                }
                else{
                    printf("This object already exists\n");
                    GetObjFromOBGUI(box);
                    ModelObject(box->companion);
                    box->companion = NULL;
                }
                CloseOBGUI(box);
                IsObjectScreenOpen = false;
                break;
            }
            case DODELETE:{
                int objectIndex = isObjectInList(&currentProject.objList,box->companion);
                if(objectIndex!=-1){
                    deleteObject(&currentProject.objList,objectIndex);
                }
                IsObjectScreenOpen = false;
                CloseOBGUI(box);
                break;
            }
            case ISTYPING:
                break;
            case DOFACING:
                break;
            default:
                printf("Unknown UpdateOBGUI return value\n");
            case DONOTHING:
                if(!IsKeyDown(KEY_LEFT_CONTROL)) UpdateCamera(&camera, CAMERA_THIRD_PERSON);
                break;
        }


    }
    else{
        if(!IsKeyDown(KEY_LEFT_CONTROL)) UpdateCamera(&camera, CAMERA_THIRD_PERSON);


        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            Object *closest =NULL;
            float closestDistance = 1000000;
            for(ObjectNode *node = currentProject.objList.head;node!=NULL;node = node->next){
                Ray mouse;
                mouse = GetMouseRay(GetMousePosition(),camera);

                RayCollision collision = GetRayCollisionBox(mouse,node->data->box);
                if(collision.hit == true){
                    if(collision.distance<closestDistance){
                        closestDistance = collision.distance;
                        closest = node->data;
                    }
                    printf("Collision with object: %s\n",node->data->name);
                }
            }
            if(closest!=NULL){
                IsObjectScreenOpen = true;
                box = InitOBGUI();
                box->companion = closest;
                GetOBGUIFromObj(box);
            }
        }
    }

    if(IsTextBoxActive(pmtBox)){
        parameter = strtod(pmtBox->text,NULL);
        pmtSlider.x = parameter * pmtScalar + pmtLine.x;


    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(),pmtSlider,20)){
        if(GetMouseX()<pmtMax && GetMouseX()>pmtMin){
            pmtSlider.x = GetMouseX();
            parameter = (pmtSlider.x - pmtLine.x)*pmtScalar;

            snprintf(pmtBox->text,6,"%.2f",parameter);
            pmtBox->textIndex = strlen(pmtBox->text);
        }

    }


    if(IsButtonPressed(&backBut) || IsMouseButtonPressed(MOUSE_BUTTON_SIDE)){
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
        if(node->data==box->companion){
            if(node->data->type == sCylinder && node->data->data.facing != 'y'){
                if(node->data->data.facing=='x'){
                    DrawBoundingBox((BoundingBox){(Vector3){node->data->box.min.x,node->data->box.min.y- (2.0f/3.0f)*node->data->data.xLength,node->data->box.min.z},
                                                  (Vector3){node->data->box.max.x,node->data->box.max.y-((2.0f/3.0f))*node->data->data.xLength,node->data->box.max.z}},theme.dark);

                }
                else{
                    DrawBoundingBox((BoundingBox){(Vector3){node->data->box.min.x,node->data->box.min.y- 2*node->data->data.xLength,node->data->box.min.z},
                                                  (Vector3){node->data->box.max.x,node->data->box.max.y-2*node->data->data.xLength,node->data->box.max.z}},theme.dark);

                }
                }
            else{
                DrawBoundingBox(node->data->box,theme.dark);

            }

        }

    }

    DrawGrid(20, 1.0f);

    EndMode3D();

    DrawRectangleRec(torqueBox,theme.light);
    DrawRectangleLinesEx(torqueBox,torqueBox.height*0.05,theme.black);
    DrawRectangleRounded(pmtLine,1,3,theme.black);
    DrawCircleV(pmtSlider,pmtLine.height/2,theme.accent2);
    DrawTextBox(pmtBox);

    DrawButton(&newObjBut);
    DrawButton(&backBut);

    if(IsObjectScreenOpen){
        DrawOBGUI(box);
        if(box->companion != NULL){

        }
    }
    DrawRectangle(screenWidth*0.49,screenHeight*0.4975,screenWidth*0.02,crosshairSize,BLACK);
    DrawRectangle((screenWidth-crosshairSize)/2,screenHeight*0.485,crosshairSize,screenHeight*0.03,BLACK);
}

// ProjectMain Screen Unload logic
void UnloadProjectMainScreen(void)
{
    // TODO: Unload ProjectMain screen variables here!
    if(IsObjectScreenOpen){
        CloseOBGUI(box);
    }
    closeProject();
}

// ProjectMain Screen should finish?
int FinishProjectMainScreen(void)
{
    return finishScreen;
}