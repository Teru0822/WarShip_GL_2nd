#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

//namespace field 
//{
float Fieldvertex[ARRAY_MAX];
int Fieldlines[ARRAY_MAX];
int FieldvertexDataSize = 0, FieldlineDataSize = 0;

void makeField(float r, float g, float b)
{

    glPointSize(3);
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < FieldlineDataSize; i++) {
            glArrayElement(Fieldlines[i * 3]);   //0
            glArrayElement(Fieldlines[i * 3 + 1]);  //1
            glArrayElement(Fieldlines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}
//}