//
// Created by Aweso on 12/31/2023.
//
#include "drawMain.h"

#define MATERIALS_COUNT 10
tqcMaterial tqcMaterials[MATERIALS_COUNT] = {
        {"6061-Aluminum", 0.09754374,LIGHTGRAY, {0}},
        {"6063-Aluminum", 0.09718247,LIGHTGRAY, {0}},
        {"Steel", 0.283599,DARKGRAY, {0}},
        {"Pine-Wood", 0.01987002,BEIGE, {0}},
        {"Polycarbonate", 0.04335278,RAYWHITE, {0}},
        {0}

};

void LoadMaterialsTextures(){
    for(int i = 0; i < MATERIALS_COUNT; i++){
        if(tqcMaterials[i].name[0] != 0){
            tqcMaterials[i].texture = LoadTexture(TextFormat("resources/%s.png",tqcMaterials[i].name));
        }
        else{
            return;
        }
    }
}

void UnloadMaterialsTextures(){
    for(int i = 0; i < MATERIALS_COUNT; i++){
        if(tqcMaterials[i].name[0] != 0){
            UnloadTexture(tqcMaterials[i].texture);
        }
        else{
            return;
        }
    }
}