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
#include "../../objectManagement/tqcObjects.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
static ObjectList objects = {NULL,NULL};
static Camera camera;

static Object dummy = {
        "Dummy",
        {0,1},
        0,5,
        sRectangle,
        {10,5,7,0,'x',false},
        (tqcMaterial){0},
        NULL
};
static Object cylinder = {
        "Cylinder",
        {5,-2},
        3,-1,
        sCylinder,
        {1,7,1,0,'y',false},
        (tqcMaterial){0},
        NULL
};
static Object *cyl;
static Object *dum;

static Ray line={0};
static float crosshairSize;
static Texture2D texture;

extern bool doesMouseUpdateCamera; //Added in rcamera.h. Changes behavior of UpdateCamera function.
static Mesh cubeMesh;
//----------------------------------------------------------------------------------
// ProjectMain Screen Functions Definition
//----------------------------------------------------------------------------------
static float parameter = 0;

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
    doesMouseUpdateCamera = false;


    dum = malloc(sizeof(Object));
    cyl = malloc(sizeof(Object));
    dummy.material = tqcMaterials[0];
    cylinder.material = tqcMaterials[2];
    *dum = dummy;
    *cyl = cylinder;

    appendObject(&objects,dum);
    appendObject(&objects,cyl);
    for(ObjectNode *obj = objects.head; obj != NULL; obj = obj->next){
        ModelObject(obj->data);
    }
}

// ProjectMain Screen Update logic
void UpdateProjectMainScreen(void)
{
    // TODO: Update ProjectMain screen variables here!
    static int index = 0;

    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    framesCounter++;
    if(IsKeyPressed(KEY_SPACE)){

        line = GetMouseRay((Vector2){screenWidth/2.0f,screenHeight/2.0f},camera);
        RayCollision rc = GetRayCollisionBox(line,(BoundingBox){(Vector3){0,0,0},(Vector3){10,10,10}});
        if(rc.hit == true)printf("X: %f, Y: %f, Z: %f\n",rc.point.x,rc.point.y,rc.point.z);
        float buffer;


        if(cyl->data.facing=='x'){
            buffer = cyl->data.xLength;
            cyl->data.xLength = cyl->data.yHeight;
            cyl->data.yHeight = buffer;
            cyl->data.facing='y';
            ReModelObject(cyl);
        }
        else if(cyl->data.facing=='z'){
            buffer = cyl->data.zDepth;
            cyl->data.zDepth = cyl->data.xLength;
            cyl->data.xLength = buffer;
            cyl->data.facing='x';
            ReModelObject(cyl);
        }
        else{
            buffer = cyl->data.yHeight;
            cyl->data.yHeight = cyl->data.zDepth;
            cyl->data.zDepth = buffer;
            cyl->data.facing='z';
            ReModelObject(cyl);
        }

        printf("F: %c\n",cyl->data.facing);
        //parameter++;
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
    //ClearBackground(theme.white);
    BeginMode3D(camera);
    for(ObjectNode *node = objects.head;node!=NULL;node = node->next){

        DrawObject(node->data,parameter);

    }


    DrawGrid(15, 1.0f);
    DrawRay(line,BLACK);

    EndMode3D();


    DrawRectangle(screenWidth*0.49,screenHeight*0.4975,screenWidth*0.02,crosshairSize,BLACK);
    DrawRectangle((screenWidth-crosshairSize)/2,screenHeight*0.485,crosshairSize,screenHeight*0.03,BLACK);
    //DrawCircle(screenWidth/2,screenHeight/2,5,BLUE);
}

// ProjectMain Screen Unload logic
void UnloadProjectMainScreen(void)
{
    // TODO: Unload ProjectMain screen variables here!
    closeObjectList(&objects);
    UnloadTexture(texture);
}

// ProjectMain Screen should finish?
int FinishProjectMainScreen(void)
{
    return finishScreen;
}