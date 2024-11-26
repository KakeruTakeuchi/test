#include "glut.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define T 100

int moveR = 0; //�E�ړ��t���O�D0:�I�t�C1:�I��
int moveL = 0; //���ړ��t���O�D0:�I�t�C1:�I��
int moveW = 0;//���ړ��t���O�D0:�I�t�C1:�I��
int moveS = 0;//��ړ��t���O�D0:�I�t�C1:�I��
int angle = 45;//��s�@�p�x
int Move = 0;//�����G
int AngleUP = 0;//�������s�@�p�x�ړ��t���O�D0:�I�t�C1:�I��
int AngleDW = 0;//��������s�@�p�x�ړ��t���O�D0:�I�t�C1:�I��
int Showline = 0; //�W�����\��
int line = 0; //�W�����\����
float LineCam = 0.0;//�W�����J����
int Life = 2; //0:�������Ă��Ȃ���� 1:�q�b�g�������  2:���j���[�@3:�N���A



double x = 0.0; //���W�n
double y = 0.0;
double y2 = 0.0;
double Angle = 0.0;
double z = 0.0;
double Zangle = 45;
double PlaneX = 0; //��s�@���W
double PlaneY = 0;
double PlaneZ = 0;
double PlaneXangle = 0;//��s�@�p�x
double PlaneYangle = 0;
int score = 0;//����(�X�R�A)
int finalscore = 0;//�ŏI�X�R�A
float LimitTime = 60;//���Ԑ���
double RingX = 0;//�����O���W�n
double RingY = 0;
double RingZ = -1;
double RingX2 = -2;
double RingY2 = 0;
double RingZ2 = -10;
double PointX = 1;//�����W�n
double PointY = 0;
double PointZ = -4;
double MovePointX = 1;//���������W
double MovePointY = 0;
double MovePointZ = -8;
int Aangle = 0; //�W�����t���O
double CloudX1 = -5;//�_���W�n
double CloudY1 = 1;
double CloudZ1 = 0;
double CloudX2 = 0;
double CloudY2 = 3;
double CloudZ2 = 0;
double CloudX3 = 3;
double CloudY3 = -2;
double CloudZ3 = 0;
int BestScore = 0; //�x�X�g�X�R�A



float amber[] = { 1.0, 0.5, 0.0, 1.0 };   //�A���o�[
float blue[] = { 0.0, 0.8, 1.0, 1.0 };    //��
float sky[] = { 0.0, 0.95, 0.97, 1.0 };    //��
float yellow[] = { 1.0, 1, 0.0, 0.0 };    //���F
float plane[] = { 0.0, 0.1, 0.5, 0.7 };    //����s�@
float positionR[] = { 1.0, 1.0, 1.0, 0.0 };   //�E��ʒu
float positionL[] = { -1.0, 1.0, 1.0, 0.0 };  //����ʒu
float black[] = { 0.0, 0.0, 0.0, 1.0 };   //��

void KeyboardHandler(unsigned char key, int x, int y)
{
    if (Life == 2) { //�X�^�[�g���
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

    if (Life == 1 || Life == 3) { //���U���g���
        if (key == ' ')
        {

            //�l�̏�����
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


    if (key == 'd')         //�E����
    {
        if (moveR == 0) {
            moveR = 1;
            moveL = 0;
        }
        else
            moveR = 0;
    }

    if (key == 'a')         //������
    {
        if (moveL == 0) {
            moveL = 1;
            moveR = 0;
        }
        else
            moveL = 0;
    }

    if (key == 's')         //�㏸
    {
        if (moveS == 0) {
            moveS = 1;
            moveW = 0;
        }
        else
            moveS = 0;
    }

    if (key == 'w')         //���~
    {
        if (moveW == 0) {
            moveW = 1;
            moveS = 0;
        }
        else
            moveW = 0;
    }

}


void PaperAirplane(void) //��s�@���f�����O
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

void EmphasisLines(void) //���������f�����O
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

void Cloud(void) { //�_���f�����O
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



void renderBitmapString(float x, float y, float z, void* font, const char* format, ...) // �����\���֐��̐錾
{
    char buffer[256]; // �o�b�t�@�̐ݒ�
    va_list args; // �ψ������X�g�̐錾
    va_start(args, format); // �ψ������X�g�̏�����
    vsnprintf(buffer, sizeof(buffer), format, args); // �o�b�t�@�Ƀt�H�[�}�b�g���ꂽ��������i�[
    va_end(args); // �ψ������X�g�̏I��

    const char* c; // �����|�C���^�̐錾
    glRasterPos3f(x, y, z); // ���X�^�ʒu�̐ݒ�
    for (c = buffer; *c != '\0'; c++) { // ���������J�E���g���Ȃ��烋�[�v
        glutBitmapCharacter(font, *c); // �r�b�g�}�b�v�ŕ����̕`��
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

    /////////////////////////////�Q�[�����̉�ʕ\��////////////////////////////////////
    if (Life == 0) {
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslated(0, 0, PlaneZ);
        glBegin(GL_POLYGON);      //���ʕ\��
        glNormal3d(0, 1, 0);
        glVertex3d(-40, -3, +40);
        glVertex3d(+40, -3, +40);
        glVertex3d(+40, -3, -40);
        glVertex3d(-40, -3, -40);
        glEnd();
        glPopMatrix();

        glPushMatrix(); //�_1
        glTranslated(CloudX1, CloudY1, CloudZ1);
        glRotated(30, 0, 1, 0);
        glScaled(0.8, 0.8, 0.8);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //�_2
        glTranslated(CloudX2, CloudY2, CloudZ2);
        glRotated(-30, 0, 1, 0);
        glScaled(0.6, 0.6, 0.6);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //�_3
        glTranslated(CloudX3, CloudY3, CloudZ3);
        glRotated(-10, 0, 1, 0);
        glScaled(0.5, 0.5, 0.5);
        Cloud();
        glPopMatrix();



        if (Showline == 1) {//�W�����\���t���O�I���̎�
            glPushMatrix(); //�W�����E
            glTranslated(PlaneX, PlaneY + 2, PlaneZ + 1);
            glRotated(Aangle, 0, 0, 1);
            EmphasisLines();
            glPopMatrix();

            glPushMatrix(); //�W������
            glTranslated(PlaneX - 1.7, PlaneY - 1, PlaneZ + 1);
            glRotated(Aangle, 0, 0, 1);
            glRotated(160, 0, 0, 1);
            EmphasisLines();
            glPopMatrix();
        }


        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, sky);//�w�i�\��
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

        glPushMatrix(); //����
        glTranslated(PointX, PointY, PointZ);
        glRotated(90, 1, 0, 0);
        glScaled(0.8, 0.8, 0.8);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();





        glPushMatrix(); //��s�@�����蔻��
        glTranslated(PlaneX - 0.7, PlaneY, PlaneZ);
        glRotated(90, 1, 0, 0);
        glScaled(0.3, 0.3, 0.3);
        //  glutSolidSphere(1, 20, 20);
        glPopMatrix();




        glPushMatrix(); //���̓����蔻��
        glTranslated(RingX2 - 0.8, RingY2, RingZ2);
        glRotated(90, 1, 0, 0);
        glScaled(0.1, 0.1, 0.1);
        //    glutSolidSphere(1, 20, 20);
        glPopMatrix();


        glPushMatrix(); //�����O
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

        glPushMatrix(); //��������
        glTranslated(MovePointX, MovePointY, MovePointZ);
        glRotated(90, 1, 0, 0);
        glScaled(0.4, 0.4, 0.4);
        glutSolidSphere(1, 20, 20);
        glPopMatrix();




        glPushMatrix(); //��s�@�\��
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

        glPushMatrix(); //Ring2�\��
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
    /////////////////////////////�Q�[���I�[�o�[���////////////////////////////////////
    if (Life == 1) {
        glDisable(GL_LIGHTING);
        renderBitmapString(PlaneX - 1.8, PlaneY + 3.0, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Best Score :\n %d m", BestScore);
        renderBitmapString(PlaneX - 1.8, PlaneY + 0.5, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "Game Over\n %d m", score);
        renderBitmapString(PlaneX - 2.0, PlaneY, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "SPACE KEY to continue");
    }
    /////////////////////////////�X�^�[�g���////////////////////////////////////
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

        glPushMatrix(); //�_1
        glTranslated(CloudX1, CloudY1, CloudZ1);
        glRotated(30, 0, 1, 0);
        glScaled(0.8, 0.8, 0.8);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //�_2
        glTranslated(CloudX2, CloudY2, CloudZ2);
        glRotated(-30, 0, 1, 0);
        glScaled(0.6, 0.6, 0.6);
        Cloud();
        glPopMatrix();

        glPushMatrix(); //�_3
        glTranslated(CloudX3, CloudY3, CloudZ3);
        glRotated(-10, 0, 1, 0);
        glScaled(0.5, 0.5, 0.5);
        Cloud();
        glPopMatrix();



        renderBitmapString(PlaneX - 1.9, PlaneY, PlaneZ + 2, GLUT_BITMAP_HELVETICA_18, "SPACE KEY to START");
    }

    /////////////////////////////�Q�[���N���A���////////////////////////////////////
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

int Kasoku = 0; //�����t���O�D0:�I�t�C1:�I��
int RandomA = 0; //����A
int RandomB = 0; //����B

void IncAngle(int timer)
{
    srand(time(NULL));//�����ݒ�̂���time�֐���ݒ�
    RandomA = rand() % 5 - 3;//����A�ݒ�
    if (timer != 1) return;
    if (Life == 0) {//�Q�[�����̍X�V
        score += 1;//�X�R�A�����1����
        LimitTime -= 0.1;//�������Ԃ����炷
        if (LimitTime <= 0.0) {//�������Ԃ�0�b
            finalscore = score;//�X�R�A�̍X�V
            if (BestScore < score)//�x�X�g�X�R�A�Ȃ�X�V
                BestScore = score;
            Life = 3;//���U���g��
        }

    }
    /////////////////////////////�X�^�[�g���////////////////////////////////////
    if (Life == 2) {
        //�ȉ���s�@�𓮂���
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

        //�ȉ��_�𓮂���
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

    if (Life == 0) { //�Q�[�����̍X�V


        PlaneZ -= 0.07; //��s�@��z���W����ɉ�����

        /////////////////////////////�������𓮂���////////////////////////////////////
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
        /////////////////////////////�ȉ������蔻��////////////////////////////////////
        //�ȉ������O�̓����蔻��
        if (PlaneX - 0.7 <= RingX + 2 && PlaneX - 0.7 >= RingX - 2 && PlaneY <= RingY + 2 && PlaneY >= RingY - 2 && PlaneZ <= RingZ && PlaneZ >= RingZ - 1.4 || PlaneX - 0.7 <= RingX2 + 0.8 && PlaneX - 0.7 >= RingX2 - 0.8 && PlaneY <= RingY2 + 1 && PlaneY >= RingY2 - 0.6 && PlaneZ <= RingZ2 && PlaneZ >= RingZ2 - 4) {
            LineCam = -0.5;//�J�������A�b�v
            Showline = 1;//�W�����̕`��I��
            score += 2;//�X�R�A��2�グ��
            PlaneZ -= 0.15; //��s�@��z���W�𓮂���
            if (Aangle >= 15) //�W�����𓮂���
                Aangle -= 3;
            else
                Aangle += 3;

        }
        else {
            Showline = 0; //�W�����̕`��I�t
            LineCam = 0; //�J�������A�b�v���I�t
        }


        //�ȉ����̓����蔻��
        if (PlaneX - 0.7 <= PointX + 0.7 && PlaneX - 0.7 >= PointX - 0.7 && PlaneY <= PointY + +0.6 && PlaneY >= PointY - 1.0 && PlaneZ <= PointZ - 0.5 && PlaneZ >= PointZ - 3.0) {
            if (BestScore < score)
                BestScore = score;
            Life = 1;
        }


        //�ȉ��������̓����蔻��
        if (PlaneX - 0.7 <= MovePointX + 0.3 && PlaneX - 0.7 >= MovePointX - 0.3 && PlaneY <= MovePointY + +0.6 && PlaneY >= MovePointY - 0.2 && PlaneZ <= MovePointZ - 0.5 && PlaneZ >= MovePointZ - 3.0) {

            if (BestScore < score)
                BestScore = score;
            Life = 1;
        }

        if (PlaneZ <= MovePointZ - 4.0) {//��s�@��z���W���߂���Ɠ�������z���W��������
            MovePointZ -= 9;
            MovePointY = RandomA + 2;
        }


        if (PlaneZ <= CloudZ3 - 5.0) {//��s�@��z���W���߂���Ɖ_��z���W��������
            CloudZ3 -= 6;
            CloudX3 = RandomB - 4;
            CloudY3 = RandomA + 2;
        }

        if (PlaneZ <= CloudZ1 - 4.0) {//��s�@��z���W���߂���Ɖ_��z���W��������
            CloudZ1 -= 8;
            CloudX1 = RandomA - 4;
            CloudY1 = RandomB - 2;
        }

        if (PlaneZ <= CloudZ2 - 4.5) {//��s�@��z���W���߂���Ɖ_��z���W��������
            CloudZ2 -= 7;
            CloudX2 = RandomA + 4;
            CloudY2 = RandomB + 2;
        }

        if (PlaneZ <= RingZ - 1.1) {//��s�@��z���W���߂���ƃ����O��z���W��������
            RingZ -= 4;
            RingX = RandomA;
            RingY = RandomB;
        }

        if (PlaneZ <= RingZ2 - 3) {//��s�@��z���W���߂���ƃ����O2��z���W��������
            RingZ2 -= 10;
            RingX2 = RandomA;
            RingY2 = RandomB;
        }



        if (PlaneZ <= PointZ - 3.0) {//��s�@��z���W���߂���Ƌ���z���W��������
            PointZ -= 6;
            PointX = RandomA;
            PointY = RandomB;
        }

        if (moveR == 1) {//d�������ꂽ��x���W���グ��
            PlaneXangle = -15;
            PlaneX = PlaneX + 0.1;
            moveL = 0;
        }

        if (moveL == 1) {//a�������ꂽ��x���W��������
            PlaneXangle = 15;
            PlaneX = PlaneX - 0.1;
            moveR = 0;
        }

        if (moveW == 1) {//w�������ꂽ��y���W�����~
            PlaneYangle = -60;
            PlaneY = PlaneY - 0.1;
            moveS = 0;
        }

        if (moveS == 1) {//s�������ꂽ��y���W���㏸
            PlaneYangle = 15;
            PlaneY = PlaneY + 0.1;
            moveW = 0;
        }

        if (moveS == 0 && moveW == 0) PlaneYangle = 0; //��s�@�̏c�����p�x

        if (moveL == 0 && moveR == 0) PlaneXangle = 0;//��s�@�̉������p�x

        RandomB = rand() % 5 - 2;//�����ݒ�

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
    glutCreateWindow("�d22-98 �|���@�x��");

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
