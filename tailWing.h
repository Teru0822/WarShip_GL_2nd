#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float tailWingvertex[ARRAY_MAX];
int tailWinglines[ARRAY_MAX];
int tailWingvertexDataSize = 0, tailWinglineDataSize = 0;

void makeTailWing(float r, float g,float b)
{

    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < tailWinglineDataSize; i++) {
            glArrayElement(tailWinglines[i * 3]);   //0
            glArrayElement(tailWinglines[i * 3 + 1]);  //1
            glArrayElement(tailWinglines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}
