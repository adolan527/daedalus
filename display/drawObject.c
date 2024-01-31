//
// Created by Aweso on 12/31/2023->
//
#include "drawMain.h"
void DrawObject(Object *source, float pmt){
    switch(source->type){
        case sRectangle:
            if(source->data.thickness==0){
                DrawModel(*source->model,(Vector3){pmt * source->xPos.meter + source->data.xLength/2,source->data.yHeight/2,source->data.zDepth/2},1,source->material.color);

            }
            else{
                DrawModel(*source->model,(Vector3){pmt * source->xPos.meter,0,0},1,source->material.color);
            }

            DrawCubeWires((Vector3){cmpPmt(source->xPos, pmt) + source->data.xLength / 2.0f, source->yPos + source->data.yHeight / 2.0f, source->zPos + source->data.zDepth / 2.0f},
                          source->data.xLength, source->data.yHeight, source->data.zDepth, theme.black);
            break;
        case sCylinder: {
            float radius, height;
            switch (source->data.facing) {
                case 'x': {
                    height = source->data.xLength;
                    radius = source->data.yHeight;
                    DrawCylinderWiresEx((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos},
                                        (Vector3) {cmpPmt(source->xPos, pmt) + source->data.xLength, source->yPos, source->zPos},
                                        radius, radius,
                                        CYLINDERRING, source->material.color);
                    break;
                }
                case 'y': {
                    height = source->data.yHeight;
                    radius = source->data.xLength;
                    DrawCylinderWiresEx((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos},
                                        (Vector3) {cmpPmt(source->xPos, pmt), source->yPos + source->data.yHeight, source->zPos},
                                        radius, radius,
                                        CYLINDERRING, source->material.color);
                    break;

                }
                case 'z': {
                    height = source->data.zDepth;
                    radius = source->data.xLength;
                    DrawCylinderWiresEx((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos},
                                        (Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos + source->data.zDepth},
                                        radius, radius,
                                        CYLINDERRING, source->material.color);
                    break;
                }

            }
            DrawModel(*source->model,(Vector3){pmt * source->xPos.meter,0,0},1,source->material.color);
            //DrawModel(*source->model, (Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, 1,
             //         source->material.color);
            //DrawCylinderWires((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius, radius, height,
              //                CYLINDERRING, source->material.color);


            break;
        }
        case sSphere:
            DrawModel(*source->model,(Vector3){pmt * source->xPos.meter,0,0},1,source->material.color);
            //DrawModel(*source->model,(Vector3){cmpPmt(source->xPos, pmt), source->yPos, source->zPos},1,source->material.color);

            break;
    }
}