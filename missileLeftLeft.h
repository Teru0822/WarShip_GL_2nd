#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float LeftLeftMissilevertex[ARRAY_MAX];
int LeftLeftMissilelines[ARRAY_MAX];
int LeftLeftMissilevertexDataSize = 0, LeftLeftMissilelineDataSize = 0;

void makeLeftLeftMissile(float r,float g, float b)
{
    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < LeftLeftMissilelineDataSize; i++) {
            glArrayElement(LeftLeftMissilelines[i * 3]);   //0
            glArrayElement(LeftLeftMissilelines[i * 3 + 1]);  //1
            glArrayElement(LeftLeftMissilelines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
