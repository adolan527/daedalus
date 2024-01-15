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
        tempButton = source->rect;

    }
    DrawRectangleRec(tempButton, source->color);
    DrawRectangleLinesEx(tempButton,tempButton.height/20,(source->color.r == theme.black.r ? theme.white:theme.black));
    int textSize = tempButton.height;
    int spacing = (textSize < SPACING ? 1 : textSize/SPACING);

    Vector2 measuredSize = MeasureTextEx(globalFont,source->text,textSize,spacing);
    while(measuredSize.x + tempButton.width/10>tempButton.width || measuredSize.y + tempButton.height/10>tempButton.height){
        textSize-=2;
        spacing = (textSize < SPACING ? 1 : textSize/SPACING);
        measuredSize = MeasureTextEx(globalFont,source->text,textSize,spacing);
    }
    Vector2 textPosition = {tempButton.x + (tempButton.width - measuredSize.x)/2, measuredSize.y/20 + tempButton.y + (tempButton.height - measuredSize.y)/2};

    DrawTextEx(globalFont, source->text, textPosition,textSize,spacing,source->textColor);
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

