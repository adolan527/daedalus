//
// Created by Aweso on 12/31/2023.
//
#include "drawMain.h"

void LoadMaterialsTextures(){
    for(int i = 0; i < TQCMATERIALS_COUNT; i++){
        if(tqcMaterials[i].name[0] != 0){
            char buffer[NAMESIZE+16] = {0};
            sprintf(buffer,"resources/%s.png",tqcMaterials[i].name);
            tqcMaterials[i].texture = LoadTexture(buffer);
        }
        else{
            return;
        }
    }
}

void UnloadMaterialsTextures(){
    for(int i = 0; i < TQCMATERIALS_COUNT; i++){
        if(tqcMaterials[i].name[0] != 0){
            UnloadTexture(tqcMaterials[i].texture);
        }
        else{
            return;
        }
    }
}