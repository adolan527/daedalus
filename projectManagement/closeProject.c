//
// Created by Aweso on 12/22/2023.
//
#include "projectManagement.h"

int closeProject(Project *source){
    closeCSV(&source->objCSV);
    fclose(source->info);
    return 0;
}