//
// Created by Aweso on 12/23/2023.
//
#include "drawMain.h"

Button* InitButton(Rectangle r,char *t, Color c){
    Button* b = calloc(1,sizeof(Button));
    b->rect = r;
    b->color = c;
    b->textColor = (c.r==theme.white.r ? theme.black : theme.white);
    strncpy(b->text,t,NAMESIZE);
    b->isPressed = false;
    b->isSelected = false;
    b->isToggle = false;
    return b;
}

void CloseButton(Button *source){
    free(source);
}

void DrawButton(Button *source) {
    bool displayCalculationInfo = false;
    // To make sure that the text size fills the button, it has to "guess and check" with MeasureText()
    // Due to the complexity of the function it would be very difficult to actually do the math for.
    // This "guess and check" approach takes place in the while loop, where the text size increases...
    // until it reaches the size of the rectangle. This would be okay if it were not computed every frame.
    // As I am working on another project that will involve GUIs in rayLib, I look to remove this
    // inefficiency by storing the text size in the struct (or in the new project, a class)
    // The first number is the number of iterations through the while loop, the second is
    // time in ms to execute those iterations.
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
    int x = 0;
    double t = GetTime();
    while(measuredSize.x + tempButton.width/10>tempButton.width || measuredSize.y + tempButton.height/10>tempButton.height){
        textSize-=2;
        spacing = (textSize < SPACING ? 1 : textSize/SPACING);
        measuredSize = MeasureTextEx(globalFont,source->text,textSize,spacing);
        x++;
    }
    if(displayCalculationInfo) t = (GetTime()-t)*1000;

    Vector2 textPosition = {tempButton.x + (tempButton.width - measuredSize.x)/2, measuredSize.y/20 + tempButton.y + (tempButton.height - measuredSize.y)/2};

    DrawTextEx(globalFont, source->text, textPosition,textSize,spacing,source->textColor);
    if(source->isSelected == true && source->isPressed == false) DrawRectangleRec(tempButton,(Color){255,255,255,64});
    if(displayCalculationInfo) DrawText(TextFormat("%d, %.2fms",x,t),source->rect.x,source->rect.y,70,BLUE);

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

