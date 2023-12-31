#pragma once
#include "GL/freeglut.h"
#include <omp.h>
#define ARRAY_MAX 10000000

float vertex[ARRAY_MAX];
int lines[ARRAY_MAX];
int vertexDataSize = 0, lineDataSize = 0;

void makeShip(float r,float g,float b)
{

    glPointSize(3);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES); 
    {
        for (int i = 0; i < lineDataSize; i++) {
            glArrayElement(lines[i * 3]);   //0
            glArrayElement(lines[i * 3 + 1]);  //1
            glArrayElement(lines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}
