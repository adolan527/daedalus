//
// Created by Aweso on 12/16/2023.
//

#ifndef TORQUECALCULATOR_FILEMANAGEMENT_H
#define TORQUECALCULATOR_FILEMANAGEMENT_H



#include <sys/stat.h>
#include "../main.h"

int doesProjectExist(char *name);

int readColors();

int readMaterials(MaterialList *list);

int readObjects();
#endif //TORQUECALCULATOR_FILEMANAGEMENT_H
