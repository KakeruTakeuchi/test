#include "glut.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define T 100

int moveR = 0; //右移動フラグ．0:オフ，1:オン
int moveL = 0; //左移動フラグ．0:オフ，1:オン
int moveW = 0;//下移動フラグ．0:オフ，1:オン
int moveS = 0;//上移動フラグ．0:オフ，1:オン
int angle = 45;//飛行機角度
int Move = 0;//動く敵
int AngleUP = 0;//上向き飛行機角度移動フラグ．0:オフ，1:オン
int AngleDW = 0;//下向き飛行機角度移動フラグ．0:オフ，1:オン
int Showline = 0; //集中線表示
int line = 0; //集中線表示中
float LineCam = 0.0;//集中線カメラ
int Life = 2; //0:当たっていない状態 1:ヒットした状態  2:メニュー　3:クリア



double x = 0.0; //座標系
double y = 0.0;
double y2 = 0.0;
double Angle = 0.0;
double z = 0.0;
double Zangle = 45;
double PlaneX = 0; //飛行機座標
double PlaneY = 0;
double PlaneZ = 0;
double PlaneXangle = 0;//飛行機角度
double PlaneYangle = 0;
int score = 0;//距離(スコア)
int finalscore = 0;//最終スコア
float LimitTime = 60;//時間制限
double RingX = 0;//リング座標系
double RingY = 0;
double RingZ = -1;
double RingX2 = -2;
double RingY2 = 0;
double RingZ2 = -10;
double PointX = 1;//球座標系
double PointY = 0;
double PointZ = -4;
double MovePointX = 1;//動く球座標
double MovePointY = 0;
double MovePointZ = -8;
int Aangle = 0; //集中線フラグ
double CloudX1 = -5;//雲座標系
double CloudY1 = 1;
double CloudZ1 = 0;
double CloudX2 = 0;
double CloudY2 = 3;
double CloudZ2 = 0;
double CloudX3 = 3;
double CloudY3 = -2;
double CloudZ3 = 0;
int BestScore = 0; //ベストスコア



float amber[] = { 1.0, 0.5, 0.0, 1.0 };   //アンバー
float blue[] = { 0.0, 0.8, 1.0, 1.0 };    //青
float sky[] = { 0.0, 0.95, 0.97, 1.0 };    //空
float yellow[] = { 1.0, 1, 0.0, 0.0 };    //黄色
float plane[] = { 0.0, 0.1, 0.5, 0.7 };    //紙飛行機
float positionR[] = { 1.0, 1.0, 1.0, 0.0 };   //右上位置
float positionL[] = { -1.0, 1.0, 1.0, 0.0 };  //左上位置
float black[] = { 0.0, 0.0, 0.0, 1.0 };   //黒

void KeyboardHandler(unsigned char key, int x, int y)
{
    if (Life == 2) { //スタート画面
        CloudX1 = -3;
        CloudY1 = 1;
        CloudZ1 = -2;
        CloudX2 = 3;
        CloudY2 = 3;
        CloudZ2 = -4;
        CloudX3 = 3;
        CloudY3 = -3;
        CloudZ3 = -7;
        PlaneY = 0;
        Life = 0;
    }

    if (Life == 1 || Life == 3) { //リザルト画面
        if (key == ' ')
        {

            //値の初期化
            x = 0.0;
            y = 0.0;
            y2 = 0.0;
            z = 0.0;
            Zangle = 45;
            PlaneX = 0;
            PlaneY = 0;
            PlaneZ = 1;
            PlaneXangle = 0;
            PlaneYangle = 0;
            score = 0;
            finalscore = 0;
            LimitTime = 60;
            RingX = 0;
            RingY = 0;
            RingZ = -1;
            RingX2 = -2;
            RingY2 = 0;
            RingZ2 = -10;
            PointX = 1;
            PointY = 0;
            PointZ = -4;
            MovePointX = 1;
            MovePointY = 0;
            MovePointZ = -8;
            Aangle = 0;
            CloudX1 = -3;
            CloudY1 = 1;
            CloudZ1 = -2;
            CloudX2 = 3;
            CloudY2 = 3;
            CloudZ2 = -4;
            CloudX3 = 3;
            CloudY3 = -3;
            CloudZ3 = -7;
            Life = 0;

        }
    }


    if (key == 'd')         //右旋回
    {
        if (moveR == 0) {
            moveR = 1;
            moveL = 0;
        }
        else
            moveR = 0;
    }

    if (key == 'a')         //左旋回
    {
        if (moveL == 0) {
            moveL = 1;
            moveR = 0;
        }
        else
            moveL = 0;
    }

    if (key == 's')         //上昇
    {
        if (moveS == 0) {
            moveS = 1;
            moveW = 0;
        }
        else
            moveS = 0;
    }

    if (key == 'w')         //下降
    {
        if (moveW == 0) {
            moveW = 1;
            moveS = 0;
        }
        else
            moveW = 0;
    }

}


void PaperAirplane(void) //飛行機モデリング
{
    glBegin(GL_TRIANGLE_STRIP);
    glNormal3d(0, 0, 1);
    glVertex3d(-1, +1, +1);
    glVertex3d(+2, 0.5, +1);
    glVertex3d(+2, +1, +1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glNormal3d(0, +1, -0.3);
    glVertex3d(+2, +1, 1);
    glVertex3d(3, +1.3, +2.5);
    glVertex3d(-1, +1, +1);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glNormal3d(0, +1, 0.3);
    glVertex3d(+2, +1, 1);
    glVertex3d(3, +1.3, -1.5);
    glVertex3d(-1, +1, +1);
    glEnd();
}

void EmphasisLines(void) //強調線モデリング
{
    glBegin(GL_LINES);
    glVertex3d(-0.4, 1.0, 3.0);
    glVertex3d(-0.1, -0.6, 0.0);
    glVertex3d(0.1, 1.0, 3.0);
    glVertex3d(0.1, -0.6, 0.0);
    glVertex3d(0.7, 1.0, 3.0);
    glVertex3d(0.3, -0.6, 0.0);
    glVertex3d(0.5, -1.0, 0.0);
    glVertex3d(1.0, 1.0, 3.0);
    glVertex3d(0.3, -0.8, 0.0);
    glVertex3d(2.0, 1.5, 3.0);
    glVertex3d(2.5, 1.3, 2.0);
    glVertex3d(1.4, -0.7, 0.0);
    glVertex3d(2.8, 1.3, 2.0);
    glVertex3d(1.4, -0.7, 0.0);
    glVertex3d(2.9, 1.0, 2.0);
    glVertex3d(1.1, -0.9, 0.0);
    glVertex3d(2.9, 0.5, 2.0);
    glVertex3d(1.1, -1.3, 0.0);
    glVertex3d(2.9, 0, 2.0);
    glVertex3d(1.1, -1.5, 0.0);
    glVertex3d(2.9, -1, 2.0);
    glVertex3d(1.1, -1.7, 0.0);
    glVertex3d(2.9, -1, 9.0);
    glVertex3d(0.8, -1.5, 0.0);
    glVertex3d(2.9, -1.5, 9.0);
    glVertex3d(1.0, -2.0, 0.0);
    glVertex3d(2.9, -1.7, 9.0);
    glVertex3d(1.2, -3.0, 0.0);
    glVertex3d(2.9, -1.0, 9.0);
    glVertex3d(0.8, -2.0, 0.0);
    glVertex3d(2.9, -2.3, 9.0);
    glVertex3d(0.6, -1.8, 0.0);
    glVertex3d(2.9, -2.6, 9.0);
    glVertex3d(0.9, -1.9, 0.0);
    glVertex3d(2.9, -2.9, 9.0);
    glVertex3d(0.6, -2.5, 0.0);
    glVertex3d(2.9, -3.3, 9.0);
    glVertex3d(0.9, -2.9, 0.0);
    glVertex3d(2.9, -3.9, 9.0);
    glVertex3d(0.2, -3.1, 0.0);
    glVertex3d(1.5, -3.9, 9.0);
    glVertex3d(-0.2, -3.1, 0.0);
    glVertex3d(1.0, -3.9, 9.0);
    glVertex3d(0, -3.5, 0.0);
    glVertex3d(0, -3.9, 9.0);
    glVertex3d(0, -3.5, 0.0);
    glVertex3d(-0.5, -3.9, 9.0);
    glVertex3d(-0.5, -3.5, 0.0);

    glEnd();
}

void Cloud(void) { //雲モデリング
    glutSolidSphere(0.7, 20, 20);
    glTranslated(1, 0, 0);
    glutSolidSphere(0.7, 20, 20);
    glTranslated(1, 0, 0);
    glutSolidSphere(0.7, 20, 20);
    glTranslated(1, 0, 0);
    glutSolidSphere(0.7, 20, 20);
    glTranslated(-3, 0.7, 0);
    glutSolidSphere(0.5, 20, 20);
    glTranslated(1, 0, 0);
    glutSolidSphere(0.7, 20, 20);
    glTranslated(1, 0, 0);
    glutSolidSphere(0.7, 20, 20);
    glTranslated(1, 0, 0);
    glutSolidSphere(0.7, 20, 20);
}



void renderBitmapString(float x, float y, float z, void* font, const char* format, ...) // 文字表示関数の宣言
{
    char buffer[256]; // バッファの設定
    va_list args; // 可変引数リストの宣言
    va_start(args, format); // 可変引数リストの初期化
    vsnprintf(buffer, sizeof(buffer), format, args); // バッファにフォーマットされた文字列を格納
    va_end(args); // 可変引数リストの終了

    const char* c; // 文字ポインタの宣言
    glRasterPos3f(x, y, z); // ラスタ位置の設定
    for (c = buffer; *c != '\0'; c++) { // 文字数をカウントしながらループ
        glutBitmapCharacter(font, *c); // ビットマップで文字の描画
    }
}

void display(void)
{
    gluPerspective(Zangle, 1.0, 1.0, 10.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(PlaneX - 0.6, PlaneY + 0.8, PlaneZ + 3 + LineCam, PlaneX - 0.6, PlaneY + 0.8, PlaneZ + LineCam, 0, 1, 0);

    glTranslated(0.0, 0.0, -6.0);

    float position[] = { x, 1, z + 5, 0.0 };
    glPushMatrix();
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glPopMatrix();

    /////////////////////////////ゲーム中の画面表示////////////////////////////////////
    if (Life == 0) {
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslated(0, 0, PlaneZ);
        glBegin(GL_POLYGON);      //下面表示
        glNormal3d(0, 1, 0);
        glVertex3d(-40, -3, +40);
        glVertex3d(+40, -3, +40);
        glVertex3d(+40, -3, -40);
        glVertex3d(-40, -3, -40);
        glEnd();
        glPopMatrix();

        glPushMatrix(); //雲1
        glTranslated(CloudX1, CloudY1, CloudZ1);
        glRotated(30, 0, 1, 0);
        glScaled(0.8, 0.8, 0.8);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //雲2
        glTranslated(CloudX2, CloudY2, CloudZ2);
        glRotated(-30, 0, 1, 0);
        glScaled(0.6, 0.6, 0.6);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //雲3
        glTranslated(CloudX3, CloudY3, CloudZ3);
        glRotated(-10, 0, 1, 0);
        glScaled(0.5, 0.5, 0.5);
        Cloud();
        glPopMatrix();



        if (Showline == 1) {//集中線表示フラグオンの時
            glPushMatrix(); //集中線右
            glTranslated(PlaneX, PlaneY + 2, PlaneZ + 1);
            glRotated(Aangle, 0, 0, 1);
            EmphasisLines();
            glPopMatrix();

            glPushMatrix(); //集中線左
            glTranslated(PlaneX - 1.7, PlaneY - 1, PlaneZ + 1);
            glRotated(Aangle, 0, 0, 1);
            glRotated(160, 0, 0, 1);
            EmphasisLines();
            glPopMatrix();
        }


        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sky);//背景表示
        glBegin(GL_POLYGON);
        glNormal3d(0, 0, 1);
        glVertex3d(+40, -40, PlaneZ - 0.99);
        glVertex3d(+40, +40, PlaneZ - 0.99);
        glVertex3d(-40, +40, PlaneZ - 0.99);
        glVertex3d(-40, -40, PlaneZ - 0.99);
        glEnd();



        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, amber);
        glLightfv(GL_LIGHT0, GL_AMBIENT, black);

        glPushMatrix(); //球体
        glTranslated(PointX, PointY, PointZ);
        glRotated(90, 1, 0, 0);
        glScaled(0.8, 0.8, 0.8);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();





        glPushMatrix(); //飛行機当たり判定
        glTranslated(PlaneX - 0.7, PlaneY, PlaneZ);
        glRotated(90, 1, 0, 0);
        glScaled(0.3, 0.3, 0.3);
        //  glutSolidSphere(1, 20, 20);
        glPopMatrix();




        glPushMatrix(); //球体当たり判定
        glTranslated(RingX2 - 0.8, RingY2, RingZ2);
        glRotated(90, 1, 0, 0);
        glScaled(0.1, 0.1, 0.1);
        //    glutSolidSphere(1, 20, 20);
        glPopMatrix();


        glPushMatrix(); //リング
        glTranslated(RingX, RingY, RingZ);
        glRotated(90, 0, 0, 1);
        glScaled(2.5, 2.5, 2.5);
        glutSolidTorus(0.1, 0.8, 20, 20);
        glPopMatrix();




        glTranslated(0.0, 0.2, 0);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, plane);
        glLightfv(GL_LIGHT0, GL_AMBIENT, plane);
        glLightfv(GL_LIGHT0, GL_POSITION, positionL);
        glShadeModel(GL_FLAT);

        glPushMatrix(); //動く球体
        glTranslated(MovePointX, MovePointY, MovePointZ);
        glRotated(90, 1, 0, 0);
        glScaled(0.4, 0.4, 0.4);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();




        glPushMatrix(); //飛行機表示
        glTranslated(PlaneX, PlaneY, PlaneZ);
        glTranslated(0, -1.2, 2);
        glRotated(PlaneXangle, 0, 0, 1);
        glRotated(PlaneXangle, 0, 1, 0);
        glRotated(PlaneYangle, 1, 0, 0);
        glRotated(-90, 0, 1, 0);
        glRotated(-10, 0, 0, 1);
        glScaled(0.8, 0.8, 0.8);
        PaperAirplane();
        glPopMatrix();

        glPushMatrix(); //Ring2表示
        glTranslated(RingX2, RingY2, RingZ2);
        glRotated(90, 0, 0, 1);
        glScaled(0.4, 0.4, 0.4);
        glScaled(2.5, 2.5, 2.5);
        glutSolidTorus(0.1, 0.8, 20, 20);
        glPopMatrix();


        glColor3f(1.0, 1.0, 1.0);


        glLightfv(GL_LIGHT0, GL_DIFFUSE, amber);
        renderBitmapString(PlaneX - 3.8, PlaneY + 3.6, PlaneZ, GLUT_BITMAP_HELVETICA_18, "Distance: %d m", score);
        renderBitmapString(PlaneX + 1, PlaneY + 3.6, PlaneZ, GLUT_BITMAP_HELVETICA_18, "Time: %d s", (int)LimitTime);
    }
    /////////////////////////////ゲームオーバー画面////////////////////////////////////
    if (Life == 1) {
        glDisable(GL_LIGHTING);
        renderBitmapString(PlaneX - 1.8, PlaneY + 3.0, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Best Score :\n %d m", BestScore);
        renderBitmapString(PlaneX - 1.8, PlaneY + 0.5, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Game Over\n %d m", score);
        renderBitmapString(PlaneX - 2.0, PlaneY, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "SPACE KEY to continue");
    }
    /////////////////////////////スタート画面////////////////////////////////////
    if (Life == 2) {
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sky);
        glBegin(GL_POLYGON);
        glNormal3d(0, 0, 1);
        glVertex3d(+40, -40, PlaneZ - 0.99);
        glVertex3d(+40, +40, PlaneZ - 0.99);
        glVertex3d(-40, +40, PlaneZ - 0.99);
        glVertex3d(-40, -40, PlaneZ - 0.99);
        glEnd();
        glLightfv(GL_LIGHT0, GL_DIFFUSE, plane);
        glLightfv(GL_LIGHT0, GL_AMBIENT, plane);
        glLightfv(GL_LIGHT0, GL_POSITION, positionL);
        glShadeModel(GL_FLAT);
        glPushMatrix();
        glTranslated(0, PlaneY, 0);
        glTranslated(0, 0.4, 2);
        glRotated(-5, 1, 0, 0);
        glRotated(Angle, 1, 0, 0);
        glRotated(10, 0, 0, 1);
        glScaled(0.8, 0.8, 0.8);
        PaperAirplane();
        glPopMatrix();

        glDisable(GL_LIGHTING);

        glPushMatrix(); //雲1
        glTranslated(CloudX1, CloudY1, CloudZ1);
        glRotated(30, 0, 1, 0);
        glScaled(0.8, 0.8, 0.8);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //雲2
        glTranslated(CloudX2, CloudY2, CloudZ2);
        glRotated(-30, 0, 1, 0);
        glScaled(0.6, 0.6, 0.6);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //雲3
        glTranslated(CloudX3, CloudY3, CloudZ3);
        glRotated(-10, 0, 1, 0);
        glScaled(0.5, 0.5, 0.5);
        Cloud();
        glPopMatrix();



        renderBitmapString(PlaneX - 1.9, PlaneY, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "SPACE KEY to START");
    }

    /////////////////////////////ゲームクリア画面////////////////////////////////////
    if (Life == 3) {
        glPushMatrix();
        glTranslated(PlaneX, PlaneY, PlaneZ);
        glTranslated(0, -1.2, 2);
        glRotated(0, 0, 1, 0);
        glRotated(30, 0, 0, 1);
        glScaled(0.8, 0.8, 0.8);
        PaperAirplane();
        glPopMatrix();
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
        glBegin(GL_POLYGON);
        glNormal3d(0, 0, 1);
        glVertex3d(+40, -40, PlaneZ - 0.99);
        glVertex3d(+40, +40, PlaneZ - 0.99);
        glVertex3d(-40, +40, PlaneZ - 0.99);
        glVertex3d(-40, -40, PlaneZ - 0.99);
        glEnd();

        glDisable(GL_LIGHTING);
        renderBitmapString(PlaneX - 1.5, PlaneY + 3.0, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Best Score :\n %d m", BestScore);
        renderBitmapString(PlaneX - 1.5, PlaneY + 0.9, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Conglutination!!");
        renderBitmapString(PlaneX - 1.5, PlaneY + 0.5, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Result\n %d m", finalscore);
        renderBitmapString(PlaneX - 2.0, PlaneY - 2, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "SPACE KEY to continue");
    }


    glFlush();
}

int Kasoku = 0; //加速フラグ．0:オフ，1:オン
int RandomA = 0; //乱数A
int RandomB = 0; //乱数B

void IncAngle(int timer)
{
    srand(time(NULL));//乱数設定のためtime関数を設定
    RandomA = rand() % 5 - 3;//乱数A設定
    if (timer != 1) return;
    if (Life == 0) {//ゲーム中の更新
        score += 1;//スコアを常に1足す
        LimitTime -= 0.1;//制限時間を減らす
        if (LimitTime <= 0.0) {//制限時間が0秒
            finalscore = score;//スコアの更新
            if (BestScore < score)//ベストスコアなら更新
                BestScore = score;
            Life = 3;//リザルトへ
        }

    }
    /////////////////////////////スタート画面////////////////////////////////////
    if (Life == 2) {
        //以下飛行機を動かす
        if (Move == 0 && PlaneY >= -0.4) {
            PlaneY -= 0.01;
            Angle += 0.1;
            if (PlaneY <= -0.3)
                Move = 1;

        }
        else if (Move == 1 && PlaneY <= 0.4) {
            PlaneY += 0.01;
            Angle -= 0.15;
            if (PlaneY >= 0.3)
                Move = 0;

        }

        //以下雲を動かす
        CloudX1 += 0.05;
        CloudX2 += 0.05;
        CloudX3 += 0.05;


        if (CloudX1 >= 4) {
            CloudX1 = -7;
            CloudY1 = RandomA;
        }
        if (CloudX2 >= 5) {
            CloudX2 = -8;
            CloudY2 = RandomA;
        }
        if (CloudX3 >= 5.5) {
            CloudX3 = -6;
            CloudY3 = RandomA;
        }


    }

    if (Life == 0) { //ゲーム中の更新


        PlaneZ -= 0.07; //飛行機のz座標を常に下げる

        /////////////////////////////動く球を動かす////////////////////////////////////
        if (Move == 0 && MovePointX <= 2.1) {
            MovePointX -= 0.1;
            if (MovePointX <= -2)
                Move = 1;

        }
        else if (Move == 1 && MovePointX >= -2.1) {
            MovePointX += 0.1;
            if (MovePointX >= 2)
                Move = 0;

        }
        /////////////////////////////以下当たり判定////////////////////////////////////
        //以下リングの当たり判定
        if (PlaneX - 0.7 <= RingX + 2 && PlaneX - 0.7 >= RingX - 2 && PlaneY <= RingY + 2 && PlaneY >= RingY - 2 && PlaneZ <= RingZ && PlaneZ >= RingZ - 1.4 || PlaneX - 0.7 <= RingX2 + 0.8 && PlaneX - 0.7 >= RingX2 - 0.8 && PlaneY <= RingY2 + 1 && PlaneY >= RingY2 - 0.6 && PlaneZ <= RingZ2 && PlaneZ >= RingZ2 - 4) {
            LineCam = -0.5;//カメラをアップ
            Showline = 1;//集中線の描画オン
            score += 2;//スコアを2上げる
            PlaneZ -= 0.15; //飛行機のz座標を動かす
            if (Aangle >= 15) //集中線を動かす
                Aangle -= 3;
            else
                Aangle += 3;

        }
        else {
            Showline = 0; //集中線の描画オフ
            LineCam = 0; //カメラをアップをオフ
        }


        //以下球の当たり判定
        if (PlaneX - 0.7 <= PointX + 0.7 && PlaneX - 0.7 >= PointX - 0.7 && PlaneY <= PointY + +0.6 && PlaneY >= PointY - 1.0 && PlaneZ <= PointZ - 0.5 && PlaneZ >= PointZ - 3.0) {
            if (BestScore < score)
                BestScore = score;
            Life = 1;
        }


        //以下動く球の当たり判定
        if (PlaneX - 0.7 <= MovePointX + 0.3 && PlaneX - 0.7 >= MovePointX - 0.3 && PlaneY <= MovePointY + +0.6 && PlaneY >= MovePointY - 0.2 && PlaneZ <= MovePointZ - 0.5 && PlaneZ >= MovePointZ - 3.0) {

            if (BestScore < score)
                BestScore = score;
            Life = 1;
        }

        if (PlaneZ <= MovePointZ - 4.0) {//飛行機のz座標を過ぎると動く球のz座標を下げる
            MovePointZ -= 9;
            MovePointY = RandomA + 2;
        }


        if (PlaneZ <= CloudZ3 - 5.0) {//飛行機のz座標を過ぎると雲のz座標を下げる
            CloudZ3 -= 6;
            CloudX3 = RandomB - 4;
            CloudY3 = RandomA + 2;
        }

        if (PlaneZ <= CloudZ1 - 4.0) {//飛行機のz座標を過ぎると雲のz座標を下げる
            CloudZ1 -= 8;
            CloudX1 = RandomA - 4;
            CloudY1 = RandomB - 2;
        }

        if (PlaneZ <= CloudZ2 - 4.5) {//飛行機のz座標を過ぎると雲のz座標を下げる
            CloudZ2 -= 7;
            CloudX2 = RandomA + 4;
            CloudY2 = RandomB + 2;
        }

        if (PlaneZ <= RingZ - 1.1) {//飛行機のz座標を過ぎるとリングのz座標を下げる
            RingZ -= 4;
            RingX = RandomA;
            RingY = RandomB;
        }

        if (PlaneZ <= RingZ2 - 3) {//飛行機のz座標を過ぎるとリング2のz座標を下げる
            RingZ2 -= 10;
            RingX2 = RandomA;
            RingY2 = RandomB;
        }



        if (PlaneZ <= PointZ - 3.0) {//飛行機のz座標を過ぎると球のz座標を下げる
            PointZ -= 6;
            PointX = RandomA;
            PointY = RandomB;
        }

        if (moveR == 1) {//dを押されたらx座標を上げる
            PlaneXangle = -15;
            PlaneX = PlaneX + 0.1;
            moveL = 0;
        }

        if (moveL == 1) {//aを押されたらx座標を下げる
            PlaneXangle = 15;
            PlaneX = PlaneX - 0.1;
            moveR = 0;
        }

        if (moveW == 1) {//wを押されたらy座標を下降
            PlaneYangle = -60;
            PlaneY = PlaneY - 0.1;
            moveS = 0;
        }

        if (moveS == 1) {//sを押されたらy座標を上昇
            PlaneYangle = 15;
            PlaneY = PlaneY + 0.1;
            moveW = 0;
        }

        if (moveS == 0 && moveW == 0) PlaneYangle = 0; //飛行機の縦方向角度

        if (moveL == 0 && moveR == 0) PlaneXangle = 0;//飛行機の横方向角度

        RandomB = rand() % 5 - 2;//乱数設定

    }

    glutTimerFunc(T, IncAngle, 1);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("電22-98 竹内　駿瑠");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutKeyboardFunc(KeyboardHandler);
    glutTimerFunc(T, IncAngle, 1);
    glutMainLoop();
}
