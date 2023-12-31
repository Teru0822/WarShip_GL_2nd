#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float cockPitvertex[ARRAY_MAX];
int cockPitlines[ARRAY_MAX];
int cockPitvertexDataSize = 0, cockPitlineDataSize = 0;

void makeCockPit(float r,float g,float b)
{

    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < cockPitlineDataSize; i++) {
            glArrayElement(cockPitlines[i * 3]);   //0
            glArrayElement(cockPitlines[i * 3 + 1]);  //1
            glArrayElement(cockPitlines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}
