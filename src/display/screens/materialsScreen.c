/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Materials Screen Functions Definitions (Init, Update, Draw, Unload)
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
typedef struct{
    tqcMaterial *companion;
    Button *but;
}MaterialButton;



static int framesCounter = 0;
static int finishScreen = 0;
static Button *backBut, *newBut, *scrollRight, *scrollLeft;
#define MAXMATERIALBUTTONCOUNT 20
static int materialButtonCount = 0;
static int lowestMaterialButton = 0;
static MaterialButton materialButtons[MAXMATERIALBUTTONCOUNT];
static MaterialGUI *materialGui;
static Button *colorButtons[PALETTE_COUNT];
static ColorGUI *colorGui;
static int newThemeIndex = 0;
static bool isMActive = false, isCActive = false;

//----------------------------------------------------------------------------------
// Materials Screen Functions Definition
//----------------------------------------------------------------------------------
void initMaterialButtons(){
    int i = 0;
    for(MaterialNode *ptr = tqcMaterials.head; ptr != NULL && i < materialButtonCount + lowestMaterialButton; ptr = ptr->next){
        if(i >= lowestMaterialButton){
            materialButtons[(i-lowestMaterialButton)].but = InitButton((Rectangle){screenWidth*.01,screenHeight*.05 + ((screenHeight*0.775)/(materialButtonCount)*1.05*(i-lowestMaterialButton)),screenWidth*.15,(screenHeight*0.775)/(materialButtonCount)},ptr->data->name,theme.light);
            materialButtons[(i-lowestMaterialButton)].companion = ptr->data;
        }
        ++i;
    }
}

void closeMaterialButtons(){
    for(int i = 0; i<materialButtonCount  && materialButtons[i].but !=NULL; i++){
        CloseButton(materialButtons[i].but);
    }
    memset(materialButtons, 0, sizeof(materialButtons));
}


void initColorButtons(){
    for(int i = 0; i<PALETTE_COUNT; i++){
        colorButtons[i] = InitButton((Rectangle){screenWidth*.5,screenHeight*.05 + ((screenHeight*0.775)/(PALETTE_COUNT)*1.05*i),screenWidth*.15,(screenHeight*0.775)/(PALETTE_COUNT)},TextFormat("Palette %d",i), (*(int*)(&palettes[i].light)) == 0 ? theme.light : palettes[i].light);
    }
}

void closeColorButtons(){
    for(int i = 0; i<PALETTE_COUNT; i++){
        CloseButton(colorButtons[i]);
    }
}

void UpdateTheme(){
    themeIndex = newThemeIndex;
    theme = palettes[newThemeIndex];
    makeConfig(screenWidth,screenHeight,windowMode,drawLogo,themeIndex);
    closeColorButtons();
    initColorButtons();
    closeMaterialButtons();
    initMaterialButtons();
    backBut->color = theme.dark;
    scrollLeft->color = theme.dark;
    scrollRight->color = theme.dark;
    newBut->color = theme.dark;

    ColorPalette *temp = colorGui->companion;

    CloseCGUI(colorGui);
    colorGui = InitCGUI();
    colorGui->companion = temp;
    GetCGUIFromColor(colorGui);
    writeColors();

}
// Materials Screen Initialization logic
void InitMaterialsScreen(void)
{
    // TODO: Initialize Materials screen variables here!
    framesCounter = 0;
    finishScreen = -1;
    isMActive = false;
    isCActive = false;
    backBut = InitButton((Rectangle){screenWidth*.9,screenHeight*.885,screenWidth*.08,screenHeight*.08},"Back",theme.dark);
    newBut = InitButton((Rectangle){screenWidth*.18,screenHeight*.885,screenWidth*.2,screenHeight*.1},"New",theme.dark);
    scrollLeft = InitButton((Rectangle){screenWidth*.01,screenHeight*.885,screenWidth*.07,screenHeight*.1},"<",theme.dark);
    scrollRight = InitButton((Rectangle){screenWidth*.09,screenHeight*.885,screenWidth*.07,screenHeight*.1},">",theme.dark);

    materialButtonCount = screenHeight/80 -1;
    initMaterialButtons();
    initColorButtons();

    materialGui = InitMGUI();
    colorGui = InitCGUI();

}

// Materials Screen Update logic
void UpdateMaterialsScreen(void)
{

    if(!isMActive && !isCActive){
        if(IsButtonPressed(backBut) || IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) finishScreen = SETTINGS;

        if(IsButtonPressed(newBut)){
            lowestMaterialButton = (getMaterialCount(&tqcMaterials)/materialButtonCount) * materialButtonCount;
            closeMaterialButtons();
            initMaterialButtons();

            DefaultMGUI(materialGui);
            isMActive = true;
        }
    }
    if(isMActive){
        switch (UpdateMGUI(materialGui)) {
            default:
            case DONOTHING:
                break;
            case DOSAVE:
                GetMatFromMGUI(materialGui, &tqcMaterials);
                refreshMaterialList(&tqcMaterials);
                closeMaterialButtons();
                initMaterialButtons();
                materialGui->companion = NULL;
                isMActive = false;
                break;
            case DOCANCEL:
                materialGui->companion = NULL;
                isMActive = false;
                break;
            case ISTYPING:
                break;
            case DODELETE: {
                MaterialNode *prev = NULL;
                for (MaterialNode *node = tqcMaterials.head; node != NULL; node = node->next) {
                    if (node->data == materialGui->companion) {
                        if(prev){
                            prev->next = node->next;

                        }
                        else{
                            tqcMaterials.head = node->next;
                        }
                        UnloadTexture(node->data->texture);
                        free(node->data);
                        free(node);
                        break;
                    }
                    prev = node;
                }
                refreshMaterialList(&tqcMaterials);
                closeMaterialButtons();
                initMaterialButtons();
                materialGui->companion = NULL;
                isMActive = false;
                break;
            }
        }
    }
    if(isCActive){
        switch (UpdateCGUI(colorGui)) {
            default:
            case DONOTHING:
                break;
            case DOSAVE:
                GetColorFromCGUI(colorGui);
                if(themeIndex == newThemeIndex){
                    UpdateTheme();
                }
                colorGui->companion = NULL;
                isCActive = false;
                break;
            case DOCANCEL:
                colorGui->companion = NULL;
                isCActive = false;
                break;
            case ISTYPING:
                break;
            case DODELETE:
                break;
            case COL_DOCHANGETHEME: {
                GetColorFromCGUI(colorGui);
                UpdateTheme();



                break;
            }

        }
    }

    if(IsButtonPressed(scrollRight)){
        lowestMaterialButton+= materialButtonCount;
        closeMaterialButtons();
        initMaterialButtons();
    }
    if(IsButtonPressed(scrollLeft)){
        lowestMaterialButton-=materialButtonCount;
        if(lowestMaterialButton < 0)lowestMaterialButton = 0;
        closeMaterialButtons();
        initMaterialButtons();
    }




    for (int i = 0; i < materialButtonCount && materialButtons[i].but != NULL; i++) {
        if (IsButtonPressed(materialButtons[i].but)) {
            materialGui->companion = materialButtons[i].companion;
            GetMGUIFromMat(materialGui);
            isMActive = true;
        }
    }

    for(int i = 0; i<PALETTE_COUNT; i++){
        if(IsButtonPressed(colorButtons[i])){
            colorGui->companion = &palettes[i];
            newThemeIndex = i;
            GetCGUIFromColor(colorGui);
            isCActive = true;
        }

    }

}

// Materials Screen Draw logic
void DrawMaterialsScreen(void)
{

    for(int i = 0; i < materialButtonCount  && materialButtons[i].but!=NULL; i++){
        DrawButton(materialButtons[i].but);
    }
    for(int i = 0; i<PALETTE_COUNT; i++){
        DrawButton(colorButtons[i]);
    }
    DrawTextEx(globalFont,TextFormat("%d-%d",lowestMaterialButton,lowestMaterialButton+materialButtonCount-1),(Vector2){screenWidth*.01,screenHeight*.01},screenHeight*0.04,GETSPACING(screenHeight*0.04),theme.dark);
    // TODO: Draw Materials screen here!
    DrawButton(backBut);
    DrawButton(newBut);
    DrawButton(scrollLeft);
    DrawButton(scrollRight);
    if(isMActive) DrawMGUI(materialGui);
    if(isCActive) DrawCGUI(colorGui);
}

// Materials Screen Unload logic
void UnloadMaterialsScreen(void)
{
    closeMaterialButtons();
    closeColorButtons();
    CloseButton(backBut);
    CloseButton(newBut);
    CloseButton(scrollLeft);
    CloseButton(scrollRight);
    CloseMGUI(materialGui);
    CloseCGUI(colorGui);
    UnloadMaterialsTextures(&tqcMaterials);
    LoadMaterialsTextures(&tqcMaterials);
    // TODO: Unload Materials screen variables here!
}

// Materials Screen should finish?
int FinishMaterialsScreen(void)
{
    return finishScreen;
}