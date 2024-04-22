#include "main.h"
#include "display/drawMain.h"

int projectCount = 0;

Project currentProject = {0};

ColorPalette palettes[PALETTE_COUNT] ={

        {// basic/defualt color palette if none are loaded
                RAYWHITE,BLACK,SKYBLUE,DARKGRAY,DARKGREEN,MAROON
        }/*,
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


int main(int argc, char **argv){

    if(initProgram()!=0){
        printf("Init failed");
        return 0;
    }
    if(initDraw()!=0){
        printf("Init draw failed");
        return 0;
    }

    GameScreen startingScreen = LOGO;
    //I don't like having this much logic in main, but this is a minor last minute addition
    if(argc>1){
        char *substr = strstr(argv[1],"projects\\");;
        if(substr==NULL){
            //arg is a project name
            if(!doesProjectExist(argv[1])){
                createProject(argv[1],(argc > 2 ? argv[2] : ""));
            }
            openProject(argv[1]);
            startingScreen = PROJECTMAIN;
        }
        else{
            //If arg is a path
            char name[NAMESIZE+1] = {0};
            char* endOfName = strchr(substr+9,'\\');
            if(endOfName!=NULL){
                strncpy(name,substr+9,endOfName-substr-9);
                openProject(name);
                startingScreen = PROJECTMAIN;
            }
        }
    }


    if(drawMain(startingScreen)==1){
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
