#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

float Rvertex[ARRAY_MAX];
int Rlines[ARRAY_MAX];
int RvertexDataSize = 0, RlineDataSize = 0;


void makeRet()
{
    glPointSize(3);
    glColor3f(0, 1, 1);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < RlineDataSize; i++) {
            glArrayElement(Rlines[i * 3]);   //0
            glArrayElement(Rlines[i * 3 + 1]);  //1
            glArrayElement(Rlines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
