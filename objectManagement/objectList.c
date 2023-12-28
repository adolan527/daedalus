//
// Created by Aweso on 12/26/2023.
//
#include "tqcObjects.h"

ObjectList initObjectList(){
    return (ObjectList){NULL,NULL};
}

void appendObject(ObjectList *source, Object *data){
    ObjectNode *new = malloc(sizeof(ObjectNode));
    new->data = data;
    new->next = NULL;
    source->tail->next = new;
    source->tail = new;
}

void closeObjectList(ObjectList *source){
    if(source->head == NULL) return;
    for(ObjectNode* current = source->head; current->next != NULL; current = current->next){
        free(current->data);
        free(current);
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
}

void deleteObject(ObjectList *source, int index){
    if(index == 0){
        ObjectNode *temp = source->head;
        source->head = source->head->next;
        free(temp->data);
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
            return;
        }
        currentIndex++;
    }
    free(new);
}


