//
// Created by Aweso on 12/23/2023.
//



#ifndef TORQUECALCULATOR_DRAWMAIN_H
#define TORQUECALCULATOR_DRAWMAIN_H

#include "raylib.h"



int drawMain(void);


typedef enum GameScreen {
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
}Button;

//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;

extern const int screenWidth;
extern const int screenHeight;


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




void DrawButton(Button source);
void PressButton(Button *source);
void UnPressButton(Button *source);
bool IsButtonPressed(Button *source);

#endif //TORQUECALCULATOR_DRAWMAIN_H
