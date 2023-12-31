#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

float ThirdRvertex[ARRAY_MAX];
int ThirdRlines[ARRAY_MAX];
int ThirdRvertexDataSize = 0, ThirdRlineDataSize = 0;


void make3Ret()
{
    glPointSize(3);
    glColor3f(0, 1, 1);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < ThirdRlineDataSize; i++) {
            glArrayElement(ThirdRlines[i * 3]);   //0
            glArrayElement(ThirdRlines[i * 3 + 1]);  //1
            glArrayElement(ThirdRlines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
