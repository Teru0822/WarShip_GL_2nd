#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float RightLeftMissilevertex[ARRAY_MAX];
int RightLeftMissilelines[ARRAY_MAX];
int RightLeftMissilevertexDataSize = 0, RightLeftMissilelineDataSize = 0;

void makeRightLeftMissile(float r,float g,float b)
{
    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < RightLeftMissilelineDataSize; i++) {
            glArrayElement(RightLeftMissilelines[i * 3]);   //0
            glArrayElement(RightLeftMissilelines[i * 3 + 1]);  //1
            glArrayElement(RightLeftMissilelines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
