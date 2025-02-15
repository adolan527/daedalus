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
customMesh.texcoords[2*_i+1] = _tc2;             \
}

#define GEN_MESH_VERTEX_N(_x,_y,_z,_tc1,_tc2,nx,ny,nz,_i) { \
             \
customMesh.vertices[3*_i] = _x;                           \
customMesh.vertices[3*_i + 1] = _y;   \
customMesh.vertices[3*_i + 2] = _z;   \
\
customMesh.texcoords[2*_i] = _tc1;  \
customMesh.texcoords[2*_i+1] = _tc2;               \
\
customMesh.normals[3*_i] = nx;                      \
customMesh.normals[3*_i + 1] = ny;                  \
customMesh.normals[3*_i + 2] = nz;    \
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
GEN_MESH_VERTEX_N(x_,y_,z_,0,0,0,0,1,(6*i_))                                         \
GEN_MESH_VERTEX_N(x2_,y2_,z_,1,1,0,0,1,(6*i_+1))         \
GEN_MESH_VERTEX_N(x2_,y_,z_,1,0,0,0,1,(6*i_+2))                         \
\
GEN_MESH_VERTEX_N(x_,y_,z_,0,0,0,0,1,(6*i_+3))                                         \
GEN_MESH_VERTEX_N(x_,y2_,z_,0,1,0,0,1,(6*i_+4))                         \
GEN_MESH_VERTEX_N(x2_,y2_,z_,1,1,0,0,1,(6*i_+5))         \
}

#define TZPLANE(x_,y_,x2_,y2_,tx1,ty1,tx2,ty2,z_,i_){ \
                                        \
GEN_MESH_VERTEX_N(x_,y_,z_,tx1,ty1,0,0,1,(6*i_))                                         \
GEN_MESH_VERTEX_N(x2_,y2_,z_,tx2,ty2,0,0,1,(6*i_+1))         \
GEN_MESH_VERTEX_N(x2_,y_,z_,tx2,ty1,0,0,1,(6*i_+2))                         \
\
GEN_MESH_VERTEX_N(x_,y_,z_,tx1,ty1,0,0,1,(6*i_+3))                                         \
GEN_MESH_VERTEX_N(x_,y2_,z_,tx1,ty2,0,0,1,(6*i_+4))                         \
GEN_MESH_VERTEX_N(x2_,y2_,z_,tx2,ty2,0,0,1,(6*i_+5))         \
}


//2 triangles
#define ZCPLANE(x_,y_,x2_,y2_,z_,i_){ \
                                        \
GEN_MESH_VERTEX_N(x_,y_,z_,0,0,0,0,1,(6*i_))  \
GEN_MESH_VERTEX_N(x2_,y_,z_,1,0,0,0,1,(6*i_+1))                         \
GEN_MESH_VERTEX_N(x2_,y2_,z_,1,1,0,0,1,(6*i_+2))         \
\
GEN_MESH_VERTEX_N(x_,y_,z_,0,0,0,0,1,(6*i_+3))\
GEN_MESH_VERTEX_N(x2_,y2_,z_,1,1,0,0,1,(6*i_+4))         \
GEN_MESH_VERTEX_N(x_,y2_,z_,0,1,0,0,1,(6*i_+5))                         \
}

#define TZCPLANE(x_,y_,x2_,y2_,tx1,ty1,tx2,ty2,z_,i_){ \
                                        \
GEN_MESH_VERTEX_N(x_,y_,z_,tx1,ty1,0,0,1,(6*i_))  \
GEN_MESH_VERTEX_N(x2_,y_,z_,tx2,ty1,0,0,1,(6*i_+1))                         \
GEN_MESH_VERTEX_N(x2_,y2_,z_,tx2,ty2,0,0,1,(6*i_+2))         \
\
GEN_MESH_VERTEX_N(x_,y_,z_,tx1,ty1,0,0,1,(6*i_+3)) \
GEN_MESH_VERTEX_N(x2_,y2_,z_,tx2,ty2,0,0,1,(6*i_+4))         \
GEN_MESH_VERTEX_N(x_,y2_,z_,tx1,ty2,0,0,1,(6*i_+5))                         \
}




// XPLANE - 2 triangles
#define XPLANE(y_, z_, y2_, z2_, x_, i_) { \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0,1,0,0, (6 * i_))                             \
    GEN_MESH_VERTEX_N(x_, y2_, z_, 0, 1, 1,0,0,(6 * i_ + 1))                         \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, 1, 1, 1,0,0,(6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0, 1,0,0,(6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, 1, 1,1,0,0, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX_N(x_, y_, z2_, 1, 0, 1,0,0,(6 * i_ + 5))                         \
}

// XCPLANE - 2 triangles
#define XCPLANE(y_, z_, y2_, z2_, x_, i_) { \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0,1,0,0, (6 * i_))                             \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, 1, 1,1,0,0, (6 * i_ + 1))                       \
    GEN_MESH_VERTEX_N(x_, y2_, z_, 1, 0, 1,0,0,(6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0, 1,0,0,(6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x_, y_, z2_, 0, 1, 1,0,0,(6 * i_ + 4))                        \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, 1, 1, 1,0,0,(6 * i_ + 5))                       \
}

// YPLANE - 2 triangles
#define YPLANE(x_, z_, x2_, z2_, y_, i_) { \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0,  0,1,0,(6 * i_))                             \
    GEN_MESH_VERTEX_N(x2_, y_, z_, 1, 0,  0,1,0,(6 * i_ + 1))                        \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, 1, 1,  0,1,0,(6 * i_ + 2))                       \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0,  0,1,0,(6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, 1, 1, 0,1,0, (6 * i_ + 4))                       \
    GEN_MESH_VERTEX_N(x_, y_, z2_, 0, 1,  0,1,0,(6 * i_ + 5))                        \
}

// YCPLANE - 2 triangles
#define YCPLANE(x_, z_, x2_, z2_, y_, i_) { \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0,  0,1,0,(6 * i_))                             \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, 1, 1, 0,1,0, (6 * i_ + 1))                       \
    GEN_MESH_VERTEX_N(x2_, y_, z_, 1, 0, 0,1,0, (6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, 0, 0,  0,1,0,(6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x_, y_, z2_, 0, 1,  0,1,0,(6 * i_ + 4))                        \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, 1, 1,  0,1,0,(6 * i_ + 5))                       \
}

// YPLANE - 2 triangles
#define TYPLANE(x_, z_, x2_, z2_,tx1,ty1,tx2,ty2, y_, i_) { \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1,  0,1,0,(6 * i_))                             \
    GEN_MESH_VERTEX_N(x2_, y_, z_, tx2, ty1, 0,1,0, (6 * i_ + 1))                        \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, tx2, ty2, 0,1,0, (6 * i_ + 2))                       \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1, 0,1,0, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, tx2, ty2,  0,1,0,(6 * i_ + 4))                       \
    GEN_MESH_VERTEX_N(x_, y_, z2_, tx1, ty2,  0,1,0,(6 * i_ + 5))                        \
}

// YCPLANE - 2 triangles
#define TYCPLANE(x_, z_, x2_, z2_,tx1,ty1,tx2,ty2, y_, i_) { \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1, 0,1,0, (6 * i_))                             \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, tx2, ty2, 0,1,0, (6 * i_ + 1))                       \
    GEN_MESH_VERTEX_N(x2_, y_, z_, tx2, ty1,  0,1,0,(6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1, 0,1,0, (6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x_, y_, z2_, tx1, ty2, 0,1,0, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX_N(x2_, y_, z2_, tx2, ty2, 0,1,0,(6 * i_ + 5))                       \
}

#define TXPLANE(y_,z_,y2_,z2_,tx1,ty1,tx2,ty2,x_,i_){ \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1,1,0,0, (6 * i_))                             \
    GEN_MESH_VERTEX_N(x_, y2_, z_, tx1, ty2,1,0,0, (6 * i_ + 1))                         \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, tx2, ty2,1,0,0, (6 * i_ + 2))                        \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1, 1,0,0,(6 * i_ + 3))                         \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, tx2, ty2,1,0,0, (6 * i_ + 4))                        \
    GEN_MESH_VERTEX_N(x_, y_, z2_, tx2, ty1, 1,0,0,(6 * i_ + 5))                         \
}

#define TXCPLANE(y_,z_,y2_,z2_,tx1,ty1,tx2,ty2,x_,i_){ \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1,1,0,0, (6 * i_)) \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, tx2, ty2, 1,0,0,(6 * i_ + 1))                        \
    GEN_MESH_VERTEX_N(x_, y2_, z_, tx1, ty2, 1,0,0,(6 * i_ + 2))                         \
    \
    GEN_MESH_VERTEX_N(x_, y_, z_, tx1, ty1, 1,0,0,(6 * i_ + 3))                          \
    GEN_MESH_VERTEX_N(x_, y_, z2_, tx2, ty1,1,0,0, (6 * i_ + 4))                         \
    GEN_MESH_VERTEX_N(x_, y2_, z2_, tx2, ty2,1,0,0, (6 * i_ + 5))                        \
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

    return (Mesh){0};
}

static int counter =0;



Mesh GenMeshRoundTube(Object *obj){
    Mesh customMesh = {0 };

    int precision,slices;
    precision = 32;//how many faces per slice

    /* One slice looks better,regardless of size
    if(obj->data.facing == 'x'){
        slices = (int)obj->data.xLength;// how many slices
    }else if(obj->data.facing == 'y'){
        slices = (int)obj->data.yHeight;// how many slices
    }
    else{
        slices = (int)obj->data.zDepth;// how many slices
    }*/
    slices = 1; //If the texture is very small (compared to model size), it may stretch poorly.


    int index = 0;

    customMesh.triangleCount = (precision * 2 * slices)*2 + 4*precision + 16;
    customMesh.vertexCount = customMesh.triangleCount * 3;

    customMesh.vertices = (float *)MemAlloc(customMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)

    customMesh.texcoords = (float *)MemAlloc(customMesh.vertexCount * 2 * sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    customMesh.normals = (float *)MemAlloc(customMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    double r,l,t,a,w;
    a = 2*M_PI/precision;//arc

    switch (obj->data.facing){
        case 'x':{

            r = obj->data.yHeight; //radius
            l = obj->data.xLength; //length
            t = obj->data.thickness; //thickness
            w = l/slices; //slice width
            //outside
            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX_N((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, ((float)i/precision), 0,sin(i*a),cos(i*a),index)
                    GEN_MESH_VERTEX_N((w*(s+1)), (r * sin(i * a)), (r * cos(i * a)), 1, ((float)i/precision),  0,sin(i*a),cos(i*a),(index+1))
                    GEN_MESH_VERTEX_N((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 1, ((float)(i+1)/precision),  0,sin((i + 1) * a),cos((i + 1) * a),(index+2))

                    GEN_MESH_VERTEX_N((s*w), (r * sin(i * a)), (r * cos(i * a)), 0, ((float)i/precision), 0,sin(i*a),cos(i*a), (index+3))
                    GEN_MESH_VERTEX_N((w*(s+1)), (r * sin((i + 1) * a)), (r * cos((i+1) * a)), 1, ((float)(i+1)/precision), 0,sin((i + 1) * a),cos((i + 1) * a), (index+4))
                    GEN_MESH_VERTEX_N((s*w), (r * sin((i+1) * a)), (r * cos((i+1) * a)), 0, ((float)(i+1)/precision), 0,sin((i + 1) * a),cos((i + 1) * a), (index+5))
                    index+=6;

                }
            }
            //inside
            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX_N((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, ((float)(i)/precision), 0,sin(i*a),cos(i*a), index)
                    GEN_MESH_VERTEX_N((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 1, ((float)(i+1)/precision),  0,sin((i+1)*a),cos((i+1)*a),(index+1))
                    GEN_MESH_VERTEX_N((w*(s+1)), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 1, ((float)(i)/precision), 0,sin(i * a),cos(i  * a), (index+2))

                    GEN_MESH_VERTEX_N((s*w), ((r-t) * sin(i * a)), ((r-t) * cos(i * a)), 0, ((float)(i)/precision),  0,sin(i*a),cos(i*a),(index+3))
                    GEN_MESH_VERTEX_N((s*w), ((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)), 0, ((float)(i+1)/precision), 0,sin((i + 1) * a),cos((i + 1) * a), (index+4))
                    GEN_MESH_VERTEX_N((w*(s+1)), ((r-t) * sin((i + 1) * a)), ((r-t) * cos((i+1) * a)), 1, ((float)(i+1)/precision), 0,sin((i + 1) * a),cos((i + 1) * a), (index+5))
                    index+=6;
                }
            }
            //front face
            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX_N(0,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),((float)(i)/precision),0,1,0,0,index)
                GEN_MESH_VERTEX_N(0,((r) * sin(i * a)), ((r) * cos(i * a)),((float)(i)/precision),(t/r),1,0,0,(index+1))
                GEN_MESH_VERTEX_N(0,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),1,0,0,(index+2))

                GEN_MESH_VERTEX_N(0,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),((float)(i)/precision),0,1,0,0,(index+3))
                GEN_MESH_VERTEX_N(0,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),1,0,0,(index+4))
                GEN_MESH_VERTEX_N(0,((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)),((float)(i+1)/precision),0,1,0,0,(index+5))
                index+=6;
            }
            //back face
            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX_N(l,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),((float)(i)/precision),0,1,0,0,index)
                GEN_MESH_VERTEX_N(l,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),1,0,0,(index+1))
                GEN_MESH_VERTEX_N(l,((r) * sin(i * a)), ((r) * cos(i * a)),((float)(i)/precision),(t/r),1,0,0,(index+2))
                                 
                GEN_MESH_VERTEX_N(l,((r-t) * sin(i * a)), ((r-t) * cos(i * a)),((float)(i)/precision),0,1,0,0,(index+3))
                GEN_MESH_VERTEX_N(l,((r-t) * sin((i+1) * a)), ((r-t) * cos((i+1) * a)),((float)(i+1)/precision),0,1,0,0,(index+4))
                GEN_MESH_VERTEX_N(l,((r) * sin((i+1) * a)), ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),1,0,0,(index+5))
                index+=6;
            }


        }
        break;
        case 'y':{

            r = obj->data.xLength; //radius
            l = obj->data.yHeight; //length
            t = obj->data.thickness; //thickness
            w = l/slices; //slice width
            //outside
            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX_N((r * sin(i * a)),(s*w),  (r * cos(i * a)), 0, ((float)i/precision),sin(i*a),0,cos(i*a), index)
                    GEN_MESH_VERTEX_N((r * sin((i + 1) * a)),(w*(s+1)),  (r * cos((i+1) * a)), 1, ((float)(i+1)/precision),sin((i+1)*a),0,cos((i+1)*a), (index+1))
                    GEN_MESH_VERTEX_N((r * sin(i * a)),(w*(s+1)),  (r * cos(i * a)), 1, ((float)i/precision),sin((i)*a),0,cos((i)*a), (index+2))

                    GEN_MESH_VERTEX_N((r * sin(i * a)),(s*w),  (r * cos(i * a)), 0, ((float)i/precision),sin((i)*a),0,cos((i)*a), (index+3))
                    GEN_MESH_VERTEX_N((r * sin((i+1) * a)),(s*w),  (r * cos((i+1) * a)), 0, ((float)(i+1)/precision), sin((i+1)*a),0,cos((i+1)*a),(index+4))
                    GEN_MESH_VERTEX_N((r * sin((i + 1) * a)),(w*(s+1)),  (r * cos((i+1) * a)), 1, ((float)(i+1)/precision),sin((i+1)*a),0,cos((i+1)*a), (index+5))
                    index+=6;

                }
            }
            //inside
            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),(s*w),  ((r-t) * cos(i * a)), 0, ((float)(i)/precision),sin((i)*a),0,cos((i)*a), index)
                    GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),(w*(s+1)),  ((r-t) * cos(i * a)), 1, ((float)(i)/precision),sin((i)*a),0,cos((i)*a), (index+1))
                    GEN_MESH_VERTEX_N(((r-t) * sin((i + 1) * a)),(w*(s+1)),  ((r-t) * cos((i+1) * a)), 1, ((float)(i+1)/precision),sin((i+1)*a),0,cos((i+1)*a), (index+2))

                    GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),(s*w),  ((r-t) * cos(i * a)), 0, ((float)(i)/precision),sin((i)*a),0,cos((i)*a), (index+3))
                    GEN_MESH_VERTEX_N(((r-t) * sin((i + 1) * a)),(w*(s+1)),  ((r-t) * cos((i+1) * a)), 1, ((float)(i+1)/precision),sin((i+1)*a),0,cos((i+1)*a), (index+4))
                    GEN_MESH_VERTEX_N(((r-t) * sin((i+1) * a)),(s*w),  ((r-t) * cos((i+1) * a)), 0, ((float)(i+1)/precision),sin((i+1)*a),0,cos((i+1)*a), (index+5))
                    index+=6;
                }
            }
            //front face
            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),0, ((r-t) * cos(i * a)),((float)(i)/precision),0,0,1,0,index)
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),0, ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),0,1,0,(index+1))
                GEN_MESH_VERTEX_N(((r) * sin(i * a)),0, ((r) * cos(i * a)),((float)(i)/precision),(t/r),0,1,0,(index+2))

                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),0, ((r-t) * cos(i * a)),((float)(i)/precision),0,0,1,0,(index+3))
                GEN_MESH_VERTEX_N(((r-t) * sin((i+1) * a)),0, ((r-t) * cos((i+1) * a)),((float)(i+1)/precision),0,0,1,0,(index+4))
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),0, ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),0,1,0,(index+5))
                index+=6;
            }
            //back face
            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),l, ((r-t) * cos(i * a)),((float)(i)/precision),0,0,1,0,index)
                GEN_MESH_VERTEX_N(((r) * sin(i * a)),l, ((r) * cos(i * a)),((float)(i)/precision),(t/r),0,1,0,(index+1))
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),l, ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),0,1,0,(index+2))

                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),l, ((r-t) * cos(i * a)),((float)(i)/precision),0,0,1,0,(index+3))
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),l, ((r) * cos((i+1) * a)),((float)(i+1)/precision),(t/r),0,1,0,(index+4))
                GEN_MESH_VERTEX_N(((r-t) * sin((i+1) * a)),l, ((r-t) * cos((i+1) * a)),((float)(i+1)/precision),0,0,1,0,(index+5))
                index+=6;
            }

        }
        break;
        case 'z':{

            r = obj->data.xLength; //radius
            l = obj->data.zDepth; //length
            t = obj->data.thickness; //thickness
            w = l/slices; //slice width
            //outside
            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX_N((r * sin(i * a)), (r * cos(i * a)),(s*w),  0, ((float)i/precision), sin(i*a),cos(i*a),0,index)
                    GEN_MESH_VERTEX_N((r * sin(i * a)),(r * cos(i * a)),(w*(s+1)),   1, ((float)i/precision),sin(i*a),cos(i*a),0, (index+1))
                    GEN_MESH_VERTEX_N((r * sin((i + 1) * a)),(r * cos((i+1) * a)),(w*(s+1)),   1, ((float)(i+1)/precision), sin((i+1)*a),cos((i+1)*a),0,(index+2))

                    GEN_MESH_VERTEX_N((r * sin(i * a)),(r * cos(i * a)),(s*w),   0, ((float)i/precision),  sin(i*a),cos(i*a),0,(index+3))
                    GEN_MESH_VERTEX_N((r * sin((i + 1) * a)), (r * cos((i+1) * a)),(w*(s+1)),  1, ((float)(i+1)/precision),sin((i+1)*a),cos((i+1)*a),0, (index+4))
                    GEN_MESH_VERTEX_N((r * sin((i+1) * a)), (r * cos((i+1) * a)),(s*w),  0, ((float)(i+1)/precision),sin((i+1)*a),cos((i+1)*a),0, (index+5))
                    index+=6;

                }
            }
            //inside
            for(int s = 0;s<slices;s++){

                for(int i = 0;i<precision;i++) {
                    GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),(s*w),   0, ((float)(i)/precision),  sin(i*a),cos(i*a),0,index)
                    GEN_MESH_VERTEX_N(((r-t) * sin((i + 1) * a)),((r-t) * cos((i+1) * a)),(w*(s+1)),   1, ((float)(i+1)/precision), sin((i+1)*a),cos((i+1)*a),0, (index+1))
                    GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),(w*(s+1)),   1, ((float)(i)/precision), sin(i*a),cos(i*a),0, (index+2))

                    GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),(s*w),   0, ((float)(i)/precision),sin(i*a),cos(i*a),0, (index+3))
                    GEN_MESH_VERTEX_N(((r-t) * sin((i+1) * a)),((r-t) * cos((i+1) * a)),(s*w),   0, ((float)(i+1)/precision),sin((i+1)*a),cos((i+1)*a),0,  (index+4))
                    GEN_MESH_VERTEX_N(((r-t) * sin((i + 1) * a)),((r-t) * cos((i+1) * a)),(w*(s+1)),   1, ((float)(i+1)/precision),sin((i+1)*a),cos((i+1)*a),0,  (index+5))
                    index+=6;
                }
            }
            //front face
            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),0, ((float)(i)/precision),0,0,0,1,index)
                GEN_MESH_VERTEX_N(((r) * sin(i * a)),((r) * cos(i * a)),0, ((float)(i)/precision),(t/r),0,0,1,(index+1))
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),((r) * cos((i+1) * a)),0, ((float)(i+1)/precision),(t/r),0,0,1,(index+2))

                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),0, ((float)(i)/precision),0,0,0,1,(index+3))
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),((r) * cos((i+1) * a)),0, ((float)(i+1)/precision),(t/r),0,0,1,(index+4))
                GEN_MESH_VERTEX_N(((r-t) * sin((i+1) * a)),((r-t) * cos((i+1) * a)),0, ((float)(i+1)/precision),0,0,0,1,(index+5))
                index+=6;
            }
            //back face
            for(int i = 0;i<precision;i++){
                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),l, ((float)(i)/precision),0,0,0,1,index)
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),((r) * cos((i+1) * a)),l, ((float)(i+1)/precision),(t/r),0,0,1,(index+1))
                GEN_MESH_VERTEX_N(((r) * sin(i * a)),((r) * cos(i * a)),l, ((float)(i)/precision),(t/r),0,0,1,(index+2))

                GEN_MESH_VERTEX_N(((r-t) * sin(i * a)),((r-t) * cos(i * a)),l, ((float)(i)/precision),0,0,0,1,(index+3))
                GEN_MESH_VERTEX_N(((r-t) * sin((i+1) * a)),((r-t) * cos((i+1) * a)),l, ((float)(i+1)/precision),0,0,0,1,(index+4))
                GEN_MESH_VERTEX_N(((r) * sin((i+1) * a)),((r) * cos((i+1) * a)),l, ((float)(i+1)/precision),(t/r),0,0,1,(index+5))
                index+=6;
            }

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
    customMesh.normals = (float *)MemAlloc(customMesh.vertexCount * 3 * sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)

    double l,h,d,t;

    t = obj->data.thickness;

    switch(obj->data.facing){
        case 'x':{
            l = obj->data.xLength;
            h = obj->data.yHeight;
            d = obj->data.zDepth;
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
        case 'y':{
            d = obj->data.xLength;
            l = obj->data.yHeight;
            h = obj->data.zDepth;
            //Z-facing side parallel to x-axis
            XCPLANE(0,0,l,h,0,0)
            //opposite face
            XPLANE(0,0,l,h,d,1)
            //Top face
            ZCPLANE(0,0,d,l,h,2)
            //bottom face
            ZPLANE(0,0,d,l,0,3)
            //lefts side faces
            //left far face
            TYPLANE(0,0,t,h,0,0,(t/d),1,0,4)
            //left close face
            TYCPLANE(d,0,(d-t),h,1,0,((d-t)/d),1,0,5)
            //left top face
            TYPLANE(t,h-t,d-t,h,(t/d),((h-t)/h),((d-t)/d),1,0,6)
            //left bot face
            TYPLANE(t,0,d-t,t,t/d,0,((d-t)/d),(t/h),0,7)
            //right faces
            //right far face
            TYCPLANE(0,0,t,h,0,0,(t/d),1,l,8)
            //right close face
            TYPLANE(d,0,d-t,h,1,0,((d-t)/d),1,l,9)
            //right top
            TYCPLANE(t,h-t,d-t,h,(t/d),((h-t)/h),((d-t)/d),1,l,10)
            //right bot
            TYCPLANE(t,0,d-t,t,t/d,0,((d-t)/d),(t/h),l,11)
            //inner faces
            //far side face
            XPLANE(0,t,l,h-t,t,12)
            //opposite/close side face
            XCPLANE(0,t,l,h-t,d-t,13)
            //bottom inner face
            ZCPLANE(t,0,d-t,l,t,14)
            //top inner face
            ZPLANE(t,0,d-t,l,h - t,15)
        }
            break;
        case 'z':{
            h = obj->data.xLength;
            d = obj->data.yHeight;
            l = obj->data.zDepth;
            //Z-facing side parallel to x-axis
            YPLANE(0,0,h,l,0,0)
            //opposite face
            YCPLANE(0,0,h,l,d,1)
            //Top face
            XPLANE(0,0,d,l,h,2)
            //bottom face
            XCPLANE(0,0,d,l,0,3)

            //lefts side faces
            //left far face
            TZPLANE(0,0,h,t,0,0,1,(t/d),0,4)
            //left close face
            TZCPLANE(0,d,h,d-t,0,1,1,((d-t)/d),0,5)
            //left top face
            TZPLANE(h-t,t,h,d-t,((h-t)/h),(t/d),1,((d-t)/d),0,6)
            //left bot face
            TZPLANE(0,t,t,d-t,0,t/d,(t/h),((d-t)/d),0,7)

            //right faces
            //right far face
            TZCPLANE(0,0,h,t,0,0,1,(t/d),l,8)
            //right close face
            TZPLANE(0,d,h,d-t,0,1,1,((d-t)/d),l,9)
            //right top
            TZCPLANE(h-t,t,h,d-t,((h-t)/h),(t/d),1,((d-t)/d),l,10)
            //right bot
            TZCPLANE(0,t,t,d-t,0,t/d,(t/h),((d-t)/d),l,11)

            //inner faces
            //far side face
            YCPLANE(t,0,h-t,l,t,12)
            //opposite/close side face
            YPLANE(t,0,h-t,l,d-t,13)
            //bottom inner face
            XPLANE(t,0,d-t,l,t,14)
            //top inner face
            XCPLANE(t,0,d-t,l,h - t,15)

        }
        break;




    }



    // Upload customMesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&customMesh, false);
    return customMesh;

}

