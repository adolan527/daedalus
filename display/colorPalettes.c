//
// Created by Aweso on 12/25/2023.
//
#include "drawMain.h"

ColorPalette palettes[10] ={
        {//basic
                RAYWHITE,BLACK,SKYBLUE,DARKGRAY,DARKGREEN,MAROON
        },
        {//advanced red/yellow/green/white
                RAYWHITE,
                BLACK,
                (Color){112, 141, 129,255},
                (Color){0, 20, 39,255},
                (Color){244, 213, 141,255},
                (Color){191, 6, 3,255}
        },
        {//yoda
                RAYWHITE,
                DARKGRAY,
                (Color){255, 232, 214,255},
                (Color){203, 153, 126,255},
                (Color){107, 112, 92,255},
                (Color){165, 165, 141,255}
        },
        {//colorful
                LIGHTGRAY,
                (Color){122, 123, 123,255},
                (Color){32, 65, 247,255},
                (Color){162, 60, 223,255},
                (Color){238, 66, 66,255},
                (Color){100, 181, 127,255}
        },
        {//red and yellow
                (Color){255, 238, 202,255},
                (Color){68, 68, 68,255},
                (Color){255, 176, 0,255},
                (Color){204, 18, 18,255},
                (Color){87, 23, 16,255},
                (Color){153, 153, 153,255}
        },
        {//Dark purple
                LIGHTGRAY,
                (Color){17, 0, 28,255},
                (Color){53, 1, 44,255},
                (Color){41, 0, 37,255},
                (Color){79, 1, 71,255},
                (Color){58, 1, 92,255}
        },
        {//Dark and red
                (Color){15,15,15,255},
                (Color){167, 157, 156,255},
                (Color){102, 7, 8,255},
                (Color){255, 226, 200,255},
                (Color){232, 93, 4,255},
                (Color){141, 153, 174,255}
        }


};