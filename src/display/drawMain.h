//
// Created by Aweso on 12/23/2023.
//



#ifndef DAEDALUS_DRAWMAIN_H
#define DAEDALUS_DRAWMAIN_H

#include "../main.h"



#define MAX_LIGHTS  4         // Max dynamic lights supported by shader
//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Light data
typedef struct {
    int type;
    bool enabled;
    Vector3 position;
    Vector3 target;
    Color color;
    float attenuation;

    // Shader locations
    int enabledLoc;
    int typeLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int attenuationLoc;
} Light;

// Light type
typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT
} LightType;



typedef enum GameScreen {
    REINIT = -2,
    UNKNOWN = -1,
    LOGO = 0,
    TITLE = 1,
    SETTINGS = 2,
    CREATEPROJECT = 3,
    PROJECTMAIN = 4,
    EDITOBJECT = 5,
    OPENPROJECT = 6,
    MATERIALS = 7
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

typedef enum{
    DONOTHING,
    DOSAVE,
    DOCANCEL,
    ISTYPING,
    OBG_DOFACING,
    DODELETE,
    COL_DOCHANGETHEME
}GUIRET;

#define OBGUITBCOUNT 10
typedef struct{
    Vector2 pos;
    TextBox *tb[OBGUITBCOUNT];
    Button *saveBut, *cancelBut, *materialBut, *typeBut, *facingBut, *deleteBut;
    Object *companion;
}ObjectBoxGUI;

#define MATERIALGUITBCOUNT 5
typedef struct{
    Vector2 pos;
    TextBox *tb[MATERIALGUITBCOUNT];
    Button *saveBut, *cancelBut, *deleteBut;
    tqcMaterial *companion;
}MaterialGUI;

#define COLORGUICOUNT 18
typedef struct{
    Vector2 pos;
    TextBox *tb[COLORGUICOUNT];
    Button *saveBut, *cancelBut, *deleteBut, *selectBut;
    ColorPalette *companion;
}ColorGUI;



int drawMain(GameScreen startingScreen);
int initDraw(void);


//----------------------------------------------------------------------------------
// Global Variables Declaration (shared by several modules)
//----------------------------------------------------------------------------------
extern GameScreen currentScreen;

extern int screenWidth;
extern int screenHeight;
extern char windowMode;
extern char drawLogo;

extern Shader shader;
extern Color ambientLightColor;
extern Light lights[MAX_LIGHTS];


#define SPACING 16
#define GETSPACING(_size) (_size < SPACING ? 1 : _size/SPACING)
extern Font globalFont, titleFont;

#define CYLINDERRING 32

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

//----------------------------------------------------------------------------------
// Materials Screen Functions Declaration
//----------------------------------------------------------------------------------
void InitMaterialsScreen(void);
void UpdateMaterialsScreen(void);
void DrawMaterialsScreen(void);
void UnloadMaterialsScreen(void);
int FinishMaterialsScreen(void);




Button* InitButton(Rectangle r,char *t, Color c);
void CloseButton(Button *source);
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


ObjectBoxGUI* InitOBGUI(void);
void DrawOBGUI(ObjectBoxGUI *source);
void CloseOBGUI(ObjectBoxGUI *source);
GUIRET UpdateOBGUI(ObjectBoxGUI *source);
void GetObjFromOBGUI(ObjectBoxGUI *source);
void GetOBGUIFromObj(ObjectBoxGUI *source);

MaterialGUI* InitMGUI(void);
void DrawMGUI(MaterialGUI *source);
void CloseMGUI(MaterialGUI *source);
GUIRET UpdateMGUI(MaterialGUI *source);
void GetMatFromMGUI(MaterialGUI *source, MaterialList *list);
void GetMGUIFromMat(MaterialGUI *source);
void DefaultMGUI(MaterialGUI *source);




void DrawCGUI(ColorGUI *source);
void CloseCGUI(ColorGUI *source);
GUIRET UpdateCGUI(ColorGUI *source);
void GetCGUIFromColor(ColorGUI *source);
void GetColorFromCGUI(ColorGUI *source);
ColorGUI* InitCGUI(void);



Mesh GenMeshRectTube(Object *obj);
Mesh GenMeshCustom();
Mesh GenMeshRoundTube(Object *obj);


//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
Light CreateLight(int type, Vector3 position, Vector3 target, Color color, Shader shader);   // Create a light and get shader locations
void UpdateLightValues(Shader shader, Light light);         // Send light properties to shader


#endif //DAEDALUS_DRAWMAIN_H
