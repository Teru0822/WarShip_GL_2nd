#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

float Bulletvertex[ARRAY_MAX];
int Bulletlines[ARRAY_MAX];
int BulletvertexDataSize = 0, BulletlineDataSize = 0;

void makeBullet(float r, float g, float b)
{

    glPointSize(3);
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < BulletlineDataSize; i++) {
            glArrayElement(Bulletlines[i * 3]);   //0
            glArrayElement(Bulletlines[i * 3 + 1]);  //1
            glArrayElement(Bulletlines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}