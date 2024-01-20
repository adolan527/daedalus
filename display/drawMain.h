//
// Created by Aweso on 12/23/2023.
//



#ifndef TORQUECALCULATOR_DRAWMAIN_H
#define TORQUECALCULATOR_DRAWMAIN_H

#include "../main.h"





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
    char text[NAMESIZE];
    Rectangle rect;
    Color color;
    Color textColor;
    bool isSelected;
    bool isPressed;
    bool isToggle;
}Button;

typedef struct{
    char *text;
    Rectangle rect;
    int charCount;
    float textSize;
    int textIndex;
    bool isTyping;
}TextBox;


#define OBGUITBCOUNT 10
typedef struct{
    Vector2 pos;
    TextBox *tb[OBGUITBCOUNT];
    Button saveBut, cancelBut, materialBut, typeBut, facingBut, deleteBut;
    Object *companion;
}ObjectBoxGUI;

typedef enum{
    obgName,
    obgXPosC,
    obgXPosM,
    obgYPos,
    obgZPos,
    obgXLength,
    obgYHeight,
    obgZDepth,
    obgThickness,
    obgMaterial //10 total
}OBGUITEXTBOXES;

typedef enum{
    DONOTHING,
    DOSAVE,
    DOCANCEL,
    ISTYPING,
    DOFACING,
    DODELETE
}OBGUIRET;


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

void DrawTextBox(TextBox *source);
void CloseTextBox(TextBox *t);
TextBox* InitTextBox(Rectangle rect, int charCount);
bool IsTextBoxActive(TextBox *source);

void DrawObject(Object *source, float pmt);
void ModelObject(Object *obj);
void ReModelObject(Object *obj);

void InitOBGUI(ObjectBoxGUI *source);
void DrawOBGUI(ObjectBoxGUI *source);
void CloseOBGUI(ObjectBoxGUI *source);
OBGUIRET UpdateOBGUI(ObjectBoxGUI *source);
void GetObjFromOBGUI(ObjectBoxGUI *source);
void GetOBGUIFromObj(ObjectBoxGUI *source);


#endif //TORQUECALCULATOR_DRAWMAIN_H
