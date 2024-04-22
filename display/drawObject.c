//
// Created by Aweso on 12/31/2023->
//
#include "drawMain.h"
void DrawObject(Object *source, float pmt){
    switch(source->type){
        case sRectangle:
            if(source->data.thickness==0){
                DrawModel(*source->model,(Vector3){pmt * source->xPos.meter + source->data.xLength/2,source->data.yHeight/2,source->data.zDepth/2},1,source->material.color);

                //DrawModel(tempModel,GetObjectPosition(source,pmt,theta),1,source->material.color);


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

                    if(source->data.thickness!=0){
                        DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius-source->data.thickness,(Vector3){0,1,0},90,theme.black);
                        DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt) + source->data.xLength, source->yPos, source->zPos}, radius-source->data.thickness,(Vector3){0,1,0},90,theme.black);

                    }
                    DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius,(Vector3){0,1,0},90,theme.black);
                    DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt) + source->data.xLength, source->yPos, source->zPos}, radius,(Vector3){0,1,0},90,theme.black);


                    break;
                }
                case 'y': {
                    height = source->data.yHeight;
                    radius = source->data.xLength;
                    if(source->data.thickness!=0){
                        DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius-source->data.thickness,(Vector3){1,0,0},90,theme.black);
                        DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos + source->data.yHeight, source->zPos}, radius-source->data.thickness,(Vector3){1,0,0},90,theme.black);

                    }
                    DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius,(Vector3){1,0,0},90,theme.black);
                    DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos + source->data.yHeight, source->zPos}, radius,(Vector3){1,0,0},90,theme.black);

                    break;

                }
                case 'z': {
                    height = source->data.zDepth;
                    radius = source->data.xLength;
                    if(source->data.thickness!=0){
                        DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius-source->data.thickness,(Vector3){1,0,0},0,theme.black);
                        DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos+source->data.zDepth}, radius-source->data.thickness,(Vector3){1,0,0},0,theme.black);

                    }
                    DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos}, radius,(Vector3){1,0,0},0,theme.black);
                    DrawCircle3D((Vector3) {cmpPmt(source->xPos, pmt), source->yPos, source->zPos+source->data.zDepth}, radius,(Vector3){1,0,0},0,theme.black);

                    break;
                }

            }
            DrawModel(*source->model,(Vector3){pmt * source->xPos.meter,0,0},1,source->material.color);

            break;
        }
        case sSphere:
            DrawModel(*source->model,(Vector3){pmt * source->xPos.meter,0,0},1,source->material.color);
            //DrawModel(tempModel,(Vector3){cmpPmt(source->xPos, pmt), source->yPos, source->zPos},1,source->material.color);

            break;
    }
}