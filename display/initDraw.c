//
// Created by Aweso on 12/22/2023.
//
#include "drawMain.h"

int screenWidth = 0;
int screenHeight = 0;
char windowMode = 'w';
char drawLogo = 't';
ColorPalette theme;
Font globalFont;

int initDraw(){

    SetTextLineSpacing(20);

    screenWidth = 0;
    screenHeight = 0;


    theme = palettes[6];
    if(*(int*)(&theme.white)==0){
        theme=palettes[0];
    }

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

    fclose(config);

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Torque Calculator");

    SetExitKey(KEY_NULL);

    LoadMaterialsTextures();

    globalFont = LoadFont("resources/roman.ttf");

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