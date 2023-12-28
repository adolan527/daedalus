//
// Created by Aweso on 12/23/2023.
//
#include "drawMain.h"

void DrawButton(Button *source) {
    Rectangle tempButton;
    if (source->isPressed == true && source->isToggle == false) {
        tempButton = (Rectangle){source->rect.x + 0.05f * source->rect.width,
                      source->rect.y + 0.05f * source->rect.height,
                      source->rect.width * 0.9f,
                      source->rect.height * 0.9f};
    }
    else{
        tempButton = (Rectangle){source->rect.x,
                                 source->rect.y,
                                 source->rect.width,
                                 source->rect.height};
    }
    DrawRectangleRec(tempButton, source->color);
    int textSize = tempButton.height;

    while(MeasureText(source->text,textSize)+tempButton.width/10>tempButton.width){
        textSize-=2;
    }

    DrawText(source->text,tempButton.x+tempButton.width/20,tempButton.y + (tempButton.height-textSize)/2,textSize,source->textColor);
    if(source->isSelected == true && source->isPressed == false) DrawRectangleRec(tempButton,(Color){255,255,255,64});

}

void PressButton(Button *source){
    source->color.r *= 0.8;
    source->color.g *= 0.8;
    source->color.b *= 0.8;
    source->textColor.r *= 0.75f;
    source->textColor.g *= 0.75f;
    source->textColor.b *= 0.75f;
    source->isPressed = true;
}

void UnPressButton(Button *source){
    source->color.r *= 1.25;
    source->color.g *= 1.25;
    source->color.b *= 1.25;
    source->textColor.r *= (float)4/3;
    source->textColor.g *= (float)4/3;
    source->textColor.b *= (float)4/3;
    source->isPressed = false;

}

bool IsButtonPressed(Button *source){
    if(CheckCollisionPointRec(GetMousePosition(), source->rect) == true){
        source->isSelected = true;
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(source->isToggle && source->isPressed){
                UnPressButton(source);
                return true;
            }
            else{
                PressButton(source);
                if(source->isToggle)return true;
            }

        }
    }
    else{
        source->isSelected = false;
    }
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && source->isPressed == true && source->isToggle==false){
        UnPressButton(source);
        if(source->isSelected == true){
            return true;
        }
    }
    return false;
}

