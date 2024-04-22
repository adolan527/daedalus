//
// Created by Aweso on 12/26/2023.
//
#include "calculations.h"


int isObjectInList(ObjectList *list, Object *source){
    int i = 0;
    for(ObjectNode *node = list->head; node != NULL; node = node->next){
        if(node->data == source){
            return i;
        }

        i++;
    }
    return -1;
}

ObjectList initObjectList(){
    return (ObjectList){NULL,NULL};
}

void appendObject(ObjectList *source, Object *data){
    ObjectNode *new = malloc(sizeof(ObjectNode));
    new->data = data;
    new->next = NULL;
    if(source->tail != NULL) source->tail->next = new;
    if(source->head == NULL) source->head = new;
    source->tail = new;
}

void closeObjectList(ObjectList *source){

    if(source->head == NULL) return;
    while(source->head){
        ObjectNode *temp = source->head;
        source->head = source->head->next;
        if(temp->data->model!=NULL){
            UnloadModel(*temp->data->model);
            free(temp->data->model);
        }
        if(temp->data!=NULL){
            free(temp->data);
        }

        free(temp);
    }

}

Object * getObjectPointer(ObjectList *source, int index){
    int currentIndex = 0;
    for(ObjectNode* current = source->head; current->next != NULL; current = current->next){
        if(index == currentIndex){
            return current->data;
        }
        currentIndex++;
    }
    return NULL;
}

void deleteObject(ObjectList *source, int index){
    if(index == 0){
        ObjectNode *temp = source->head;
        source->head = source->head->next;
        free(temp->data);
        UnloadModel(*temp->data->model);
        free(temp);
        return;
    }
    int currentIndex = 0;
    ObjectNode *target = NULL;
    for(ObjectNode *current = source->head; current->next != NULL; current = current->next){
        if(currentIndex == index - 1){
            target = current->next;
            current->next = current->next->next;
            free(target->data);
            UnloadModel(*target->data->model);
            free(target);
            return;
        }
        currentIndex++;
    }
}

void insertObject(ObjectList *source, Object *data, int index){
    ObjectNode *new = malloc(sizeof(ObjectNode));
    new->data = data;
    if(index == 0){
        new->next = source->head;
        source->head = new;
        return;
    }
    int currentIndex = 0;
    for(ObjectNode *current = source->head; current->next != NULL; current = current->next){
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


