//
// Created by Aweso on 12/23/2023.
//
#include "drawMain.h"

void DrawButton(Button source){
    DrawRectangleRec(source.rect,source.color);
    int textSize = source.rect.height;

    while(MeasureText(source.text,textSize)+source.rect.width/10>source.rect.width){
        textSize-=2;
    }

    DrawText(source.text,source.rect.x+source.rect.width/20,source.rect.y + (source.rect.height-textSize)/2,textSize,source.textColor);
    if(source.isSelected == true && source.isPressed == false) DrawRectangleRec(source.rect,(Color){255,255,255,64});

}

void PressButton(Button *source){
    source->rect.x += 0.05f * source->rect.width;
    source->rect.y += 0.05f * source->rect.height;
    source->rect.height *= 0.9f;
    source->rect.width *= 0.9f;
    source->color.r *= 0.8;
    source->color.g *= 0.8;
    source->color.b *= 0.8;
    source->textColor.r *= 0.8f;
    source->textColor.g *= 0.8f;
    source->textColor.b *= 0.8f;
    source->isPressed = true;
}

void UnPressButton(Button *source){
    source->rect.height *= 10.0f/9.0f;
    source->rect.width *= 10.0f/9.0f;
    source->rect.x -= 0.05f * source->rect.width;
    source->rect.y -= 0.05f * source->rect.height;
    source->color.r *= 1.25;
    source->color.g *= 1.25;
    source->color.b *= 1.25;
    source->textColor.r *= 1.25;
    source->textColor.g *= 1.25;
    source->textColor.b *= 1.25;
    source->isPressed = false;

}

bool IsButtonPressed(Button *source){
    if(CheckCollisionPointRec(GetMousePosition(), source->rect) == true){
        source->isSelected = true;
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            PressButton(source);
        }
    }
    else{
        source->isSelected = false;
    }
    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && source->isPressed == true){
        UnPressButton(source);
        source->isPressed = false;
        if(source->isSelected == true){
            return true;
        }
    }
    return false;
}