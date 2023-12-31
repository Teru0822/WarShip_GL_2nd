#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

float Misilevertex[ARRAY_MAX];
int Misilelines[ARRAY_MAX];
int MisilevertexDataSize = 0, MisilelineDataSize = 0;

void makeMisile()
{
    glPointSize(3);

    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < MisilelineDataSize; i++) {
            glArrayElement(Misilelines[i * 3]);   //0
            glArrayElement(Misilelines[i * 3 + 1]);  //1
            glArrayElement(Misilelines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
