#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float Fire2vertex[ARRAY_MAX];
int Fire2lines[ARRAY_MAX];
int Fire2vertexDataSize = 0, Fire2lineDataSize = 0;

void fire2(float r, float g, float b)
{
    glPointSize(3);

    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < Fire2lineDataSize; i++) {
            glArrayElement(Fire2lines[i * 3]);   //0
            glArrayElement(Fire2lines[i * 3 + 1]);  //1
            glArrayElement(Fire2lines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
