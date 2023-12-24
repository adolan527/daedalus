//
// Created by Aweso on 12/22/2023.
//
#include "projectManagement.h"

int closeProject(Project *source){
    closeCSV(&source->objects);
    fclose(source->info);
    return 0;
}