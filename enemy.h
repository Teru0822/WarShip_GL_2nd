#pragma once
#include "GL/freeglut.h"
#define ARRAY_MAX 10000000

float Enemyvertex[ARRAY_MAX];
int Enemylines[ARRAY_MAX];
int EnemyvertexDataSize = 0, EnemylineDataSize = 0;

void makeEnemy(float r, float g, float b)
{

    glPointSize(3);
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    {
        for (int i = 0; i < EnemylineDataSize; i++) {
            glArrayElement(Enemylines[i * 3]);   //0
            glArrayElement(Enemylines[i * 3 + 1]);  //1
            glArrayElement(Enemylines[i * 3 + 2]);  //2
        }
    }
    glEnd();

}