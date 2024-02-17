//
// Created by Aweso on 12/15/2023.
//

#include "projectManagement.h"

const char header[CONFIG_HEADER_SIZE] = "torqueCalculator";

int doesConfigExist(){
    FILE *config = fopen("config.dat","r");
    if(config == NULL){

        return 1;
    }
    char buffer[CONFIG_HEADER_SIZE+1];
    fgets(buffer,CONFIG_HEADER_SIZE,config);
    buffer[CONFIG_HEADER_SIZE] = 0;
    if(strcmp(buffer,header)!=0){
        fclose(config);

        return 1;
    }
    fclose(config);

    return 0;
}

int makeConfig(int width, int height,char wMode,char doLogo){

    FILE *config = fopen("config.dat","w");
    if(config == NULL){
        return 1;
    }
    fputs(header,config);
    //Other config stuff
    //To be implemented
    fprintf(config,"\nres:%dx%d\n",width,height);
    fprintf(config,"window:%c\n",wMode);
    fprintf(config,"logo:%c\n",doLogo);

    fclose(config);
    return 0;
}




int initProgram() {


    int retVal = 0;

    if (doesConfigExist() == 0) {
        //program is already initialized
        getProjectCount();
        tqcMaterials = initMaterialList();
        retVal += readMaterials(&tqcMaterials);
        retVal += readColors();
        return retVal;
    }
    const int defaultWidth = 1480;
    const int defaultHeight = 720;
    const char defaultWMode = 'w';
    const char defaultDoLogo = 't';
    retVal += makeConfig(defaultWidth,defaultHeight,defaultWMode,defaultDoLogo);
    FILE *error = fopen("error.log","w");
    if(error == NULL){
        return 1;
    }
    fclose(error);

    retVal += mkdir("resources/");


    FILE *materials = fopen("resources/materials.dat","w");
    if(materials == NULL){
        return 1;
    }
    fclose(materials);

    FILE *colors = fopen("resources/colors.dat","w");
    if(colors == NULL){
        return 1;
    }
    fclose(colors);

    retVal += mkdir("projects/");
    retVal += mkdir("resources/textures/");
    retVal += mkdir("resources/fonts/");
    retVal += mkdir("resources/shaders/");
    retVal += system("dir /b/a:d projects\\ > projects/projects.dat");

    return retVal;
}

