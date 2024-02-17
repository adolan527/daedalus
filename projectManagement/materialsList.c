//
// Created by Aweso on 12/26/2023.
//
#include "projectManagement.h"
MaterialList tqcMaterials = {NULL,NULL};

void LoadMaterialsTextures(MaterialList *list){
    MaterialNode *ptr = list->head;
    while(ptr){
        ptr->data->texture = LoadTexture(TextFormat("resources/textures/%s.png",ptr->data->name));
        ptr = ptr->next;
    }
}

void UnloadMaterialsTextures(MaterialList *list){
    MaterialNode *ptr = list->head;
    while(ptr){
        UnloadTexture(ptr->data->texture);
        ptr = ptr->next;
    }
}



int isMaterialInList(MaterialList *list, tqcMaterial *source){
    int i = 0;
    for(MaterialNode *node = list->head; node != NULL; node = node->next){
        if(node->data == source){
            return i;
        }

        i++;
    }
    return -1;
}

MaterialList initMaterialList(){
    return (MaterialList){NULL,NULL};
}

int getMaterialCount(MaterialList *source){
    int size = 0;
    for(MaterialNode *current = source->head; current != NULL; current = current->next){
        size++;
    }
    return size;
}

void appendMaterial(MaterialList *source, tqcMaterial *data){
    MaterialNode *new = malloc(sizeof(MaterialNode));
    new->data = data;
    new->next = NULL;
    if(source->tail != NULL) source->tail->next = new;
    if(source->head == NULL) source->head = new;
    source->tail = new;
}

void closeMaterialList(MaterialList *source){
    if(source->head == NULL) return;
    while(source->head){

        MaterialNode *temp = source->head;
        source->head = source->head->next;
        UnloadTexture(temp->data->texture);

        if(temp->data!=NULL){
            free(temp->data);
        }

        free(temp);
    }

}

tqcMaterial* getMaterialPointer(MaterialList *source, int index){
    int currentIndex = 0;
    for(MaterialNode* current = source->head; current->next != NULL; current = current->next){
        if(index == currentIndex){
            return current->data;
        }
        currentIndex++;
    }
    return NULL;
}

void refreshMaterialList(MaterialList *list){
    writeMaterials(list);
    closeMaterialList(list);
    readMaterials(list);


}


void deleteMaterial(MaterialList *source, int index){
    if(index == 0){
        MaterialNode *temp = source->head;
        source->head = source->head->next;
        UnloadTexture(temp->data->texture);
        free(temp->data);
        free(temp);
        return;
    }
    int currentIndex = 0;
    MaterialNode *target = NULL;
    for(MaterialNode *current = source->head; current->next != NULL; current = current->next){
        if(currentIndex == index - 1){
            target = current->next;
            current->next = current->next->next;
            UnloadTexture(target->data->texture);
            free(target->data);
            free(target);
            return;
        }
        currentIndex++;
    }
}

void insertMaterial(MaterialList *source, tqcMaterial *data, int index){
    MaterialNode *new = malloc(sizeof(MaterialNode));
    new->data = data;
    if(index == 0){
        new->next = source->head;
        source->head = new;
        return;
    }
    int currentIndex = 0;
    for(MaterialNode *current = source->head; current->next != NULL; current = current->next){
        if(currentIndex == index - 1){
            new->next = current->next;
            current->next = new;
            if(new->next==NULL){
                source->tail = new;
            }
            return;
        }
        currentIndex++;
    }
}


