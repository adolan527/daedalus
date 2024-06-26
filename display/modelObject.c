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
            if(obj->data.thickness==0){
                tempMesh = GenMeshCube(obj->data.xLength,obj->data.yHeight,obj->data.zDepth);
            }
            else{
                tempMesh = GenMeshRectTube(obj);
            }

            break;

        }
        case sCylinder:{
            if(obj->data.thickness!=0){
                tempMesh = GenMeshRoundTube(obj);
            }
            else {
                switch (obj->data.facing) {
                    case 'x': {
                        rotation.z = DEG2RAD * -90;
                        tempMesh = GenMeshCylinder(obj->data.yHeight, obj->data.xLength, CYLINDERRING);
                        break;
                    }
                    case 'y': {
                        tempMesh = GenMeshCylinder(obj->data.xLength, obj->data.yHeight, CYLINDERRING);
                        break;

                    }
                    case 'z': {
                        rotation.x = DEG2RAD * 90;
                        tempMesh = GenMeshCylinder(obj->data.xLength, obj->data.zDepth, CYLINDERRING);
                        break;
                    }

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
    obj->model->transform = MatrixMultiply(MatrixRotateXYZ(rotation), MatrixTranslate(obj->xPos.constant,obj->yPos,obj->zPos));


}
