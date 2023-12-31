#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "warship_3d.h"
#include "ret.h"
#include "fire1.h"
#include "fire2.h"
#include "makefloor.h"
#include "misile.h"
#include "wing.h"
#include "ammo.h"
#include "cockPit.h"
#include "tailWing.h"
#include "missileRightRight.h"
#include "missileRightLeft.h"
#include "missileLeftRight.h"
#include "missileLeftLeft.h"
#include "enemy.h"
#include "bullet.h"
#include "3ret.h"
#include "field.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <omp.h>
#include <string>
//#pragma comment (lib, "lib\x86\freeglut.lib")
//bool
bool keys[256];
bool onKeyPress = false;
bool boolBullet = false;
bool dead = false;
bool retry = false;
bool GUI = true;
bool weaponChange = false;
bool checkRightRightFire = false;
bool checkRightLeftFire = false;
bool checkLeftRightFire = false;
bool checkLeftLeftFire = false;
bool twobyone=false,rightButton=false,leftButton = false;
bool enemycreate = false;
bool pause = false;
bool thirdSpec = true;
bool pauseBool = true;
bool timeOver = false;
bool goStraight = false;


//int
int bulletNUM = 0;
int frameCount = 0;
int lastSec = 0;
int score = 0;
int damage = 0;
int bulletCount = 0;
int keyNum = NULL;
int randXNUM, randYNUM, randX,randY,randXnum,randYnum;
int HitCheck;
int list;

//double
double x,y;
double movingBulletX[300];
double movingBulletY[300];
double movingBulletZ[300];
double _movingXPoint;
double _movingYPoint;
double _movingZPoint;
double enemyPosCheck[3];
double RRPosCheck[3];
double RLPosCheck[3];
double LRPosCheck[3];
double LLPosCheck[3];
double firstClickXPos=0,firstClickYPos=0,saveXPos=0,saveYPos = 0;
double LLMissileCont = 0.0, LRMissileCont = 0.0, RLMissileCont = 0.0, RRMissileCont = 0.0;

//float
float movingRRXPoint = 0, movingRRYPoint = 0, movingRLXPoint = 0, movingRLYPoint = 0, movingLRXPoint = 0, movingLRYPoint = 0, movingLLXPoint = 0, movingLLYPoint = 0;
GLfloat red[] = { 1.0, 0.4, 0.3, 1.0 };  //赤
GLfloat blue[] = { 0.4, 0.6, 1.0, 1.0 };  //青
GLfloat green[] = { 0.2,1.0,0.4 };     //緑
GLfloat white[] = { 1,1,1};    //白
float shininess = 128.0;
float rightrightPos = 0,rightleftPos = 0,leftrightPos= 0,leftleftPos = 0;
float diffuse[] = { 1,1,1,1 };
float specular[] = { 1,1,1,1 };
float ambient[] = { 0.1,0.1,0.1,1.0 };
float light[] = { 1.0,1.0,1.0,0.0 };
float enemyPos;

//char
char t_char[20];
char t_char2[20];
char t_char3[20];
char t_char4[60];
char t_char5[20];
char t_char6[30];
char t_char7[40];

//vector
std::pair<std::vector<double>, std::vector<double>> CoordinateXY;

//関数の宣言
void DISPLAY_TEXT(int x, int y, char* string);
void DRAW_STRING(int x, int y, char* string, void* font);
void Bullet(int num);
void disp()
{
    /*
    今後の追加予定
    ・OpenMPを用いたGPUによる並列処理(これはfor分の中身が大きすぎて抜け出せなくなるような場所に使用するべき)
    ・機銃の追加
    ・機銃とミサイルにそれぞれ攻撃力を設定し、それぞれを切り替えるキーバインドの追加
    ・オンライン対戦機能の追加
    ・NPCオブジェクトの追加
    ・追加ミサイルオブジェクトや追加パーツオブジェクトの追加
    ・敵オブジェクトを倒した際にお金をドロップ、そのお金を使って機体のアップグレードできるようにしたい
    ・テクスチャマッピングを用いて青空の描写
    */

        GLfloat light0pos[] = { 10.0 - _movingXPoint, 10.0 - _movingYPoint, 7.0, 0.5 };

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (dead == true)
        {
            sprintf_s(t_char5, "You are dead!");
            DISPLAY_TEXT(46, 55, t_char5);
            sprintf_s(t_char6, "Your score is %d",score);
            DISPLAY_TEXT(46, 50, t_char6);
            sprintf_s(t_char7, "Play Again? --> Y/N");
            DISPLAY_TEXT(44, 42, t_char7);


        }
        if (GUI == true)
        {
            sprintf_s(t_char, "Time: %d", 40 - lastSec);
            DISPLAY_TEXT(0, 95, t_char);
            sprintf_s(t_char2, "Score: %d", score);
            DISPLAY_TEXT(95, 95, t_char2);
            sprintf_s(t_char3, "HP: %d", 10 - damage);
            DISPLAY_TEXT(2, 2, t_char3);
        }
        if(pauseBool == true)
        {
            sprintf_s(t_char4, "Please Press SHIFT_R and start game!");
            DISPLAY_TEXT(40, 55, t_char4);
        }
        if (timeOver == true)
        {
            sprintf_s(t_char5, "Finish!");
            DISPLAY_TEXT(48, 55, t_char5);
            sprintf_s(t_char6, "Your score is %d", score);
            DISPLAY_TEXT(45, 50, t_char6);
            sprintf_s(t_char7, "Play Again? --> Y/N");
            DISPLAY_TEXT(44, 42, t_char7);

        }
        glShadeModel(GL_SMOOTH);
        glLoadIdentity();

        if (thirdSpec == true)
        {
            gluLookAt(0 - _movingXPoint, 1 - _movingYPoint, 10 - _movingZPoint, 0 - _movingXPoint, 1 - _movingYPoint, -_movingZPoint, 0, 1, 0);
        }
        else
        {
            gluLookAt(0 - _movingXPoint, 1 - _movingYPoint, -3, 0 - _movingXPoint, 1 - _movingYPoint, -5, 0, 1, 0);

        }
        glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

        //glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
        //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        //glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        //glMaterialf(GL_FRONT, GL_SHININESS, shininess);

        //地面
        //glColor3f(1, 1, 1);
        //glBegin(GL_TRIANGLES);
        //glNormal3f(0, 1, 0);
        //glVertex3f(100, -20, -200);
        //glVertex3f(100, -20, 10);
        //glVertex3f(-100, -20, -200);
        //glEnd();
        //glBegin(GL_TRIANGLES);
        //glNormal3f(0, 1, 0);
        //glVertex3f(-100, -20, 10);
        //glVertex3f(100, -20, 10);
        //glVertex3f(-100, -20, -200);
        //glEnd();
        glVertexPointer(3, GL_FLOAT, 0, Fieldvertex);
        makeField(1, 1, 1);
        //天井
        //glColor3f(1, 1, 1);
        //glBegin(GL_QUADS);
        //glNormal3f(0, 1, 0);
        //glVertex3f(100, 40, -200);
        //glVertex3f(-100, 40, -200);
        //glVertex3f(-100, 40, 10);
        //glVertex3f(100, 40, 10);
        //glEnd();

        //if (pauseBool == false && dead == false && timeOver == false)
        //{
        //    if (enemycreate == false)
        //    {
        //        randX = rand() % 2;
        //        randY = rand() % 2;

        //        randXnum = rand() % 10;
        //        randYnum = rand() % 4;

        //        enemyPos = 0;
        //        if (randX == 1)
        //        {
        //            randXNUM = -randXnum;
        //        }
        //        else
        //        {
        //            randXNUM = randXnum;
        //        }
        //        if (randY == 1)
        //        {
        //            randYNUM = -randYnum;
        //        }
        //        else
        //        {
        //            randYNUM = randYnum;
        //        }
        //        enemycreate = true;
        //    }
        //    else
        //    {
        //        if (enemyPos > 68.0)
        //        {
        //            enemycreate = false;
        //            damage++;
        //        }
        //        glPushMatrix();
        //        glTranslatef(randXNUM, randYNUM, -70 + enemyPos);
        //        glVertexPointer(3, GL_FLOAT, 0, Enemyvertex);
        //        makeEnemy(1, 1, 1);
        //        glPopMatrix();
        //        enemyPos += 0.03;
        //    }
        //}

        glEnableClientState(GL_VERTEX_ARRAY);


        if (checkRightRightFire == true)
        {
            if (rightrightPos < -150.0)
            {
                checkRightRightFire = false;
                rightrightPos = 0;
                RRMissileCont = 0.0;
            }
            glPushMatrix();

            glTranslatef(movingRRXPoint + RRMissileCont, movingRRYPoint, rightrightPos);
            glVertexPointer(3, GL_FLOAT, 0, RightRightMissilevertex);
            makeRightRightMissile(0.3, 0.3, 0.3);
            glPopMatrix();
            rightrightPos -= 0.1;
            RRMissileCont -= 0.5 / 300.0;
        }

        if (checkRightLeftFire == true)
        {
            if (rightleftPos < -150.0)
            {
                checkRightLeftFire = false;
                rightleftPos = 0;
                RLMissileCont = 0.0;
            }
            glPushMatrix();
            glTranslatef(movingRLXPoint + RLMissileCont, movingRLYPoint, rightleftPos);
            glVertexPointer(3, GL_FLOAT, 0, RightLeftMissilevertex);
            makeRightLeftMissile(0.3, 0.3, 0.3);
            glPopMatrix();
            rightleftPos -= 0.1;
            RLMissileCont -= 0.2 / 300.0;
        }

        if (checkLeftRightFire == true)
        {
            if (leftrightPos < -150.0)
            {
                checkLeftRightFire = false;
                leftrightPos = 0;
                LRMissileCont = 0.0;
            }
            glPushMatrix();
            glTranslatef(movingLRXPoint + LRMissileCont, movingLRYPoint, leftrightPos);
            glVertexPointer(3, GL_FLOAT, 0, LeftRightMissilevertex);
            makeLeftRightMissile(0.3, 0.3, 0.3);
            glPopMatrix();
            leftrightPos -= 0.1;
            LRMissileCont += 0.2 / 300.0;
        }

        if (checkLeftLeftFire == true)
        {
            if (leftleftPos < -150.0)
            {
                checkLeftLeftFire = false;
                leftleftPos = 0;
                LLMissileCont = 0.0;
            }
            glPushMatrix();
            glTranslatef(movingLLXPoint + LLMissileCont, movingLLYPoint, leftleftPos);
            glVertexPointer(3, GL_FLOAT, 0, LeftLeftMissilevertex);
            makeLeftLeftMissile(0.3, 0.3, 0.3);
            glPopMatrix();
            leftleftPos -= 0.1;
            LLMissileCont += 0.5 / 300.0;
        }
        
        //boolBulletがtrueの時for分を作成し続ける

        //if (boolBullet == true)
        //{
        //    glPushMatrix();
        //    glTranslatef(movingBulletX[bulletNUM], movingBulletY[bulletNUM], movingBulletZ[bulletNUM]);
        //    glVertexPointer(3, GL_FLOAT, 0, Bulletvertex);
        //    makeBullet(0.3, 0.3, 0.3);
        //    glPopMatrix();
        //}
        

        if (goStraight == true)
        {
            _movingZPoint += 0.008;
        }

        glPushMatrix();
        glTranslatef(-_movingXPoint, -_movingYPoint, -_movingZPoint);

        if (checkRightRightFire == false)
        {
            glVertexPointer(3, GL_FLOAT, 0, RightRightMissilevertex);
            makeRightRightMissile(0.3, 0.3, 0.3);
        }
        if (checkRightLeftFire == false)
        {
            glVertexPointer(3, GL_FLOAT, 0, RightLeftMissilevertex);
            makeRightLeftMissile(0.3, 0.3, 0.3);
        }
        if (checkLeftRightFire == false)
        {
            glVertexPointer(3, GL_FLOAT, 0, LeftRightMissilevertex);
            makeLeftRightMissile(0.3, 0.3, 0.3);
        }
        if (checkLeftLeftFire == false)
        {
            glVertexPointer(3, GL_FLOAT, 0, LeftLeftMissilevertex);
            makeLeftLeftMissile(0.3, 0.3, 0.3);
        }

        glVertexPointer(3, GL_FLOAT, 0, vertex);
        makeShip(0.3, 0.3, 0.3);

        if (thirdSpec == true)
        {
            glVertexPointer(3, GL_FLOAT, 0, ThirdRvertex);
            make3Ret();

        }
        else
        {
            glVertexPointer(3, GL_FLOAT, 0, Rvertex);
            makeRet();
        }
        glVertexPointer(3, GL_FLOAT, 0, Wingvertex);
        makeWing(0.4, 0.4, 0.4);

        glVertexPointer(3, GL_FLOAT, 0, Fire1vertex);
        fire1(0.44, 0.4, 0.4);

        glVertexPointer(3, GL_FLOAT, 0, Fire2vertex);
        fire2(0.4, 0.4, 0.44);

        glVertexPointer(3, GL_FLOAT, 0, tailWingvertex);
        makeTailWing(0.3, 0.3, 0.3);

        glVertexPointer(3, GL_FLOAT, 0, cockPitvertex);
        makeCockPit(0.8, 0.8, 0.8);



        glPopMatrix();
        if (pauseBool == false && dead == false && timeOver == false)
        {

            if (boolBullet == true)
            {
                frameCount++;
                if (frameCount > 100)
                {
                    frameCount = 0;
                    movingBulletX[bulletNUM] = -_movingXPoint;
                    movingBulletY[bulletNUM] = -_movingYPoint;
                    bulletNUM++;
                    if (bulletNUM == 300)
                    {
                        bulletNUM = 0;
                    }
                }
            }
#pragma omp parallel for
            for (int i = 0; i < bulletNUM; i++)
            {
                Bullet(i);
            }
        }
        glutSwapBuffers();
        glFlush();
}

void Bullet(int num)
{
    if (movingBulletZ[num] > -100)
    {
        glPushMatrix();
        glTranslatef(movingBulletX[num], movingBulletY[num], movingBulletZ[num]);
        glVertexPointer(3, GL_FLOAT, 0, Bulletvertex);
        makeBullet(1, 1, 1);
        glPopMatrix();
        movingBulletZ[num] -= 0.2;
    }
}

void reshape(int width, int height) 
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);					// 射影行列を操作する
    glLoadIdentity();						// 行列を初期化
    gluPerspective(60.0, (double)width / height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    y = 0;
}


void InitialProc(const std::unordered_map<std::string,std::string>& maps)
{
    _movingXPoint = 0;
    _movingYPoint = 0;
    _movingZPoint = 0;
    memset(movingBulletX, 0.0, sizeof(movingBulletX));
    memset(movingBulletY, 0.0, sizeof(movingBulletY));
    memset(movingBulletZ, 0.0, sizeof(movingBulletZ));

    FILE* fpVData, * fpFData, * fpretVData, * fpretFData, * fpFire1VData, * fpFire1FData, * fpFire2VData, * fpFire2FData, * fpWingVData, * fpWingFData, * fpTailWingVData, * fpTailWingFData, * fpCockPitVData, * fpCockPitFData, * fpRightRightMissileVData, * fpRightRightMissileFData, * fpRightLeftMissileVData, * fpRightLeftMissileFData, * fpLeftRightMissileVData, * fpLeftRightMissileFData, * fpLeftLeftMissileVData, * fpLeftLeftMissileFData;
    FILE* fpEnemyVData, * fpEnemyFData, * fpBulletVData, * fpBulletFData, * fp3retVData, * fp3retFData, * fpFieldVData, * fpFieldFData;
    
    fopen_s(&fpVData,maps.at("mainShipV").c_str(), "r");//vData.txtをargs[0]に入れている
    fopen_s(&fpFData, maps.at("mainShipF").c_str(), "r");
    fopen_s(&fpretVData, maps.at("retV").c_str(), "r");
    fopen_s(&fpretFData, maps.at("retF").c_str(), "r");
    fopen_s(&fpFire1VData, maps.at("fire1V").c_str(), "r");
    fopen_s(&fpFire1FData, maps.at("fire1F").c_str(), "r");
    fopen_s(&fpFire2VData, maps.at("fire2V").c_str(), "r");
    fopen_s(&fpFire2FData, maps.at("fire2F").c_str(), "r");
    fopen_s(&fpWingVData, maps.at("wingV").c_str(), "r");
    fopen_s(&fpWingFData, maps.at("wingF").c_str(), "r");
    fopen_s(&fpTailWingVData, maps.at("tailWingV").c_str(), "r");
    fopen_s(&fpTailWingFData, maps.at("tailWingF").c_str(), "r");
    fopen_s(&fpCockPitVData, maps.at("cockPitV").c_str(), "r");
    fopen_s(&fpCockPitFData, maps.at("cockPitF").c_str(), "r");
    fopen_s(&fpRightRightMissileVData, maps.at("RRMissileV").c_str(), "r");
    fopen_s(&fpRightRightMissileFData, maps.at("RRMissileF").c_str(), "r");
    fopen_s(&fpRightLeftMissileVData, maps.at("RLMissileV").c_str(), "r");
    fopen_s(&fpRightLeftMissileFData, maps.at("RLMissileF").c_str(), "r");
    fopen_s(&fpLeftRightMissileVData, maps.at("LRMissileV").c_str(), "r");
    fopen_s(&fpLeftRightMissileFData, maps.at("LRMissileF").c_str(), "r");
    fopen_s(&fpLeftLeftMissileVData, maps.at("LLMissileV").c_str(), "r");
    fopen_s(&fpLeftLeftMissileFData, maps.at("LLMissileF").c_str(), "r");
    fopen_s(&fpEnemyVData, maps.at("enemyV").c_str(), "r");
    fopen_s(&fpEnemyFData, maps.at("enemyF").c_str(), "r");
    fopen_s(&fpBulletVData, maps.at("bulletV").c_str(), "r");
    fopen_s(&fpBulletFData, maps.at("bulletF").c_str(), "r");
    fopen_s(&fp3retVData, maps.at("3retV").c_str(), "r");
    fopen_s(&fp3retFData, maps.at("3retF").c_str(), "r");
    fopen_s(&fpFieldVData, maps.at("fieldV").c_str(), "r");
    fopen_s(&fpFieldFData, maps.at("fieldF").c_str(), "r");

    

    if ((fpVData == NULL) || (fpFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpVData, "%f, %f, %f", &vertex[vertexDataSize * 3], &vertex[vertexDataSize * 3 + 1], &vertex[vertexDataSize * 3 + 2]) != EOF)
            vertexDataSize++;

        while (fscanf_s(fpFData, "%d, %d, %d", &lines[lineDataSize * 3], &lines[lineDataSize * 3 + 1], &lines[lineDataSize * 3 + 2]) != EOF)
            lineDataSize++;
    }
    if ((fpretVData == NULL) || (fpretFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpretVData, "%f, %f, %f", &Rvertex[RvertexDataSize * 3], &Rvertex[RvertexDataSize * 3 + 1], &Rvertex[RvertexDataSize * 3 + 2]) != EOF)
            RvertexDataSize++;

        while (fscanf_s(fpretFData, "%d, %d, %d", &Rlines[RlineDataSize * 3], &Rlines[RlineDataSize * 3 + 1], &Rlines[RlineDataSize * 3 + 2]) != EOF)
            RlineDataSize++;
    }
    if ((fp3retVData == NULL) || (fp3retFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fp3retVData, "%f, %f, %f", &ThirdRvertex[ThirdRvertexDataSize * 3], &ThirdRvertex[ThirdRvertexDataSize * 3 + 1], &ThirdRvertex[ThirdRvertexDataSize * 3 + 2]) != EOF)
            ThirdRvertexDataSize++;

        while (fscanf_s(fp3retFData, "%d, %d, %d", &ThirdRlines[ThirdRlineDataSize * 3], &ThirdRlines[ThirdRlineDataSize * 3 + 1], &ThirdRlines[ThirdRlineDataSize * 3 + 2]) != EOF)
            ThirdRlineDataSize++;
    }

    if ((fpFire1VData == NULL) || (fpFire1FData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpFire1VData, "%f, %f, %f", &Fire1vertex[Fire1vertexDataSize * 3], &Fire1vertex[Fire1vertexDataSize * 3 + 1], &Fire1vertex[Fire1vertexDataSize * 3 + 2]) != EOF)
            Fire1vertexDataSize++;

        while (fscanf_s(fpFire1FData, "%d, %d, %d", &Fire1lines[Fire1lineDataSize * 3], &Fire1lines[Fire1lineDataSize * 3 + 1], &Fire1lines[Fire1lineDataSize * 3 + 2]) != EOF)
            Fire1lineDataSize++;
    }
    if ((fpFire2VData == NULL) || (fpFire2FData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpFire2VData, "%f, %f, %f", &Fire2vertex[Fire2vertexDataSize * 3], &Fire2vertex[Fire2vertexDataSize * 3 + 1], &Fire2vertex[Fire2vertexDataSize * 3 + 2]) != EOF)
            Fire2vertexDataSize++;

        while (fscanf_s(fpFire2FData, "%d, %d, %d", &Fire2lines[Fire2lineDataSize * 3], &Fire2lines[Fire2lineDataSize * 3 + 1], &Fire2lines[Fire2lineDataSize * 3 + 2]) != EOF)
            Fire2lineDataSize++;
    }
    if ((fpWingVData == NULL) || (fpWingFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpWingVData, "%f, %f, %f", &Wingvertex[WingvertexDataSize * 3], &Wingvertex[WingvertexDataSize * 3 + 1], &Wingvertex[WingvertexDataSize * 3 + 2]) != EOF)
            WingvertexDataSize++;

        while (fscanf_s(fpWingFData, "%d, %d, %d", &Winglines[WinglineDataSize * 3], &Winglines[WinglineDataSize * 3 + 1], &Winglines[WinglineDataSize * 3 + 2]) != EOF)
            WinglineDataSize++;
    }


    if ((fpTailWingVData == NULL) || (fpTailWingFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpTailWingVData, "%f, %f, %f", &tailWingvertex[tailWingvertexDataSize * 3], &tailWingvertex[tailWingvertexDataSize * 3 + 1], &tailWingvertex[tailWingvertexDataSize * 3 + 2]) != EOF)
            tailWingvertexDataSize++;

        while (fscanf_s(fpTailWingFData, "%d, %d, %d", &tailWinglines[tailWinglineDataSize * 3], &tailWinglines[tailWinglineDataSize * 3 + 1], &tailWinglines[tailWinglineDataSize * 3 + 2]) != EOF)
            tailWinglineDataSize++;
    }
    if ((fpCockPitVData == NULL) || (fpCockPitFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpCockPitVData, "%f, %f, %f", &cockPitvertex[cockPitvertexDataSize * 3], &cockPitvertex[cockPitvertexDataSize * 3 + 1], &cockPitvertex[cockPitvertexDataSize * 3 + 2]) != EOF)
            cockPitvertexDataSize++;

        while (fscanf_s(fpCockPitFData, "%d, %d, %d", &cockPitlines[cockPitlineDataSize * 3], &cockPitlines[cockPitlineDataSize * 3 + 1], &cockPitlines[cockPitlineDataSize * 3 + 2]) != EOF)
            cockPitlineDataSize++;
    }
    if ((fpRightRightMissileVData == NULL) || (fpRightRightMissileFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpRightRightMissileVData, "%f, %f, %f", &RightRightMissilevertex[RightRightMissilevertexDataSize * 3], &RightRightMissilevertex[RightRightMissilevertexDataSize * 3 + 1], &RightRightMissilevertex[RightRightMissilevertexDataSize * 3 + 2]) != EOF)
            RightRightMissilevertexDataSize++;

        while (fscanf_s(fpRightRightMissileFData, "%d, %d, %d", &RightRightMissilelines[RightRightMissilelineDataSize * 3], &RightRightMissilelines[RightRightMissilelineDataSize * 3 + 1], &RightRightMissilelines[RightRightMissilelineDataSize * 3 + 2]) != EOF)
            RightRightMissilelineDataSize++;
    }
    if ((fpRightLeftMissileVData == NULL) || (fpRightLeftMissileFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpRightLeftMissileVData, "%f, %f, %f", &RightLeftMissilevertex[RightLeftMissilevertexDataSize * 3], &RightLeftMissilevertex[RightLeftMissilevertexDataSize * 3 + 1], &RightLeftMissilevertex[RightLeftMissilevertexDataSize * 3 + 2]) != EOF)
            RightLeftMissilevertexDataSize++;

        while (fscanf_s(fpRightLeftMissileFData, "%d, %d, %d", &RightLeftMissilelines[RightLeftMissilelineDataSize * 3], &RightLeftMissilelines[RightLeftMissilelineDataSize * 3 + 1], &RightLeftMissilelines[RightLeftMissilelineDataSize * 3 + 2]) != EOF)
            RightLeftMissilelineDataSize++;
    }
    if ((fpLeftRightMissileVData == NULL) || (fpLeftRightMissileFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpLeftRightMissileVData, "%f, %f, %f", &LeftRightMissilevertex[LeftRightMissilevertexDataSize * 3], &LeftRightMissilevertex[LeftRightMissilevertexDataSize * 3 + 1], &LeftRightMissilevertex[LeftRightMissilevertexDataSize * 3 + 2]) != EOF)
            LeftRightMissilevertexDataSize++;

        while (fscanf_s(fpLeftRightMissileFData, "%d, %d, %d", &LeftRightMissilelines[LeftRightMissilelineDataSize * 3], &LeftRightMissilelines[LeftRightMissilelineDataSize * 3 + 1], &LeftRightMissilelines[LeftRightMissilelineDataSize * 3 + 2]) != EOF)
            LeftRightMissilelineDataSize++;
    }
    if ((fpLeftLeftMissileVData == NULL) || (fpLeftLeftMissileFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpLeftLeftMissileVData, "%f, %f, %f", &LeftLeftMissilevertex[LeftLeftMissilevertexDataSize * 3], &LeftLeftMissilevertex[LeftLeftMissilevertexDataSize * 3 + 1], &LeftLeftMissilevertex[LeftLeftMissilevertexDataSize * 3 + 2]) != EOF)
            LeftLeftMissilevertexDataSize++;

        while (fscanf_s(fpLeftLeftMissileFData, "%d, %d, %d", &LeftLeftMissilelines[LeftLeftMissilelineDataSize * 3], &LeftLeftMissilelines[LeftLeftMissilelineDataSize * 3 + 1], &LeftLeftMissilelines[LeftLeftMissilelineDataSize * 3 + 2]) != EOF)
            LeftLeftMissilelineDataSize++;
    }
    if ((fpEnemyVData == NULL) || (fpEnemyFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpEnemyVData, "%f, %f, %f", &Enemyvertex[EnemyvertexDataSize * 3], &Enemyvertex[EnemyvertexDataSize * 3 + 1], &Enemyvertex[EnemyvertexDataSize * 3 + 2]) != EOF)
            EnemyvertexDataSize++;

        while (fscanf_s(fpEnemyFData, "%d, %d, %d", &Enemylines[EnemylineDataSize * 3], &Enemylines[EnemylineDataSize * 3 + 1], &Enemylines[EnemylineDataSize * 3 + 2]) != EOF)
            EnemylineDataSize++;
    }
    if ((fpBulletVData == NULL) || (fpBulletFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpBulletVData, "%f, %f, %f", &Bulletvertex[BulletvertexDataSize * 3], &Bulletvertex[BulletvertexDataSize * 3 + 1], &Bulletvertex[BulletvertexDataSize * 3 + 2]) != EOF)
            BulletvertexDataSize++;

        while (fscanf_s(fpBulletFData, "%d, %d, %d", &Bulletlines[BulletlineDataSize * 3], &Bulletlines[BulletlineDataSize * 3 + 1], &Bulletlines[BulletlineDataSize * 3 + 2]) != EOF)
            BulletlineDataSize++;
    }
    if ((fpFieldVData == NULL) || (fpFieldFData == NULL)) {
        printf("file error!!\n");
        return;
    }
    else
    {
        while (fscanf_s(fpFieldVData, "%f, %f, %f", &Fieldvertex[FieldvertexDataSize * 3], &Fieldvertex[FieldvertexDataSize * 3 + 1], &Fieldvertex[FieldvertexDataSize * 3 + 2]) != EOF)
            FieldvertexDataSize++;

        while (fscanf_s(fpFieldFData, "%d, %d, %d", &Fieldlines[FieldlineDataSize * 3], &Fieldlines[FieldlineDataSize * 3 + 1], &Fieldlines[FieldlineDataSize * 3 + 2]) != EOF)
            FieldlineDataSize++;
    }

}
void keyUp(unsigned char key, int x, int y)
{
    if (key == 'w')
    {
        goStraight = false;
    }
}
void keyboard(unsigned char key, int x, int y)
{
    if (key == 0x1b)
        exit(0);

    if (key == 'w')
    {
        goStraight = true;
    }
    if (key == 'v')
    {
        if (thirdSpec == true)
        {
            thirdSpec = false;
        }
        else
        {
            thirdSpec = true;
        }
    }
    if (key == 'c')
    {
        if (weaponChange == false)
        {
            weaponChange = true;
        }
        else
        {
            weaponChange = false;
        }
    }
    if (retry == true)
    {
        if (key == 'y')
        {
            dead = false;
            retry = false;
            GUI = true;
            weaponChange = false;
            checkRightRightFire = false;
            checkRightLeftFire = false;
            checkLeftRightFire = false;
            checkLeftLeftFire = false;
            twobyone = false, rightButton = false, leftButton = false;
            enemycreate = false;
            pause = false;
            thirdSpec = true;
            pauseBool = true;
            timeOver = false;
            boolBullet = false;


            memset(movingBulletX, 0.0, sizeof(movingBulletX));
            memset(movingBulletY, 0.0, sizeof(movingBulletY));
            memset(movingBulletZ, 0.0, sizeof(movingBulletZ));

            score = 0;
            damage = 0;
            bulletNUM = 0;
            lastSec = 0;
            bulletCount = 0;


        }
        else if (key == 'n')
        {
            exit(0);
        }
    }
}
void spe(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        keyNum = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        keyNum = GLUT_KEY_DOWN;
        break;
    case GLUT_KEY_LEFT:
        keyNum = GLUT_KEY_LEFT;
        break;
    case GLUT_KEY_RIGHT:
        keyNum = GLUT_KEY_RIGHT;
        break;
    case GLUT_KEY_HOME:
        if (checkRightRightFire == true && checkLeftLeftFire == true && checkLeftRightFire == true)
        {
            checkRightLeftFire = true;
            movingRLXPoint = -_movingXPoint;
            movingRLYPoint = -_movingYPoint;
        }
        if (checkRightRightFire == true && checkLeftRightFire == true)
        {
            checkLeftLeftFire = true;
            movingLLXPoint = -_movingXPoint;
            movingLLYPoint = -_movingYPoint;
        }
        else if (checkLeftRightFire == true)
        {
            checkRightRightFire = true;
            movingRRXPoint = -_movingXPoint;
            movingRRYPoint = -_movingYPoint;
        }
        else if (checkRightLeftFire == true)
        {
            checkLeftRightFire = true;
            movingLRXPoint = -_movingXPoint;
            movingLRYPoint = -_movingYPoint;
        }
        else if (checkLeftLeftFire == true)
        {
            checkRightLeftFire = true;
            movingRLXPoint = -_movingXPoint;
            movingRLYPoint = -_movingYPoint;
        }
        else if (checkRightRightFire == true)
        {
            checkLeftLeftFire = true;
            movingLLXPoint = -_movingXPoint;
            movingLLYPoint = -_movingYPoint;
        }
        else if (checkLeftLeftFire == false && checkLeftRightFire == false && checkRightLeftFire == false && checkRightRightFire == false)
        {
            checkRightRightFire = true;
            movingRRXPoint = -_movingXPoint;
            movingRRYPoint = -_movingYPoint;
        }
        break;
    case GLUT_KEY_SHIFT_R:
        if (pauseBool == true)
        {
            pauseBool = false;
            GUI = true;
        }
        else
        {
            pauseBool = true;
            GUI = false;
        }
        break;
    case GLUT_KEY_SHIFT_L:
        break;
    }
    onKeyPress = true;
}
void speUP(int key, int x, int y)
{
    onKeyPress = false;
    keyNum = NULL;
}

void idle(void)
{
    if (damage == 10)
    {
        dead = true;
        retry = true;
        GUI = false;
    }
    HitCheck = 0;

    enemyPosCheck[0] = randXNUM;
    enemyPosCheck[1] = randYNUM;
    enemyPosCheck[2] = enemyPos - 70;
    if (checkRightRightFire == true)
    {
        RRPosCheck[0] = movingRRXPoint;
        RRPosCheck[1] = movingRRYPoint;
        RRPosCheck[2] = rightrightPos;
    }
    else
    {
        RRPosCheck[0] = -_movingXPoint;
        RRPosCheck[1] = -_movingYPoint;
        RRPosCheck[2] = 0;
    }
    if (checkRightLeftFire == true)
    {
        RLPosCheck[0] = movingRLXPoint;
        RLPosCheck[1] = movingRLYPoint;
        RLPosCheck[2] = rightleftPos;
    }
    else
    {
        RLPosCheck[0] = -_movingXPoint;
        RLPosCheck[1] = -_movingYPoint;
        RLPosCheck[2] = 0;
    }
    if (checkLeftRightFire == true)
    {
        LRPosCheck[0] = movingLRXPoint;
        LRPosCheck[1] = movingLRYPoint;
        LRPosCheck[2] = leftrightPos;
    }
    else
    {
        LRPosCheck[0] = -_movingXPoint;
        LRPosCheck[1] = -_movingYPoint;
        LRPosCheck[2] = 0;
    }
    if (checkLeftLeftFire == true)
    {
        LLPosCheck[0] = movingLLXPoint;
        LLPosCheck[1] = movingLLYPoint;
        LLPosCheck[2] = leftleftPos;
    }
    else
    {
        LLPosCheck[0] = -_movingXPoint;
        LLPosCheck[1] = -_movingYPoint;
        LLPosCheck[2] = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        if (enemyPosCheck[i] + 0.62 > RRPosCheck[i] && RRPosCheck[i] > enemyPosCheck[i] - 0.62)
        {
            HitCheck++;
        }
        if (HitCheck == 3)
        {
            enemycreate = false;
            movingRRYPoint += 50;
            score++;
            HitCheck = 0;
        }

    }
    HitCheck = 0;
    for (int i = 0; i < 3; i++)
    {
        if (enemyPosCheck[i] + 0.62 > RLPosCheck[i] && RLPosCheck[i] > enemyPosCheck[i] - 0.62)
        {
            HitCheck++;
        }
        if (HitCheck == 3)
        {
            enemycreate = false;
            movingRLYPoint += 50;
            score++;
            HitCheck = 0;
        }
    }
    HitCheck = 0;
    for (int i = 0; i < 3; i++)
    {
        if (enemyPosCheck[i] + 0.62 > LRPosCheck[i] && LRPosCheck[i] > enemyPosCheck[i] - 0.62)
        {
            HitCheck++;
        }
        if (HitCheck == 3)
        {
            enemycreate = false;
            movingLRYPoint += 50;
            score++;
            HitCheck = 0;
        }
    }
    HitCheck = 0;
    for (int i = 0; i < 3; i++)
    {
        if (enemyPosCheck[i] + 0.62 > LLPosCheck[i] && LLPosCheck[i] > enemyPosCheck[i] - 0.62)
        {
            HitCheck++;
        }
        if (HitCheck == 3)
        {
            enemycreate = false;
            movingLLYPoint += 50;
            score++;
            HitCheck = 0;
        }
    }
    
    //if (_movingXPoint > 20)
    //    _movingXPoint = -20;
    //if (_movingXPoint < -20)
    //    _movingXPoint = 20;
    //if (_movingYPoint > 8)
    //    _movingYPoint = -10;
    //if (_movingYPoint < -10)
    //    _movingYPoint = 8;

    if (onKeyPress)
    {
        if (keyNum == GLUT_KEY_UP)
        {
            _movingYPoint -= 0.05;

        }
        if (keyNum == GLUT_KEY_DOWN)
        {
            _movingYPoint += 0.05;


        }
        if (keyNum == GLUT_KEY_LEFT)
        {
            _movingXPoint += 0.05;


        }
        if (keyNum == GLUT_KEY_RIGHT)
        {
            _movingXPoint -= 0.05;


        }

    }
    glutPostRedisplay();


}

void mouse(int button, int state, int x, int y)//マウスをクリックする瞬間しか読まない
{
    if (pauseBool == false && dead == false && timeOver == false)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (weaponChange == false)
            {
                if (twobyone == false)
                {
                    if (checkRightRightFire == true && checkLeftLeftFire == true && checkLeftRightFire == true)
                    {
                        checkRightLeftFire = true;
                        movingRLXPoint = -_movingXPoint;
                        movingRLYPoint = -_movingYPoint;
                    }
                    if (checkRightRightFire == true && checkLeftRightFire == true)
                    {
                        checkLeftLeftFire = true;
                        movingLLXPoint = -_movingXPoint;
                        movingLLYPoint = -_movingYPoint;
                    }
                    else if (checkLeftRightFire == true)
                    {
                        checkRightRightFire = true;
                        movingRRXPoint = -_movingXPoint;
                        movingRRYPoint = -_movingYPoint;
                    }
                    else if (checkRightLeftFire == true)
                    {
                        checkLeftRightFire = true;
                        movingLRXPoint = -_movingXPoint;
                        movingLRYPoint = -_movingYPoint;
                    }
                    else if (checkLeftLeftFire == true)
                    {
                        checkRightLeftFire = true;
                        movingRLXPoint = -_movingXPoint;
                        movingRLYPoint = -_movingYPoint;
                    }
                    else if (checkRightRightFire == true)
                    {
                        checkLeftLeftFire = true;
                        movingLLXPoint = -_movingXPoint;
                        movingLLYPoint = -_movingYPoint;
                    }
                    else if (checkLeftLeftFire == false && checkLeftRightFire == false && checkRightLeftFire == false && checkRightRightFire == false)
                    {
                        checkRightRightFire = true;
                        movingRRXPoint = -_movingXPoint;
                        movingRRYPoint = -_movingYPoint;
                    }
                    twobyone = true;
                }
                else
                {
                    twobyone = false;
                }
            }
            else
            {
                //ここに弾丸
                if (boolBullet == true)
                {
                    boolBullet = false;

                }
                else
                {
                    boolBullet = true;

                }

            }
        }
    }
}
void passiveMotion(int x, int y)
{
    if (pauseBool == false && dead == false && timeOver == false)
    {
        _movingXPoint -= (x - 900) / 50.0;
        _movingYPoint += (y - 500) / 50.0;
        glutWarpPointer(900, 500);
        glutMouseFunc(mouse);
    }
}
void clickingMotion(int x, int y)//クリックしながら動かさないと読まない
{
    if (pauseBool == false && dead == false && timeOver == false)
    {
        _movingXPoint -= (x - 900) / 50.0;
        _movingYPoint += (y - 500) / 50.0;
        glutWarpPointer(900, 500);
        glutMouseFunc(mouse);
    }

}
void DISPLAY_TEXT(int x, int y, char* string) {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glPushAttrib(GL_ENABLE_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glCallList(list);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
    glMatrixMode(GL_MODELVIEW);
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    DRAW_STRING(x, y, string, GLUT_BITMAP_HELVETICA_18);
    glEndList();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
void DRAW_STRING(int x, int y, char* string, void* font) {
    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++) {

        glutBitmapCharacter(font, string[i]);
    }
}
void timerCallback(int x)
{
    if (pauseBool == false && dead == false && timeOver == false)
    {
        lastSec += 1;
        if (lastSec == 40)
        {
            retry = true;
            GUI = false;
            timeOver = true;
        }
        glutPostRedisplay();
    }
    glutTimerFunc(1000, timerCallback, 0);
}
int main(int argc, char** argv)
{
    
    glutInit(&argc, argv);
    glutInitWindowSize(1980, 1080);
    glutCreateWindow("Ace combat");
    glutWarpPointer(900, 500);

    //glutSetCursor(GLUT_CURSOR_NONE);
    //std::vector<std::string> args;
    //for (int i = 1; i < argc; ++i)
    //{
    //    args.push_back(argv[i]);
    //}

    std::unordered_map<std::string, std::string> map;
    map.insert(std::make_pair("mainShipV", "config/vData.txt"));
    map.insert(std::make_pair("mainShipF", "config/fData.txt"));
    map.insert(std::make_pair("cockPitV", "config/cockPitVData.txt"));
    map.insert(std::make_pair("cockPitF", "config/cockPitFData.txt"));
    map.insert(std::make_pair("enemyV", "config/enemyVData.txt"));
    map.insert(std::make_pair("enemyF", "config/enemyFData.txt"));
    map.insert(std::make_pair("fire1V", "config/fire1VData.txt"));
    map.insert(std::make_pair("fire1F", "config/fire1FData.txt"));
    map.insert(std::make_pair("fire2V", "config/fire2VData.txt"));
    map.insert(std::make_pair("fire2F", "config/fire2FData.txt"));
    map.insert(std::make_pair("RRMissileV", "config/missileRightRightVData.txt"));
    map.insert(std::make_pair("RRMissileF", "config/missileRightRightFData.txt"));
    map.insert(std::make_pair("RLMissileV", "config/missileRightLeftVData.txt"));
    map.insert(std::make_pair("RLMissileF", "config/missileRightLeftFData.txt"));
    map.insert(std::make_pair("LLMissileV", "config/missileLeftLeftVData.txt"));
    map.insert(std::make_pair("LLMissileF", "config/missileLeftLeftFData.txt"));
    map.insert(std::make_pair("LRMissileV", "config/missileLeftRightVData.txt"));
    map.insert(std::make_pair("LRMissileF", "config/missileLeftRightFData.txt"));
    map.insert(std::make_pair("retV", "config/retVData.txt"));
    map.insert(std::make_pair("retF", "config/retFData.txt"));
    map.insert(std::make_pair("tailWingV", "config/tailWingVData.txt"));
    map.insert(std::make_pair("tailWingF", "config/tailWingFData.txt"));
    map.insert(std::make_pair("wingV", "config/wingVData.txt"));
    map.insert(std::make_pair("wingF", "config/wingFData.txt"));
    map.insert(std::make_pair("bulletV", "config/bulletVData.txt"));
    map.insert(std::make_pair("bulletF", "config/bulletFData.txt"));
    map.insert(std::make_pair("3retV", "config/3retVData.txt"));
    map.insert(std::make_pair("3retF", "config/3retFData.txt"));
    map.insert(std::make_pair("fieldV", "config/fieldVData.txt"));
    map.insert(std::make_pair("fieldF", "config/fieldFData.txt"));

    //for (const auto& m:n)
    //{
    //    m.second;
    //}
    //glRotatef(30, 1.0, 0, 0);
    //glRotatef(30, 0, 1.0, 0);
    //glScalef(0.8, 0.8, 0.8);
    glutGameModeString("1920x1080:1@60");  // 解像度とビット深度を適切に指定
    glutEnterGameMode();
    glutSetCursor(GLUT_CURSOR_NONE);

    InitialProc(map);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(spe);
    glutSpecialUpFunc(speUP);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passiveMotion);
    glutMotionFunc(clickingMotion);
    glutMouseFunc(mouse);

    glutIdleFunc(idle);
    glutReshapeFunc(reshape);   
    glutDisplayFunc(disp);
    glutTimerFunc(1000, timerCallback, 0);
    glutIgnoreKeyRepeat(GL_TRUE);
    glutKeyboardFunc(keyboard);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);        //ライティングON
    glEnable(GL_LIGHT0);

    glutMainLoop();

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);        //ライティングOFF
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);


    return 0;
}