/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "drawMain.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Shared Variables Definition (global)
// NOTE: Those variables are shared between modules through screens.h
//----------------------------------------------------------------------------------
GameScreen currentScreen = LOGO;


//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------


// Required variables to manage screen transitions (fade-in, fade-out)
static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;
static bool exitWindow = false;
static bool exitRequest = false;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void ChangeToScreen(int screen);     // Change to screen, no transition effect

static void TransitionToScreen(int screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

static int UpdateDrawFrame(void);          // Update and draw one frame



//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int drawMain(GameScreen startingScreen)
{

    int returnValue = 0;
    // Initialization
    //---------------------------------------------------------

    // Load global data (assets that must be available in all screens, i.e. font)
    if(drawLogo == 'f' && startingScreen == LOGO){
        startingScreen = TITLE;
    }

    // Setup and init first screen
    currentScreen = startingScreen;

    switch (currentScreen)
    {
        case LOGO: InitLogoScreen(); break;
        case TITLE: InitTitleScreen(); break;
        case SETTINGS: InitSettingsScreen(); break;
        case PROJECTMAIN: InitProjectMainScreen(); break;
        case EDITOBJECT: InitEditObjectScreen(); break;
        case OPENPROJECT: InitOpenProjectScreen(); break;
        default: break;
    }
    InitLogoScreen();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while(!exitWindow){
        if(WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitRequest = true;

        if(UpdateDrawFrame()==1){
            returnValue = 1;
            break;
        }
    }



#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload current screen data before closing
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case SETTINGS: UnloadSettingsScreen(); break;
        case PROJECTMAIN: UnloadProjectMainScreen(); break;
        case EDITOBJECT: UnloadEditObjectScreen(); break;
        case OPENPROJECT: UnloadOpenProjectScreen(); break;
        default: break;
    }

    // Unload global data loaded
    UnloadMaterialsTextures();
    UnloadFont(globalFont);
    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return returnValue;
}

//----------------------------------------------------------------------------------
// Module specific Functions Definition
//----------------------------------------------------------------------------------
// Change to next screen, no transition
static void ChangeToScreen(GameScreen screen)
{
    // Unload current screen
    switch (currentScreen)
    {
        case LOGO: UnloadLogoScreen(); break;
        case TITLE: UnloadTitleScreen(); break;
        case SETTINGS: UnloadSettingsScreen(); break;
        case PROJECTMAIN: UnloadProjectMainScreen(); break;
        case EDITOBJECT: UnloadEditObjectScreen(); break;
        case OPENPROJECT: UnloadOpenProjectScreen(); break;
        default: break;
    }

    // Init next screen
    switch (screen)
    {
        case LOGO: InitLogoScreen(); break;
        case TITLE: InitTitleScreen(); break;
        case SETTINGS: InitSettingsScreen(); break;
        case PROJECTMAIN: InitProjectMainScreen(); break;
        case EDITOBJECT: InitEditObjectScreen(); break;
        case OPENPROJECT: InitOpenProjectScreen(); break;
        default: break;
    }

    currentScreen = screen;
}

// Request transition to next screen
static void TransitionToScreen(GameScreen screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

// Update transition effect (fade-in, fade-out)
static void UpdateTransition(void)
{
    if (!transFadeOut)
    {
        transAlpha += 0.10f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            switch (transFromScreen)
            {
                case LOGO: UnloadLogoScreen(); break;
                case TITLE: UnloadTitleScreen(); break;
                case SETTINGS: UnloadSettingsScreen(); break;
                case PROJECTMAIN: UnloadProjectMainScreen(); break;
                case EDITOBJECT: UnloadEditObjectScreen(); break;
                case OPENPROJECT: UnloadOpenProjectScreen(); break;
                default: break;
            }

            // Load next screen
            switch (transToScreen)
            {
                case LOGO: InitLogoScreen(); break;
                case TITLE: InitTitleScreen(); break;
                case SETTINGS: InitSettingsScreen(); break;
                case PROJECTMAIN: InitProjectMainScreen(); break;
                case EDITOBJECT: InitEditObjectScreen(); break;
                case OPENPROJECT: InitOpenProjectScreen();break;
                default: break;
            }

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else  // Transition fade out logic
    {
        transAlpha -= 0.05f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = UNKNOWN;
        }
    }
}

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, transAlpha));
}

// Update and draw game frame
static int UpdateDrawFrame(void)
{
    // Update
    //----------------------------------------------------------------------------------
    if(exitRequest){
        if (IsKeyPressed(KEY_Y)){
            exitWindow = true;
        }
        else if (IsKeyPressed(KEY_N)||IsKeyPressedRepeat(KEY_ESCAPE)) {
            exitRequest = false;
        }
    }
    else if (!onTransition)
    {
        switch(currentScreen)
        {
            case LOGO:
            {
                UpdateLogoScreen();

                if (FinishLogoScreen()) TransitionToScreen(TITLE);

            } break;
            case TITLE:
            {
                UpdateTitleScreen();
                if(FinishTitleScreen()!=-1){
                    TransitionToScreen(FinishTitleScreen());
                }

            } break;
            case SETTINGS:
            {
                UpdateSettingsScreen();
                if(FinishSettingsScreen()==REINIT)return 1;
                if(FinishSettingsScreen()!=-1){
                    TransitionToScreen(FinishSettingsScreen());
                }

            } break;

            case PROJECTMAIN:
            {
                UpdateProjectMainScreen();
                if(FinishProjectMainScreen()!=-1){
                    if(FinishProjectMainScreen()==OPENPROJECT){
                        ChangeToScreen(OPENPROJECT);
                    }
                    else{
                        TransitionToScreen(FinishProjectMainScreen());
                    }

                }

            } break;
            case EDITOBJECT:
            {
                UpdateEditObjectScreen();
                if(FinishEditObjectScreen()!=-1){
                    TransitionToScreen(FinishEditObjectScreen());
                }
            }
            case OPENPROJECT:
            {
                UpdateOpenProjectScreen();
                if(FinishOpenProjectScreen()!=-1){
                    if(FinishOpenProjectScreen() == PROJECTMAIN){
                        ChangeToScreen(PROJECTMAIN);
                    }
                    else{
                        TransitionToScreen(FinishOpenProjectScreen());
                    }
                }
            }
            default: break;
        }

    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(theme.white);

    switch(currentScreen)
    {
        case LOGO: DrawLogoScreen(); break;
        case TITLE: DrawTitleScreen(); break;
        case SETTINGS: DrawSettingsScreen(); break;
        case PROJECTMAIN: DrawProjectMainScreen(); break;
        case EDITOBJECT: DrawEditObjectScreen(); break;
        case OPENPROJECT: DrawOpenProjectScreen(); break;
        default: break;
    }

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();

    //DrawFPS(screenWidth/2, 100);


    if(exitRequest){
        DrawRectangle(0,0,screenWidth,screenHeight,(Color){theme.black.r,theme.black.g,theme.black.b,200});
        DrawText("Confirm exit: [Y/N]",screenWidth/4,screenHeight/2,screenHeight/10,theme.accent1);

    }

    EndDrawing();
    //----------------------------------------------------------------------------------
    return 0;
}
