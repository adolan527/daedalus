# What is Daedalus?

TL;DR - A rudimentary CAD program made with Raylib and C.

To better learn the C language and the (amazing) Raylib graphics API, I set myself the goal of developing a CAD program to simplify common calculations done when designing
mechanical systems, particularly to appeal to FRC teams. Specifically, calculating torque on an axis and anything with aluminum rectangular tubing. 
While the program does accomplish this goal, the other things I learned as a result are arguably more significant.

- File IO for applications utilizing multiple directories/files.
- Structuring a codebase into multiple encapsulated modules
- Managing application state across files and closing/opening the application
- Dynamic mesh generation by uploading vertices to VRAM
- Basic shaders and GLSL
- Principles of UI
     - How to relate a GUI to data/application state and vice versa
     - Making UI feel response
     - Customizability/configurability by the user
     - UI API through standardized inputs and outputs on different features
- 3D graphics
- Safe memory management in C

Additionally, as all of this was done in C, I can now appreciate some of the abstractions that C++ offers. Templates alone would have saved hours on this project.


A working executable can be found [here](https://github.com/adolan527/daedalus/blob/main/cmake-build-debug/daedalus.exe)
The program does create one directory and two files in whatever directory you put it in.


# 



## Guide to Running
1. Download the .exe [here:](https://github.com/adolan527/daedalus/blob/main/cmake-build-debug/daedalus.exe)
2. Create a directory/folder and put the .exe into said directory.
3. Run the program

The .exe will create all of the necessary subdirectories and files when it initializes itself.
See below for information on the customization of the program and its appearance.

# Program File Structure
## daedalus.exe
The main executable. It can be called from the command line, where the first argument is the name or directory of the project you want to open.
Ex: `>daedalus.exe project1`

## config.dat and error.log
These two files are created in the same directory as the executable. config.dat is formatted as such:
```
daedalus //Mandatory Header
res:WIDTHxHEIGHT 
window:WINDOWMODE
logo:BOOL
theme:PALETTEINDEX
```
WIDTH and HEIGHT are self explanatory. Ex: 1920x1080.
WINDOWMODE is one of: *w*, *b*, or *f*. Windowed, borderless, or fullscreen.
BOOL is either *t* or *f*. If true, then the Raylib logo is drawn on startup.
PALETTEINDEX is an int. It is the index in the array that holds all of the color palettes/themes. Out-of-bounds indexing is an undefined behavior.

None of these values need to be changed through the file manually, as the program provides interfaces for changing all of these values. The exception is weird resolution ratios.

error.log is not implemented. It is never written to or read from. It is only referenced the first time the program is run. 
The RayLib console TraceLogs are sufficient for detecting errors, but in the future, those could be redirected to this file.

## Projects
Contains a folder for each project, in addition to a **projects.dat** file.
projects.dat is a list of all of the projects, as generated by the Windows command "dir /b/a:d > projects.dat". 

### Project folder
Folder with the same name as the project. Contains **info.dat** and **objects.dat**. info.dat contains the following information in the following format:
Name: NAME
Notes: NOTES
objects.dat contains the binary data for all of the objects in that project. This should not edited.

## Resources
The resources folder that the program generates contains many of the assets that the program uses. Although not necessary they make it look much nicer.
**For the best experience, copy this repository's resources folder in place of your own**

### Fonts
In the fonts folder, a **main** and **title** file can be placed to affect the fonts in those locations. On this repository, you can find the ones I used.
Both **.ttf** and **.otf** are accepted.

### Shaders
The program only expects a light shader that is defined by the **lighting.vs** and **lighting.fs** files contained in this repository. Anything not following these names
will be ignored, and using shader files other than the ones contained in this repository will is undefined behavior.
Note: These shaders were copied from the [Raylib basic lighting example](https://github.com/raysan5/raylib/blob/master/examples/shaders/shaders_basic_lighting.c).

### Textures
The textures folder contains **.png** files matching the names of the materials in the program, and uses these images as textures.
If you have a material named "Steel", you should have a file name **Steel.png** in the textures folder (or else it will use the default texture).

### Colors and Materials
These two **.dat** files are stored in a binary format. colors.dat contains all of the palettes stored contiguously (each palette is 10 colors, and each color is 4 bytes RGBA).

Note: If you see "torqueCalculator" or "GeneralizedRobotArm" mentioned anywhere please make an issue of it. Those were the previous names for this project. They should all have been updated to say Daedalus by now, but CLion makes renaming projects difficult.

