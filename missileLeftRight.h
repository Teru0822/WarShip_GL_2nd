#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float LeftRightMissilevertex[ARRAY_MAX];
int LeftRightMissilelines[ARRAY_MAX];
int LeftRightMissilevertexDataSize = 0, LeftRightMissilelineDataSize = 0;

void makeLeftRightMissile(float r,float g,float b)
{
    glPointSize(3);
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < LeftRightMissilelineDataSize; i++) {
            glArrayElement(LeftRightMissilelines[i * 3]);   //0
            glArrayElement(LeftRightMissilelines[i * 3 + 1]);  //1
            glArrayElement(LeftRightMissilelines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
