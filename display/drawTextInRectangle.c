//
// Created by Aweso on 12/30/2023.
//
#include "drawMain.h"


#define CHAR_PER_LINE 30

void DrawTextInRectangle(char *text, Rectangle rect, int rowCount, Color textColor, Color background, Color border) {
    DrawRectangleRec(rect,background);
    DrawRectangleLinesEx(rect,rect.height/50,border);
    rowCount++;
    char buffer[CHAR_PER_LINE + 1] = {0};
    int length = strlen(text);
    int row = 0;

    for (int i = 0; i < length; i++) {
        int j;
        for (j = 0; i + j < length && j <= CHAR_PER_LINE && text[i + j] != 0 && text[i + j] != '\n'; j++) {
            buffer[j] = text[i + j];
        }
        buffer[j] = '\0';
        DrawTextEx(globalFont,buffer,(Vector2){rect.x + rect.width * 0.05, rect.y + rect.height * (((float)row / (float)rowCount) + 0.075)},rect.height / (float)rowCount,(rect.height / (float)rowCount < 10 ? 1 : rect.height / (float)rowCount/10),textColor);
        memset(buffer, 0, CHAR_PER_LINE + 1);
        i += j;
        row++;
        if(row==rowCount-1)return;
    }
}