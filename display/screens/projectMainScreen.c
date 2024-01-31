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

#include "../drawMain.h"


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
static float pmtCenter = 0;
static float pmtMin, pmtMax;
static TextBox *pmtBox;
static float pmtTextX = 0;
static Ray mouse;


static ObjectBoxGUI *box = NULL;

static float crosshairSize;
extern bool doesMouseUpdateCamera; //Added in rcamera.h. Changes behavior of UpdateCamera function.
static bool isObjectScreenOpen;
static Button backBut, newObjBut;
static bool isSliding = false;


static Rectangle infoBox;
static double currentVolume = 0, currentWeight = 0, currentTorque = 0;
static Vector3 currentCOM = {0};
static float infoBoxTextSize,infoBoxTextSpacing;


//----------------------------------------------------------------------------------
// ProjectMain Screen Functions Definition
//----------------------------------------------------------------------------------
static int index = 0;
static void UpdateInfoBox(Object *obj){
    printf("Updated info box\n");
    currentVolume = getObjectVolume(obj);
    if(strcmp(obj->material.name,WEIGHTMATERIAL)!=0){
        currentWeight = currentVolume * obj->material.density;
    }
    else{
        printf("Dummy weight detected\n");
        currentWeight = obj->material.density;
    }

    currentTorque = computeObject(obj,parameter);
    if(obj->type == sSphere){
        currentCOM = (Vector3){obj->xPos.constant,obj->yPos,obj->zPos};
    }
    else if(obj->type == sRectangle){
        currentCOM = (Vector3){obj->xPos.constant+obj->data.xLength/2,obj->yPos+obj->data.yHeight/2,obj->zPos+obj->data.zDepth/2};
    }
    else{
        switch (obj->data.facing) {
            case 'x': {
                currentCOM = (Vector3) {obj->xPos.constant + obj->data.xLength / 2, obj->yPos, obj->zPos};
                break;
            }
            case 'y': {
                currentCOM = (Vector3) {obj->xPos.constant, obj->yPos + obj->data.yHeight / 2, obj->zPos};
                break;
            }
            case 'z': {
                currentCOM = (Vector3) {obj->xPos.constant, obj->yPos, obj->zPos + obj->data.zDepth / 2};
                break;
            }
        }
    }
}

Mesh thing = {0};

// ProjectMain Screen Initialization logic
void InitProjectMainScreen(void)
{


    // TODO: Initialize ProjectMain screen variables here!
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    currentCOM = (Vector3){0};
    currentVolume = 0;
    currentWeight = 0;
    currentTorque = 0;



    crosshairSize = (float)screenHeight/250;
    framesCounter = 0;
    finishScreen = -1;
    doesMouseUpdateCamera = true;
    isObjectScreenOpen = false;
    isSliding = false;
    torqueBox = (Rectangle){screenWidth*.28,screenHeight*.825,screenWidth*.5,screenHeight*.15};

    pmtLine = (Rectangle){screenWidth*0.52,screenHeight*0.895,screenWidth*0.25,screenHeight*0.05};
    pmtSlider = (Vector2){pmtLine.x+pmtLine.width/2,screenHeight*0.92};
    pmtCenter = pmtLine.x + pmtLine.width/2;
    pmtMin = pmtLine.x + pmtLine.height/2;
    pmtMax = pmtLine.x + pmtLine.width - pmtLine.height/2;
    pmtBox = InitTextBox((Rectangle){screenWidth*.52,screenHeight*.84,screenWidth*.25,screenHeight*.05},6);
    pmtScalar = (pmtLine.width-pmtLine.height)/1000;
    pmtTextX = pmtCenter - MeasureTextEx(globalFont,"Parameter",pmtLine.height,GETSPACING(pmtLine.height)).x/2;


    infoBox = (Rectangle){screenWidth*.79,screenHeight*.6025,screenWidth*.2,screenHeight*.2175};
    infoBoxTextSize = infoBox.height/7;
    infoBoxTextSpacing = GETSPACING(infoBoxTextSize);
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
        if(obj->data->data.thickness!=0 && obj->data->type==sRectangle && obj->data->data.facing!='x'){
            obj->data->data.facing='x';
        }
        ModelObject(obj->data);
        UpdateInfoBox(obj->data);
        printf("Object found\n");
    }

    thing = GenMeshCustom();

}

// ProjectMain Screen Update logic
void UpdateProjectMainScreen(void)
{
    // TODO: Update ProjectMain screen variables here!

    framesCounter++;



    if(IsButtonPressed(&newObjBut) || (IsKeyPressed(KEY_N)&&IsKeyDown(KEY_LEFT_CONTROL))){
        isObjectScreenOpen = true;
        box = InitOBGUI();

    }


    if(isObjectScreenOpen){
        switch(UpdateOBGUI(box)){
            case DOCANCEL:
                isObjectScreenOpen = false;
                if(box->companion!=NULL){
                    box->companion->material.color.a=255;
                    printf("Brightness readjusted\n");

                }
                CloseOBGUI(box);

                break;
            case DOSAVE:{
                if(box->companion==NULL){
                    box->companion = calloc(1,sizeof(Object));
                    GetObjFromOBGUI(box);
                    ModelObject(box->companion);
                    UpdateInfoBox(box->companion);
                    appendObject(&currentProject.objList,box->companion);

                }
                else{
                    printf("This object already exists\n");
                    GetObjFromOBGUI(box);
                    ModelObject(box->companion);
                    UpdateInfoBox(box->companion);
                    if(box->companion!=NULL){
                        box->companion->material.color.a=255;
                        printf("Brightness readjusted\n");
                    }
                    box->companion = NULL;
                }
                CloseOBGUI(box);
                isObjectScreenOpen = false;
                break;
            }
            case DODELETE:{
                int objectIndex = isObjectInList(&currentProject.objList,box->companion);
                if(objectIndex!=-1){
                    deleteObject(&currentProject.objList,objectIndex);
                }
                isObjectScreenOpen = false;
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
            float closestDistance = 999999999999.0f;
            for(ObjectNode *node = currentProject.objList.head;node!=NULL;node = node->next){

                mouse = GetMouseRay(GetMousePosition(),camera);
                //MatrixTranslate(cmpPmt(node->data->xPos,parameter),node->data->yPos,node->data->zPos)
                RayCollision collision;

                if(node->data->type==sRectangle && node->data->data.thickness==0){
                    collision = GetRayCollisionMesh(mouse,node->data->model->meshes[0],
                                        MatrixMultiply(node->data->model->transform,
                                        MatrixTranslate(parameter*node->data->xPos.meter + node->data->data.xLength/2,node->data->data.yHeight/2,node->data->data.zDepth/2)));
                }
                else{
                    collision = GetRayCollisionMesh(mouse,node->data->model->meshes[0],MatrixMultiply(node->data->model->transform,
                                                                                                      MatrixTranslate(parameter*node->data->xPos.meter,0,0)));

                }

                if(collision.hit == true){
                    if(collision.distance<closestDistance){
                        closestDistance = collision.distance;
                        closest = node->data;
                    }
                    printf("Collision with object: %s\n",node->data->name);
                }
            }
            if(closest!=NULL){
                isObjectScreenOpen = true;
                box = InitOBGUI();
                box->companion = closest;
                GetOBGUIFromObj(box);
                UpdateInfoBox(box->companion);
                box->companion->material.color.a=127;

            }
        }
    }

    if(IsTextBoxActive(pmtBox)){
        parameter = strtod(pmtBox->text,NULL);
        if(isObjectScreenOpen){
            UpdateInfoBox(box->companion);
        }
        pmtSlider.x = parameter * pmtScalar + pmtCenter;
    }

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointCircle(GetMousePosition(),pmtSlider,pmtLine.height)){
        isSliding = true;
    }

    if(isSliding){
        int mouseX = GetMouseX();
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            isSliding = false;
        }

        if(mouseX>=pmtMax) pmtSlider.x = pmtMax;
        else if(mouseX<=pmtMin) pmtSlider.x = pmtMin;
        else pmtSlider.x = mouseX;

        parameter = (pmtSlider.x - pmtCenter)*pmtScalar;

        snprintf(pmtBox->text,6,"%.2f",parameter);
        pmtBox->textIndex = strlen(pmtBox->text);
        if(isObjectScreenOpen){
            UpdateInfoBox(box->companion);
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
    }

    DrawGrid(20, 1.0f);

    //DrawMesh(thing,LoadMaterialDefault(),MatrixIdentity());


    EndMode3D();

    DrawRectangleRec(torqueBox,theme.light);
    DrawRectangleLinesEx(torqueBox,torqueBox.height*0.05,theme.black);
    DrawRectangleRounded(pmtLine,1,3,theme.black);
    DrawTextBox(pmtBox);
    DrawTextEx(globalFont,"Parameter",(Vector2){pmtTextX,pmtLine.y},pmtLine.height,GETSPACING(pmtLine.height),theme.white);
    DrawCircleV(pmtSlider,pmtLine.height/2,(Color){theme.accent2.r,theme.accent2.g,theme.accent2.b,127});


    DrawButton(&newObjBut);
    DrawButton(&backBut);

    if(isObjectScreenOpen){
        DrawOBGUI(box);
        DrawRectangleRec(infoBox,theme.light);
        DrawRectangleLinesEx(infoBox,1,theme.black);
        //    infoBox = (Rectangle){screenWidth*.79,screenHeight*.6025,screenWidth*.2,screenHeight*.2175};
        DrawTextEx(globalFont,"Volume:",
                   (Vector2){screenWidth*.8,screenHeight*0.6125},infoBoxTextSize,infoBoxTextSpacing,WHITE);
        DrawTextEx(globalFont,"Weight:",
                      (Vector2){screenWidth*.8,screenHeight*0.6525},infoBoxTextSize,infoBoxTextSpacing,WHITE);
        DrawTextEx(globalFont,"Torque:",
                        (Vector2){screenWidth*.8,screenHeight*0.6925},infoBoxTextSize,infoBoxTextSpacing,WHITE);
        DrawTextEx(globalFont,"C.o.M.:",
                              (Vector2){screenWidth*.8,screenHeight*0.7325},infoBoxTextSize,infoBoxTextSpacing,WHITE);
        DrawTextEx(globalFont,TextFormat("%f in3",currentVolume),
                   (Vector2){screenWidth*.87,screenHeight*0.6125},infoBoxTextSize,infoBoxTextSpacing,WHITE);
        DrawTextEx(globalFont,TextFormat("%f lbs",currentWeight),
                   (Vector2){screenWidth*.87,screenHeight*0.6525},infoBoxTextSize,infoBoxTextSpacing,WHITE);
        DrawTextEx(globalFont,TextFormat("%f in/lbs",currentTorque),
                   (Vector2){screenWidth*.87,screenHeight*.6925},infoBoxTextSize,infoBoxTextSpacing,WHITE);


    }
    DrawRectangle(screenWidth*0.49,screenHeight*0.4975,screenWidth*0.02,crosshairSize,BLACK);
    DrawRectangle((screenWidth-crosshairSize)/2,screenHeight*0.485,crosshairSize,screenHeight*0.03,BLACK);
}

// ProjectMain Screen Unload logic
void UnloadProjectMainScreen(void)
{
    // TODO: Unload ProjectMain screen variables here!
    if(isObjectScreenOpen){
        CloseOBGUI(box);
    }
    closeProject();
    UnloadMesh(thing);
}

// ProjectMain Screen should finish?
int FinishProjectMainScreen(void)
{
    return finishScreen;
}