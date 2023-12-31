#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float RightRightMissilevertex[ARRAY_MAX];
int RightRightMissilelines[ARRAY_MAX];
int RightRightMissilevertexDataSize = 0, RightRightMissilelineDataSize = 0;

void makeRightRightMissile(float r,float g,float b)
{
    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < RightRightMissilelineDataSize; i++) {
            glArrayElement(RightRightMissilelines[i * 3]);   //0
            glArrayElement(RightRightMissilelines[i * 3 + 1]);  //1
            glArrayElement(RightRightMissilelines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
