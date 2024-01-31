//
// Created by Aweso on 1/29/2024.
//
#include "drawMain.h"

#define GEN_MESH_VERTEX(_x,_y,_z,_tc1,_tc2,_i) { \
             \
customMesh.vertices[3*_i] = _x;                           \
customMesh.vertices[3*_i + 1] = _y;   \
customMesh.vertices[3*_i + 2] = _z;   \
\
customMesh.texcoords[2*_i] = _tc1;  \
customMesh.texcoords[2*_i+1] = _tc2;                    \
}

#define ZTRIANGLE(xtriz,ytriz,x2triz,y2triz,ztriz,itriz) { \
                                                \
GEN_MESH_VERTEX(xtriz,ytriz,ztriz,0,0,(3*itriz))                             \
GEN_MESH_VERTEX(x2triz,y2triz,ztriz,1,1,(1 + (3*itriz)))                        \
GEN_MESH_VERTEX(xtriz,y2triz,ztriz,0,0,(2 + (3*itriz)))                                                                  \
}

#define ZCTRIANGLE(xtriz,ytriz,x2triz,y2triz,ztriz,itriz) { \
GEN_MESH_VERTEX(xtriz,ytriz,ztriz,0,0,(3*itriz))            \
GEN_MESH_VERTEX(xtriz,y2triz,ztriz,0,0,(1 + (3*itriz)))                   \
GEN_MESH_VERTEX(x2triz,y2triz,ztriz,1,1,(2 + (3*itriz)))                     \
}

#define XTRIANGLE(ytrix,ztrix,y2trix,z2trix,xtrix,itrix){ \
GEN_MESH_VERTEX(xtrix,ytrix,ztrix,0,0,(3*itrix))                             \
GEN_MESH_VERTEX(xtrix,y2trix,z2trix,1,1,(1 + (3*itrix)))                        \
GEN_MESH_VERTEX(xtrix,y2trix,ztrix,0,0,(2 + (3*itrix)))                                                               \
}

#define XCTRIANGLE(ytrix,ztrix,y2trix,z2trix,xtrix,itrix){ \
GEN_MESH_VERTEX(xtrix,ytrix,ztrix,0,0,(3*itrix))           \
GEN_MESH_VERTEX(xtrix,y2trix,ztrix,0,0,(1 + (3*itrix)))                                             \
GEN_MESH_VERTEX(xtrix,y2trix,z2trix,1,1,(2 + (3*itrix)))                        \
}


#define YTRIANGLE(xtriy,ztriy,x2triy,z2triy,ytriy,itriy){ \
GEN_MESH_VERTEX(xtriy,ytriy,ztriy,0,0,(3*itriy))                             \
GEN_MESH_VERTEX(x2triy,ytriy,z2triy,1,1,(1 + (3*itriy)))                        \
GEN_MESH_VERTEX(x2triy,ytriy,ztriy,0,0,(2 + (3*itriy)))                                                        \
}

#define YCTRIANGLE(xtriy,ztriy,x2triy,z2triy,ytriy,itriy){ \
GEN_MESH_VERTEX(xtriy,ytriy,ztriy,0,0,(3*itriy))           \
GEN_MESH_VERTEX(x2triy,ytriy,ztriy,0,0,(1 + (3*itriy)))            \
GEN_MESH_VERTEX(x2triy,ytriy,z2triy,1,1,(2 + (3*itriy)))                        \
}





//2 triangles
#define ZPLANE(x_,y_,x2_,y2_,z_,i_){ \
                                        \
GEN_MESH_VERTEX(x_,y_,z_,0,0,(6*i_))                                         \
GEN_MESH_VERTEX(x2_,y2_,z_,1,1,(6*i_+1))         \
GEN_MESH_VERTEX(x2_,y_,z_,1,0,(6*i_+2))                         \
\
GEN_MESH_VERTEX(x_,y_,z_,0,0,(6*i_+3))                                         \
GEN_MESH_VERTEX(x_,y2_,z_,0,1,(6*i_+4))                         \
GEN_MESH_VERTEX(x2_,y2_,z_,1,1,(6*i_+5))         \
}


//2 triangles
#define ZCPLANE(x_,y_,x2_,y2_,z_,i_){ \
                                        \
GEN_MESH_VERTEX(x_,y_,z_,0,0,(6*i_))  \
GEN_MESH_VERTEX(x2_,y_,z_,1,0,(6*i_+1))                         \
GEN_MESH_VERTEX(x2_,y2_,z_,1,1,(6*i_+2))         \
\
GEN_MESH_VERTEX(x_,y_,z_,0,0,(6*i_+3))\
GEN_MESH_VERTEX(x2_,y2_,z_,1,1,(6*i_+4))         \
GEN_MESH_VERTEX(x_,y2_,z_,0,1,(6*i_+5))                         \
}



// XPLANE - 2 triangles
#define XPLANE(y_, z_, y2_, z2_, x_, i_) { \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_))                             \
    GEN_MESH_VERTEX(x_, y2_, z_, 0, 1, (6 * i_ + 1))                         \
    GEN_MESH_VERTEX(x_, y2_, z2_, 1, 1, (6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX(x_, y2_, z2_, 1, 1, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX(x_, y_, z2_, 1, 0, (6 * i_ + 5))                         \
}

// XCPLANE - 2 triangles
#define XCPLANE(y_, z_, y2_, z2_, x_, i_) { \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_))                             \
    GEN_MESH_VERTEX(x_, y2_, z2_, 1, 1, (6 * i_ + 1))                       \
    GEN_MESH_VERTEX(x_, y2_, z_, 1, 0, (6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX(x_, y_, z2_, 0, 1, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX(x_, y2_, z2_, 1, 1, (6 * i_ + 5))                       \
}

// YPLANE - 2 triangles
#define YPLANE(x_, z_, x2_, z2_, y_, i_) { \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_))                             \
    GEN_MESH_VERTEX(x2_, y_, z_, 1, 0, (6 * i_ + 1))                        \
    GEN_MESH_VERTEX(x2_, y_, z2_, 1, 1, (6 * i_ + 2))                       \
    \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX(x2_, y_, z2_, 1, 1, (6 * i_ + 4))                       \
    GEN_MESH_VERTEX(x_, y_, z2_, 0, 1, (6 * i_ + 5))                        \
}

// YCPLANE - 2 triangles
#define YCPLANE(x_, z_, x2_, z2_, y_, i_) { \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_))                             \
    GEN_MESH_VERTEX(x2_, y_, z2_, 1, 1, (6 * i_ + 1))                       \
    GEN_MESH_VERTEX(x2_, y_, z_, 1, 0, (6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX(x_, y_, z_, 0, 0, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX(x_, y_, z2_, 0, 1, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX(x2_, y_, z2_, 1, 1, (6 * i_ + 5))                       \
}


#define TXPLANE(y_,z_,y2_,z2_,tx1,ty1,tx2,ty2,x_,i_){ \
    GEN_MESH_VERTEX(x_, y_, z_, tx1, ty1, (6 * i_))                             \
    GEN_MESH_VERTEX(x_, y2_, z_, tx1, ty2, (6 * i_ + 1))                         \
    GEN_MESH_VERTEX(x_, y2_, z2_, tx2, ty2, (6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX(x_, y_, z_, tx1, ty1, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX(x_, y2_, z2_, tx2, ty2, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX(x_, y_, z2_, tx2, ty1, (6 * i_ + 5))                         \
}

#define TXCPLANE(y_,z_,y2_,z2_,tx1,ty1,tx2,ty2,x_,i_){ \
    GEN_MESH_VERTEX(x_, y_, z_, tx1, ty1, (6 * i_)) \
    GEN_MESH_VERTEX(x_, y2_, z2_, tx2, ty2, (6 * i_ + 1))                        \
    GEN_MESH_VERTEX(x_, y2_, z_, tx1, ty2, (6 * i_ + 2))                         \
    \
    GEN_MESH_VERTEX(x_, y_, z_, tx1, ty1, (6 * i_ + 3))                          \
    GEN_MESH_VERTEX(x_, y_, z2_, tx2, ty1, (6 * i_ + 4))                         \
    GEN_MESH_VERTEX(x_, y2_, z2_, tx2, ty2, (6 * i_ + 5))                        \
}

#define PLANE(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,i){ \
GEN_MESH_VERTEX(x1,y1,z1,0,0,(6*i + 0))            \
GEN_MESH_VERTEX(x2,y2,z2,1,1,(6*i + 1))         \
GEN_MESH_VERTEX(x3,y3,z3,1,1,(6*i + 2))         \
                                                    \
GEN_MESH_VERTEX(x1,y1,z1,0,0,(6*i + 3))         \
GEN_MESH_VERTEX(x4,y4,z4,1,1,(6*i + 4))\
GEN_MESH_VERTEX(x2,y2,z2,1,1,(6*i + 5))         \
\
}


Mesh GenMeshCustom(){

    Mesh customMesh = {0 };

    int precision,slices;
    precision = 32;//how many faces per slice
    slices = 1;// how many slices
    int index = 0;

    customMesh.triangleCount = (precision * 2 * slices)*2 + 4*precision + 16;
    customMesh.vertexCount = customMesh.triangleCount * 3;
    printf("VC: %d\n", customMesh.vertexCount);

    customMesh.vertices = (float *)MemAlloc(customMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)

    customMesh.texcoords = (float *)MemAlloc(customMesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)

    double r,l,t,a,w;
    r = 2; //radius
    l = 5; //length
    t = 1; //thickness
    w = l/slices; //slice width
    a = 2*M_PI/precision;//arc

    for(int s = 0;s<slices;s++){

        for(int i = 0;i<precision;i++) {
            GEN_MESH_VERTEX((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, 0, index)
            GEN_MESH_VERTEX((w*(s+1)), (r * sin(i * a)), (r * cos(i * a)), 0, 0, (index+1))
            GEN_MESH_VERTEX((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 0, 0, (index+2))

            GEN_MESH_VERTEX((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, 0, (index+3))
            GEN_MESH_VERTEX((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 0, 0, (index+4))
            GEN_MESH_VERTEX((s*w), (r * sin((i+1) * a)), (r * cos((i+1) * a)), 0, 0, (index+5))
            index+=6;

        }
    }

    for(int s = 0;s<slices;s++){

        for(int i = 0;i<precision;i++) {
            GEN_MESH_VERTEX((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, index)
            GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 0, 0, (index+1))
            GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, (index+2))

            GEN_MESH_VERTEX((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, (index+3))
            GEN_MESH_VERTEX((s*w), ((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)), 0, 0, (index+4))
            GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 0, 0, (index+5))
            index+=6;
        }
    }

    for(int i = 0;i<precision;i++){
        GEN_MESH_VERTEX(0,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,index)
        GEN_MESH_VERTEX(0,((r) * sin(i * a)), ((r) * cos(i * a)),0,0,(index+1))
        GEN_MESH_VERTEX(0,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),0,0,(index+2))

        GEN_MESH_VERTEX(0,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,(index+3))
        GEN_MESH_VERTEX(0,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),0,0,(index+4))
        GEN_MESH_VERTEX(0,((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)),0,0,(index+5))
        index+=6;
    }

    for(int i = 0;i<precision;i++){
        GEN_MESH_VERTEX(l,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,index)
        GEN_MESH_VERTEX(l,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),0,0,(index+1))
        GEN_MESH_VERTEX(l,((r) * sin(i * a)), ((r) * cos(i * a)),0,0,(index+2))

        GEN_MESH_VERTEX(l,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,(index+3))
        GEN_MESH_VERTEX(l,((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)),0,0,(index+4))
        GEN_MESH_VERTEX(l,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),0,0,(index+5))
        index+=6;
    }



    /*
    for(int s = 0;s<slices;s++){

        for(int i = 0;i<precision;i++) {
            GEN_MESH_VERTEX((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, 0, ((s*precision*6)+6*i))
            GEN_MESH_VERTEX((w*(s+1)), (r * sin(i * a)), (r * cos(i * a)), 0, 0, ((s*precision*6)+6*i+1))
            GEN_MESH_VERTEX((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 0, 0, ((s*precision*6)+6*i+2))

            GEN_MESH_VERTEX((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, 0, ((s*precision*6)+6*i+3))
            GEN_MESH_VERTEX((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 0, 0, ((s*precision*6)+6*i+4))
            GEN_MESH_VERTEX((s*w), (r * sin((i+1) * a)), (r * cos((i+1) * a)), 0, 0, ((s*precision*6)+6*i+5))

        }
    }

    for(int s = 0;s<slices;s++){

        for(int i = 0;i<precision;i++) {
            GEN_MESH_VERTEX((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, (offset+(s*precision*6)+6*i))
            GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, (offset+(s*precision*6)+6*i+1))
            GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 0, 0, (offset+(s*precision*6)+6*i+2))

            GEN_MESH_VERTEX((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, (offset+(s*precision*6)+6*i+3+offset))
            GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 0, 0, (offset+(s*precision*6)+6*i+4))
            GEN_MESH_VERTEX((s*w), ((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)), 0, 0, (offset+(s*precision*6)+6*i+5))

        }
    }
     */
    UploadMesh(&customMesh, false);
    return customMesh;
}

Mesh GenMeshRoundTube(Object *obj){
    Mesh customMesh = {0 };

    int precision,slices;
    precision = 32;//how many faces per slice
    slices = 1;// how many slices
    int index = 0;

    customMesh.triangleCount = (precision * 2 * slices)*2 + 4*precision + 16;
    customMesh.vertexCount = customMesh.triangleCount * 3;

    customMesh.vertices = (float *)MemAlloc(customMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)

    customMesh.texcoords = (float *)MemAlloc(customMesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)

    double r,l,t,a,w;
    a = 2*M_PI/precision;//arc

    switch (obj->data.facing){
        case 'x':{

            r = obj->data.yHeight; //radius
            l = obj->data.xLength; //length
            t = obj->data.thickness; //thickness
            w = l/slices; //slice width

            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, i/precision, index)
                    GEN_MESH_VERTEX((w*(s+1)), (r * sin(i * a)), (r * cos(i * a)), 1, i/precision, (index+1))
                    GEN_MESH_VERTEX((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 1, (i+1)/precision, (index+2))

                    GEN_MESH_VERTEX((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, i/precision, (index+3))
                    GEN_MESH_VERTEX((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 1, (i+1)/precision, (index+4))
                    GEN_MESH_VERTEX((s*w), (r * sin((i+1) * a)), (r * cos((i+1) * a)), 0, (i+1)/precision, (index+5))
                    index+=6;

                }
            }

            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, index)
                    GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 1, (i+1)/precision, (index+1))
                    GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 1, 0, (index+2))

                    GEN_MESH_VERTEX((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, 0, (index+3))
                    GEN_MESH_VERTEX((s*w), ((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)), 0, (i+1)/precision, (index+4))
                    GEN_MESH_VERTEX((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 1, (i+1)/precision, (index+5))
                    index+=6;
                }
            }

            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX(0,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,index)
                GEN_MESH_VERTEX(0,((r) * sin(i * a)), ((r) * cos(i * a)),0,1,(index+1))
                GEN_MESH_VERTEX(0,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),(i+1)/precision,1,(index+2))

                GEN_MESH_VERTEX(0,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,(index+3))
                GEN_MESH_VERTEX(0,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),(i+1)/precision,1,(index+4))
                GEN_MESH_VERTEX(0,((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)),(i+1)/precision,0,(index+5))
                index+=6;
            }

            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX(l,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,index)
                GEN_MESH_VERTEX(l,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),(i+1)/precision,1,(index+1))
                GEN_MESH_VERTEX(l,((r) * sin(i * a)), ((r) * cos(i * a)),0,1,(index+2))

                GEN_MESH_VERTEX(l,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),0,0,(index+3))
                GEN_MESH_VERTEX(l,((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)),(i+1)/precision,0,(index+4))
                GEN_MESH_VERTEX(l,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),(i+1)/precision,1,(index+5))
                index+=6;
            }


        }
        break;
        case 'y':{

        }
        break;
        case 'z':{

        }
        break;
    }

    UploadMesh(&customMesh, false);
    return customMesh;
}

Mesh GenMeshRectTube(Object *obj){

    Mesh customMesh = {0 };
    customMesh.triangleCount = 32;
    customMesh.vertexCount = customMesh.triangleCount * 3;
    customMesh.vertices = (float *)MemAlloc(customMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    customMesh.texcoords = (float *)MemAlloc(customMesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)

    double l,h,d,t;
    l = obj->data.xLength;
    h = obj->data.yHeight;
    d = obj->data.zDepth;
    t = obj->data.thickness;

    switch(obj->data.facing){
        case 'x':{
            //Z-facing side parallel to x-axis
            ZPLANE(0,0,l,h,0,0)
            //opposite face
            ZCPLANE(0,0,l,h,d,1)
            //Top face
            YCPLANE(0,0,l,d,h,2)
            //bottom face
            YPLANE(0,0,l,d,0,3)
            //lefts side faces
            //left far face
            TXCPLANE(0,0,h,t,0,0,(t/d),1,0,4)
            //left close face
            TXPLANE(0,d,h,d-t,1,0,((d-t)/d),1,0,5)
            //left top face
            TXCPLANE(h-t,t,h,d-t,(t/d),((h-t)/h),((d-t)/d),1,0,6)
            //left bot face
            TXCPLANE(0,t,t,d-t,t/d,0,((d-t)/d),(t/h),0,7)
            //right faces
            //right far face
            TXPLANE(0,0,h,t,0,0,(t/d),1,l,8)
            //right close face
            TXCPLANE(0,d,h,d-t,1,0,((d-t)/d),1,l,9)
            //right top
            TXPLANE(h-t,t,h,d-t,(t/d),((h-t)/h),((d-t)/d),1,l,10)
            //right bot
            TXPLANE(0,t,t,d-t,t/d,0,((d-t)/d),(t/h),l,11)
            //inner faces
            //far side face
            ZCPLANE(0,t,l,h-t,t,12)
            //opposite/close side face
            ZPLANE(0,t,l,h-t,d-t,13)
            //bottom inner face
            YCPLANE(0,t,l,d-t,t,14)
            //top inner face
            YPLANE(0,t,l,d-t,h - t,15)
             }
        break;
        case 'z':{

        }
        break;
        case 'y':{

        }
        break;



    }



    // Upload customMesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&customMesh, false);
    return customMesh;

}

