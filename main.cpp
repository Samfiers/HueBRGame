/*
    HueBRGame
    Autor: Samuel de Souza Silva
    Data: 12/06/2017
*/

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <sstream>
#include <string>

#include <time.h>
#include "Stick.h"
#include "Ball.h"

#define MAX_HEIGHT 350
#define MIN_HEIGHT 100
#define MAX_WIDTH  560
#define MIN_WIDTH  40

using namespace std;

GLint movebola = 0,direcao = 1, scoreP1 = 0, scoreP2 = 0;
GLfloat moveHSpeed, luzAmbiente[4] = {1.0,1.0,1.0,1.0};
Stick stick1;
Stick stick2;
Ball ball;
int startGame = clock() * 1000 / CLOCKS_PER_SEC;
float ambientLight[4] = {1.0, 1.0, 1.0, 0.0};
float blueColor[4] = {0.0, 0.0, 1.0, 0.0};

void init(void)
{

    glClearColor(0.0, 0.0, 0.0, 0.0);

    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, 600, 0, 400, -1,1);
    glMatrixMode(GL_MODELVIEW);
}

// Função que recebe a fonte e um texto por parâmetro para ser exibido na
// tela usando caracteres bitmap
void DesenhaTexto(void *font, char *string)
{
    // Exibe caractere a caractere
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++);
}

void display(void)
{
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Iluminação ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    glLineWidth(15.0);

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, stick1.color.rgba());
    glVertex3f(stick1.position.x,stick1.position.y-stick1.height,stick1.position.z);
    glVertex3i(stick1.position.x,stick1.position.y,stick1.position.z);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, stick2.color.rgba());
    glVertex3i(stick2.position.x,stick2.position.y-stick2.height,stick2.position.z);
    glVertex3i(stick2.position.x,stick2.position.y,stick2.position.z);
    glEnd();

    glBegin(GL_LINES);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ball.color.rgba());
    glVertex3f(ball.position.x,ball.position.y-ball.height, ball.position.z);
    glVertex3f(ball.position.x,ball.position.y, ball.position.z);
    glEnd();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, stick1.color.rgba());
    glRasterPos2f(20,380);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,"Player 1");

    stringstream strs;
    strs << scoreP1 << " | " << scoreP2;
    string temp_str = strs.str();
    char* scoreText = (char*) temp_str.c_str();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientLight);
    glRasterPos2f(265,370);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,scoreText);


    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, stick2.color.rgba());
    //glScalef(0.1, 0.1, 0.1); // diminui o tamanho do fonte
    //glRotatef(15, 0,0,1); // rotaciona o texto
    glRasterPos2f(500,380);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,"Player 2");

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambientLight);
    stringstream strsCl;
    strsCl << (startGame + (clock() * 1000 / CLOCKS_PER_SEC))/1000;
    string temp_strCl = strsCl.str();
    char* scoreTimer = (char*) temp_strCl.c_str();

    glRasterPos2f(277,380);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,scoreTimer);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'w' :
        if(stick1.position.y <= MAX_HEIGHT)
        {
            stick1.position.y += 10;
        }
        break;
    case 's' :
        if(stick1.position.y >= MIN_HEIGHT)
        {
            stick1.position.y -= 10;
        }
        break;
    }
}

void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP :
        if(stick2.position.y < MAX_HEIGHT)
        {
            stick2.position.y += 10;
        }
        break;
    case GLUT_KEY_DOWN :
        if(stick2.position.y > MIN_HEIGHT)
        {
            stick2.position.y -= 10;
        }
        break;
    }
    glutPostRedisplay();
}

void bola(int passo)
{
    ball.position.y += moveHSpeed;

    if(direcao==1)
    {
        ball.position.x += 1;

        if(ball.position.x == MAX_WIDTH)
        {

            if(ball.position.y <= stick2.position.y + ball.height && ball.position.y >= stick2.position.y - stick2.height)
            {
                scoreP2++;
                ball.color = Color(0.0, 0.0, 1.0, 0.0);
            }
            else
            {
                ball.color = Color(1.0, 0.0, 0.0, 0.0);
            }
            direcao = 0;
            moveHSpeed = ((rand() % (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT) - ball.position.y) / MAX_WIDTH;

            ball.speed = rand() % 3 + 2;
        }
    }

    else
    {
        ball.position.x -= 1;

        if(ball.position.x == MIN_WIDTH)
        {
            if(ball.position.y <= stick1.position.y + ball.height && ball.position.y >= stick1.position.y - stick1.height)
            {
                scoreP1++;
                ball.color = Color(0.0, 1.0, 0.0, 0.0);
            }
            else
            {
                ball.color = Color(1.0, 0.0, 0.0, 0.0);
            }

            direcao = 1;
            moveHSpeed = ((rand() % (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT) - ball.position.y) / MAX_WIDTH;

            ball.speed = rand() % 3 + 2;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(ball.speed,bola, 1);

}

int main(int argc, char** argv)
{
    /* initialize random seed: */
    srand (time(NULL));

    stick1.position = Position(30.0, 240.0, 0.0);
    stick1.height = 50.0;
    stick1.color = Color(0.0, 1.0, 0.0, 0.0);

    stick2.position = Position(570.0, 240.0, 0.0);
    stick2.height = 50.0;
    stick2.color = Color(0.0, 0.0, 1.0, 0.0);

    ball.position = Position(200.0, 210.0, 0.0);
    ball.height = 5.0;
    ball.speed = 4;
    ball.color = Color(1.0, 1.0, 1.0, 0.0);

    moveHSpeed = ((rand() % (MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT) - ball.position.y) / MAX_WIDTH;

    glutInit(&argc, argv);
    //glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("HUEBRGAME");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(ball.speed,bola,1);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
    return 0;
}


