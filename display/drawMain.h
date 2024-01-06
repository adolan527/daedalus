//
// Created by Aweso on 12/23/2023.
//



#ifndef TORQUECALCULATOR_DRAWMAIN_H
#define TORQUECALCULATOR_DRAWMAIN_H

#include "../main.h"

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "../projectManagement/projectManagement.h"
#include "../objectManagement/tqcObjects.h"
#include "raymath.h"



typedef enum GameScreen {
    REINIT = -2,
    UNKNOWN = -1,
    LOGO = 0,
    TITLE = 1,
    SETTINGS = 2,
    CREATEPROJECT = 3,
    PROJECTMAIN = 4,
    EDITOBJECT = 5,
    OPENPROJECT = 6
}GameScreen;

typedef struct{
    char text[20];
    Rectangle rect;
    Color color;
    Color textColor;
    bool isSelected;
    bool isPressed;
    bool isToggle;
}Button;



typedef struct{
    Color white;
    Color black;
    Color light;
    Color dark;
    Color accent1;
    Color accent2;
}ColorPalette;

int drawMain(GameScreen startingScreen);
int initDraw(void);
void LoadMaterialsTextures(void);
void UnloadMaterialsTextures(void);

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;

extern int screenWidth;
extern int screenHeight;
extern char windowMode;
extern char drawLogo;
extern ColorPalette theme;
extern ColorPalette palettes[10];
extern tqcMaterial tqcMaterials[10];
#define SPACING 16
#define GETSPACING(_size) (_size < SPACING ? 1 : _size/SPACING)
extern Font globalFont;

#define CYLINDERRING 64

//----------------------------------------------------------------------------------
// Logo Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitLogoScreen(void);
void UpdateLogoScreen(void);
void DrawLogoScreen(void);
void UnloadLogoScreen(void);
int FinishLogoScreen(void);

//----------------------------------------------------------------------------------
// Title Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitTitleScreen(void);
void UpdateTitleScreen(void);
void DrawTitleScreen(void);
void UnloadTitleScreen(void);
int FinishTitleScreen(void);

//----------------------------------------------------------------------------------
// Settings Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitSettingsScreen(void);
void UpdateSettingsScreen(void);
void DrawSettingsScreen(void);
void UnloadSettingsScreen(void);
int FinishSettingsScreen(void);

//----------------------------------------------------------------------------------
// CreateProject Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitCreateProjectScreen(void);
void UpdateCreateProjectScreen(void);
void DrawCreateProjectScreen(void);
void UnloadCreateProjectScreen(void);
int FinishCreateProjectScreen(void);

//----------------------------------------------------------------------------------
// ProjectMain Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitProjectMainScreen(void);
void UpdateProjectMainScreen(void);
void DrawProjectMainScreen(void);
void UnloadProjectMainScreen(void);
int FinishProjectMainScreen(void);

//----------------------------------------------------------------------------------
// EditObject Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitEditObjectScreen(void);
void UpdateEditObjectScreen(void);
void DrawEditObjectScreen(void);
void UnloadEditObjectScreen(void);
int FinishEditObjectScreen(void);

//----------------------------------------------------------------------------------
// OpenProject Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitOpenProjectScreen(void);
void UpdateOpenProjectScreen(void);
void DrawOpenProjectScreen(void);
void UnloadOpenProjectScreen(void);
int FinishOpenProjectScreen(void);




void DrawButton(Button *source);
void PressButton(Button *source);
void UnPressButton(Button *source);
bool IsButtonPressed(Button *source);


void DrawTextInRectangle(char *text,Rectangle rect, int rowCount, Color textColor, Color background, Color border);

void DrawObject(Object *source, float pmt);
void ModelObject(Object *obj);
void ReModelObject(Object *obj);

#endif //TORQUECALCULATOR_DRAWMAIN_H
