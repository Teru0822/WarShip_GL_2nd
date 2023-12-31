#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float Fire1vertex[ARRAY_MAX];
int Fire1lines[ARRAY_MAX];
int Fire1vertexDataSize = 0, Fire1lineDataSize = 0;

void fire1(float r,float g ,float b)
{
    glPointSize(3);

    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < Fire1lineDataSize; i++) {
            glArrayElement(Fire1lines[i * 3]);   //0
            glArrayElement(Fire1lines[i * 3 + 1]);  //1
            glArrayElement(Fire1lines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}
