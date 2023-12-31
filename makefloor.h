#pragma once
#include "GL/freeglut.h"

void makefloor(double _movingXPoint,double _movingYPoint)
{

    glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(200 + _movingXPoint, -2 + _movingYPoint, -200);
        glVertex3f(200 + _movingXPoint, -2 + _movingYPoint, 10);
        glVertex3f(100 + _movingXPoint, -2 + _movingYPoint, -200);
    }
    glEnd();
    glColor3f(0, 1, 0);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(100 + _movingXPoint, -2 + _movingYPoint, 10);
        glVertex3f(200 + _movingXPoint, -2 + _movingYPoint, 10);
        glVertex3f(100 + _movingXPoint, -2 + _movingYPoint, -200);
    }
    glEnd();
    glFlush();
}