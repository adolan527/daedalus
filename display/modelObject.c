//
// Created by Aweso on 1/4/2024.
//
#include "drawMain.h"

void ReModelObject(Object *obj){
    UnloadModel(*obj->model);
    free(obj->model);
    ModelObject(obj);
}

void ModelObject(Object *obj){
    Vector3 rotation = {0};
    Mesh tempMesh = {0};
    switch (obj->type){

        case sRectangle:{

            tempMesh = GenMeshCube(obj->data.xLength,obj->data.yHeight,obj->data.zDepth);
            break;

        }
        case sCylinder:{
            switch(obj->data.facing){
                case 'x':{
                    rotation.z = DEG2RAD * -90;
                    tempMesh = GenMeshCylinder(obj->data.yHeight,obj->data.xLength,CYLINDERRING);
                    break;
                }
                case 'y':{
                    tempMesh = GenMeshCylinder(obj->data.xLength,obj->data.yHeight,CYLINDERRING);
                    break;

                }
                case 'z':{
                    rotation.x = DEG2RAD * 90;
                    tempMesh = GenMeshCylinder(obj->data.xLength,obj->data.zDepth,CYLINDERRING);
                    break;
                }

            }
            break;
        }
        case sSphere:{
            tempMesh = GenMeshSphere(obj->data.xLength,20,20);
        }
    }

    obj->model = malloc(sizeof(Model));
    if(obj->model==NULL) {
        printf("Error allocating memory\n");
    }
    *obj->model = LoadModelFromMesh(tempMesh);
    obj->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = obj->material.texture;
    obj->model->materials[0].maps[MATERIAL_MAP_DIFFUSE].color = obj->material.color;
    obj->model->transform = MatrixRotateXYZ(rotation);
    if(obj->type == sRectangle){
        obj->box.min.x = obj->xPos.constant;
        obj->box.min.y = obj->yPos;
        obj->box.min.z = obj->zPos;
        obj->box.max.x = obj->xPos.constant + obj->data.xLength;
        obj->box.max.y = obj->yPos + obj->data.yHeight;
        obj->box.max.z = obj->zPos + obj->data.zDepth;
    }
    else{
        // TODO: Bounding box on cylinders that are not facing the y axis is messed up
        obj->box = GetModelBoundingBox(*obj->model);
        obj->box.min.x+=obj->xPos.constant;
        obj->box.min.y+=obj->yPos;
        obj->box.min.z+=obj->zPos;
        obj->box.max.x+=obj->xPos.constant;
        obj->box.max.y+=obj->yPos;
        obj->box.max.z+=obj->zPos;
    }


}
