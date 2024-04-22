//
// Created by Aweso on 1/14/2024.
//
#include "drawMain.h"


TextBox* InitTextBox(Rectangle rect, int charCount){
    TextBox *temp = malloc(sizeof(TextBox));
    temp->text = calloc(1, charCount);
    temp->charCount=charCount;
    temp->textIndex = 0;
    temp->textSize = rect.height*0.9;
    temp->isTyping = false;
    temp->rect = rect;
    return temp;
}

void CloseTextBox(TextBox *t){
    free(t->text);
    free(t);
    t = NULL;

}

void DrawTextBox(TextBox *source){

    DrawRectangleRec(source->rect,(source->isTyping? theme.white :theme.light));
    DrawRectangleLinesEx(source->rect,source->rect.height/25,theme.black);

    if(MeasureTextEx(globalFont,source->text,source->textSize,GETSPACING(source->textSize)).x > source->rect.width){
        source->textSize *=0.9f;
    }

    DrawTextEx(globalFont,source->text,
               (Vector2){source->rect.x+source->rect.width*0.05,source->rect.y+source->rect.height*0.05},
               source->textSize,
               GETSPACING(source->textSize),theme.black);
}

bool IsTextBoxActive(TextBox *source){
    if(source->isTyping==true){
        int c = GetKeyPressed();
        if(IsKeyDown(KEY_LEFT_CONTROL)){
            if(c == KEY_A){
                memset(source->text,0,source->charCount);
                source->textIndex = 0;
            }
            return true;

        }

        if(c== KEY_ENTER && !IsKeyDown(KEY_LEFT_SHIFT)){
            source->isTyping = false;
            return false;
        }
        Vector2 textSize = MeasureTextEx(globalFont,source->text,source->textSize,GETSPACING(source->textSize));
        if(c==KEY_BACKSPACE){
            if(source->textIndex>0){
                source->textIndex--;
                source->text[source->textIndex] = 0;
            }
            if(textSize.x < source->rect.width && textSize.y < source->rect.height*.9){
                source->textSize /=0.8f;
            }
            return true;
        }
        else if(source->textIndex < source->charCount-1 && c != 0 && c!= KEY_LEFT_SHIFT){
            if(!IsKeyDown(KEY_LEFT_SHIFT)){
                c = c | 0x20;
            }
            if(c==KEY_ENTER){
                c = '\n';
                printf("newline detected\n");
            }

            source->text[source->textIndex] = (char)c;
            source->textIndex++;
            if(textSize.x >= source->rect.width && textSize.y >= source->rect.height*.9){
                source->textSize *=0.8f;
            }
        }
        return true;

    }
    if(CheckCollisionPointRec(GetMousePosition(),source->rect)){
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            source->isTyping = true;
            return true;
        }

    }

    return false;
}