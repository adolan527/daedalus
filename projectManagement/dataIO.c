//
// Created by Aweso on 1/6/2024.
//
#include "projectManagement.h"

int readColors(){
    FILE *colors = fopen("colors.dat","rb");
    if(colors == NULL){
        return 1;
    }
    for(int i = 0;i < PALETTE_COUNT && !feof(colors); i++){

        if(fread(&palettes[i],sizeof(ColorPalette ),1,colors) != 1){
            fclose(colors);
            return 0;
        }
    }
    fclose(colors);
    return 0;
}

int readMaterials(){
    FILE *materials = fopen("materials.dat","rb");
    if(materials == NULL){
        return 1;
    }
    for(int i = 0;i < MATERIALS_COUNT && !feof(materials); i++){
        if( fread(tqcMaterials[i].name,NAMESIZE,1,materials)!=1 ||
            fread(&tqcMaterials[i].density,sizeof(double),1,materials) != 1 ||
            fread(&tqcMaterials[i].color,sizeof(Color),1,materials) != 1){
            fclose(materials);
            return 0;
        }

    }
    fclose(materials);
    return 0;
}

int readObjects(){
    int retVal = 0;
    currentProject.objList = initObjectList();
    char filename[100] = {0};
    sprintf(filename,"projects/%s/objects.dat",currentProject.name);
    FILE *objects = fopen(filename,"rb");
    if(objects == NULL){
        return 1;
    }
    for(int i = 0;!feof(objects); i++){
        char nameBuf[NAMESIZE] = {0};
        if(fread(nameBuf,NAMESIZE,1,objects)!=1){
            fclose(objects);
            return 0;
        }
        Object *tempObject = malloc(sizeof(Object));
        memcpy(tempObject->name,nameBuf,NAMESIZE);
        if(fread(&tempObject->xPos,(sizeof(Object)-NAMESIZE),1,objects)!=1) retVal++;
        if(retVal!=0){
            fclose(objects);
            free(tempObject);
            printf("%d errors\n",retVal);
            return retVal;

        }
        for(int j = 0;j<MATERIALS_COUNT && tqcMaterials[j].name[0]!=0;j++){
            printf("|%s| - |%s|\n",tempObject->material.name,tqcMaterials[j].name);
            if(strcmp(tempObject->material.name,tqcMaterials[j].name)==0){
                tempObject->material = tqcMaterials[j];
                printf("Material matched\n");
                break;
            }
        }
        appendObject(&currentProject.objList,tempObject);

        /*
        if(fread(&tempObject->xPos.constant,sizeof(double),1,objects)!=1) retVal++;
        if(fread(&tempObject->xPos.meter,sizeof(double),1,objects)!=1) retVal++;
        if(fread(&tempObject->yPos,sizeof(double),1,objects)!=1) retVal++;
        if(fread(&tempObject->zPos,sizeof(double),1,objects)!=1) retVal++;
        if(fread(&tempObject->type,sizeof(ShapeType),1,objects)!=1) retVal++;
        if(fread(&tempObject->data,sizeof(tqcShape),1,objects)!=1) retVal++;
        if(fread(&tempObject->material,sizeof(tqcMaterial),1,objects)!=1) retVal++;
        if(retVal!=0){
            fclose(objects);
            free(tempObject);
            printf("%d errors\n",retVal);
            return retVal;

        }
        appendObject(&currentProject.objList,tempObject);
        */
    }
    fclose(objects);
    return 0;
}

int writeObjects(ObjectList *objectsList){

    FILE *objects = fopen(TextFormat("projects/%s/objects.dat",currentProject.name),"wb");
    if(objects == NULL){
        return 1;
    }
    for(ObjectNode *objNode = objectsList->head;objNode!=NULL;objNode=objNode->next){
        if(fwrite(objNode->data,sizeof(Object),1,objects)!=1){
            fclose(objects);
            return 1;
        }
    }

    fclose(objects);
    return 0;
}


int writeColors() {
    FILE *colors = fopen("colors.dat", "wb");
    if (colors == NULL) {
        return 1;
    }
    for (int i = 0; i < PALETTE_COUNT && !feof(colors); i++) {

        if (fwrite(&palettes[i], sizeof(ColorPalette), 1, colors) != 1) {
            fclose(colors);
            return 1;
        }
    }
    fclose(colors);
    return 0;
}


int writeMaterials(){
    FILE *materials = fopen("materials.dat","wb");
    if(materials == NULL){
        return 1;
    }
    for(int i = 0;i < MATERIALS_COUNT && !feof(materials); i++){
        if( fwrite(tqcMaterials[i].name,NAMESIZE,1,materials)!=1 ||
            fwrite(&tqcMaterials[i].density,sizeof(double),1,materials) != 1 ||
            fwrite(&tqcMaterials[i].color,sizeof(Color),1,materials) != 1){
            fclose(materials);
            return 1;
        }

    }
    fclose(materials);
    return 0;
}
