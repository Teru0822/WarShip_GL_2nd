#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

float Ammovertex[ARRAY_MAX];
int Ammolines[ARRAY_MAX];
int AmmovertexDataSize = 0, AmmolineDataSize = 0;

void makeAmmo()
{
    glPointSize(3);
    glColor4f(1, 0, 0,1);
    glBegin(GL_TRIANGLES); //–Ê‚Ì•`ŽÊ
    {
        for (int i = 0; i < AmmolineDataSize; i++) {
            glArrayElement(Ammolines[i * 3]);   //0
            glArrayElement(Ammolines[i * 3 + 1]);  //1
            glArrayElement(Ammolines[i * 3 + 2]);  //2
        }
    }
    glEnd();
}
