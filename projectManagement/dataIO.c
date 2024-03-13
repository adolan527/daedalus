//
// Created by Aweso on 1/6/2024.
//
#include "projectManagement.h"

int readColors(){
    FILE *colors = fopen("resources/colors.dat","rb");
    if(colors == NULL){
        return 1;
    }
    for(int i = 0;i < PALETTE_COUNT && !feof(colors); i++){

        if(fread(&palettes[i], sizeof(ColorPalette ), 1, colors) != 1){
            fclose(colors);
            return 0;
        }
    }
    fclose(colors);
    return 0;
}

int readMaterials(MaterialList *list){
    FILE *materials = fopen("resources/materials.dat","rb");
    if(materials == NULL){
        return 1;
    }
    while(!feof(materials)){
        tqcMaterial *new = calloc(1,sizeof(tqcMaterial));
        if( fread(new->name,NAMESIZE,1,materials)!=1 ||
            fread(&new->density,sizeof(double),1,materials) != 1 ||
            fread(&new->color,sizeof(Color),1,materials) != 1){
            free(new);
            fclose(materials);
            return 0;
        }
        if(strcmp(DEFAULTMATERIALNAME,new->name)==0){
            free(new);
        }
        else{
            appendMaterial(list,new);

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
        MaterialNode *ptr = tqcMaterials.head;
        while(ptr){
            if(strcmp(tempObject->material.name,ptr->data->name)==0){
                tempObject->material = *ptr->data;
                printf("Material matched\n");
                break;
            }
            ptr = ptr->next;
        }

        appendObject(&currentProject.objList,tempObject);

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
    FILE *colors = fopen("resources/colors.dat", "wb");
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


int writeMaterials(MaterialList *source){
    int counter = 0;
    FILE *materials = fopen("resources/materials.dat","wb");
    if(materials == NULL){
        return 1;
    }
    MaterialNode *ptr = tqcMaterials.head;
    while(ptr){
        if(strcmp(DEFAULTMATERIALNAME,ptr->data->name)!=0){
            if( fwrite(ptr->data->name,NAMESIZE,1,materials)!=1 ||
                fwrite(&ptr->data->density,sizeof(double),1,materials) != 1 ||
                fwrite(&ptr->data->color,sizeof(Color),1,materials) != 1){
                fclose(materials);
                return 1;
            }
        }
        ptr = ptr->next;
        counter++;
    }

    fclose(materials);
    return 0;
}
