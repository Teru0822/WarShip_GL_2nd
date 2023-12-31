#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float Wingvertex[ARRAY_MAX];
int Winglines[ARRAY_MAX];
int WingvertexDataSize = 0, WinglineDataSize = 0;

void makeWing(float r ,float g ,float b)
{
    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        
        for (int i = 0; i < WinglineDataSize; i++) {
            glArrayElement(Winglines[i * 3]);   //0
            glArrayElement(Winglines[i * 3 + 1]);  //1
            glArrayElement(Winglines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
