#include "main.h"
#include "display/drawMain.h"

int projectCount = 0;

Project currentProject = {0};

tqcMaterial tqcMaterials[MATERIALS_COUNT] = {
/*
        {"6061-Aluminum", 0.09754374,LIGHTGRAY, {0}},
        {"6063-Aluminum", 0.09718247,LIGHTGRAY, {0}},
        {"Steel", 0.283599,DARKGRAY, {0}},
        {"Pine-Wood", 0.01987002,(Color){240, 215, 93,255}, {0}},
        {"Polycarbonate", 0.04335278,(Color){ 245, 245, 255, 255 }, {0}},
        {0}
*/
};

ColorPalette palettes[PALETTE_COUNT] ={
        /*
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
         */
};

static Object dummy = {
        "Dummy",
        {0,1},
        0,5,

        {10,5,7,0,'x',false},
        sRectangle,
        (tqcMaterial){0},
        NULL
};
static Object cylinder = {
        "Cylinder",
        {5,-2},
        3,-1,

        {1,7,1,0,'y',false},
        sCylinder,
        (tqcMaterial){0},
        NULL
};
static Object sphere = {
        "Sphere",
        {-10,1},
        0,1,

        {2,2,2,0,'y',false},
        sSphere,
        (tqcMaterial){0},

        NULL
};

int main(){


/*
    Object d = {
            "abcdefghijklmnopqrstuvwxyz123456",
            (double){0xFFFFFFFF},
            (double){0xEEEE},
            (double){0xDDDD},
            (double){0xCCCC},
            -1235835.0289355f,
            -195823.085320f,
            -1235835.0289355f,
            -195823.085320f,
            'x',
            false,
            (ShapeType){0xBBBBBBBB},
            "abcdefghijklmnopqrstuvwxyz123456",
            -1235835.0289355f,
            244,
            244,
            243,
            243,
            12,
            13,
            14,
            15,
            16,
            NULL
    };

    memset(&d.xPos.constant,0xFF,sizeof(double));
    memset(&d.xPos.meter,0xEE,sizeof(double));
    memset(&d.yPos,0xDD,sizeof(double));
    memset(&d.zPos,0xCC,sizeof(double));
    memset(&d.type,0xBB,sizeof(ShapeType));
    memset(&d.data.xLength,0xAA,sizeof(double));
    memset(&d.data.yHeight,0xbb,sizeof(double));
    memset(&d.data.zDepth,0xcc,sizeof(double));
    memset(&d.data.thickness,0xdd,sizeof(double));
    memset(&d.material.density,0xff,sizeof(double));
    printf("dummy %s",d.name);
    return 0;
    */
    if(initProgram()!=0){
        printf("Init failed");
        return 0;
    }
    if(initDraw()!=0){
        printf("Init draw failed");
        return 0;
    }
    if(drawMain(LOGO)==1){
        if(initDraw()!=0){
            printf("Init draw failed");
            return 0;
        }
        while(drawMain(SETTINGS)==1){
            if(initDraw()==1){
                printf("Init draw failed");
                return 0;
            }
        }
    }

    return 0;


}
