//
// Created by Aweso on 12/22/2023.
//
#include "drawMain.h"

int screenWidth = 0;
int screenHeight = 0;
char windowMode = 'w';
char drawLogo = 't';
ColorPalette theme;
int themeIndex = 0;
Font globalFont, titleFont;



int initDraw(){

    SetTextLineSpacing(20);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    screenWidth = 0;
    screenHeight = 0;

    FILE *config = fopen("config.dat","r");
    fseek(config,CONFIG_HEADER_SIZE+1,SEEK_CUR);
    char buffer[16] = {0};
    char *substring;
    fgets(buffer,16,config);
    long width = strtol(strchr(buffer,':')+1,&substring,10);
    long height = strtol(substring+1,NULL,10);
    screenWidth = width;
    screenHeight = height;
    if(screenHeight == 0 || screenWidth == 0){
        return 1;
    }

    fgets(buffer,16,config);
    windowMode = *(strchr(buffer,':') + 1);

    fgets(buffer,16,config);
    drawLogo = *(strchr(buffer,':') + 1);

    fgets(buffer,16,config);
    themeIndex = strtol(strchr(buffer,':')+1,NULL,10);
    theme = palettes[themeIndex];

    fclose(config);

    InitWindow(screenWidth, screenHeight, "Daedalus");

    SetExitKey(KEY_NULL);

    LoadMaterialsTextures(&tqcMaterials);

    globalFont = LoadFontEx("resources/fonts/main.ttf",100,NULL,0);
    if(globalFont.baseSize != 100){
        globalFont = LoadFontEx("resources/fonts/main.otf",100,NULL,0);
    }
    titleFont = LoadFontEx("resources/fonts/title.ttf",screenHeight/3,NULL,0);
    if(titleFont.baseSize != screenHeight/3){
        titleFont = LoadFontEx("resources/fonts/title.otf",screenHeight/3,NULL,0);
    }
    if(windowMode == 'f'){
        if(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE) == true)ToggleBorderlessWindowed();

        if(IsWindowFullscreen()==false)ToggleFullscreen();
    }
    else if(windowMode == 'b'){
        if(IsWindowFullscreen()==true)ToggleFullscreen();

        if(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE) == false)ToggleBorderlessWindowed();
    }
    else{
        if(IsWindowFullscreen()==true)ToggleFullscreen();
        if(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE) == true)ToggleBorderlessWindowed();

    }

    return 0;
}