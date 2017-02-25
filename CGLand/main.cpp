//
//  main.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 22/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//



#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#include <math.h>
#include <stdio.h>

#include "Ground.hpp"

float posCameraX,posCameraY,posCameraZ;
Ground g1 = *new Ground(5,5,5,80,20);


void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    //inicializa posição da câmera
    posCameraX = 0.3;
    posCameraY = 0.4;
    posCameraZ = -2;
    
   
    
}

// Testador de teclados
void specialKeys(int key, int x, int y)
{
    float angulo = 2*M_PI/180;
    switch (key) {
        case GLUT_KEY_LEFT :
            posCameraX =  posCameraX*cos(-angulo) + posCameraZ*sin(-angulo);
            posCameraZ = -posCameraX*sin(-angulo) + posCameraZ*cos(-angulo);
            break;
        case GLUT_KEY_RIGHT :
            posCameraX =  posCameraX*cos(angulo) + posCameraZ*sin(angulo);
            posCameraZ = -posCameraX*sin(angulo) + posCameraZ*cos(angulo);
            break;
        case GLUT_KEY_PAGE_UP :
            posCameraY = posCameraY+0.3;
            break;
        case GLUT_KEY_PAGE_DOWN :
            posCameraY = posCameraY-0.3;
            break;
        case GLUT_KEY_HOME :
            posCameraZ = posCameraZ+0.3;
            break;
        case GLUT_KEY_END :
            posCameraZ = posCameraZ-0.3;
            break;
    }
    glutPostRedisplay();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt (posCameraX, posCameraY, posCameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    glColor3f (0.7, 0.7, 1.0);
    glutWireTeapot(0.5);
    //glutWireSphere(0.5,20,20);
    
    //visualização dos eixos
    //exercício: faça um plano sob a chaleira
    /* glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 10.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
     */
    g1.generateIsle();

    //troca de buffers, o flush é implícito aqui
    glutSwapBuffers();
}

//função chamada quando a tela é redimensionada
void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("CGLand");
    
    init ();
    
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    
    return 0;
}
