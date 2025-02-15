//
// Created by Aweso on 12/16/2023.
//

#ifndef DAEDALUS_FILEMANAGEMENT_H
#define DAEDALUS_FILEMANAGEMENT_H



#include <sys/stat.h>
#include "../main.h"
#define DEFAULTMATERIALNAME "DEFAULT"


int readColors();

int readMaterials(MaterialList *list);

int readObjects();
#endif //DAEDALUS_FILEMANAGEMENT_H
