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
#include "camera.h"
#include "Zebra.hpp"


#define ShowUpvector

CCamera Camera;

float posCameraX,posCameraY,posCameraZ;
float pitch, yaw, walk;
Ground g1 = *new Ground(15,12,15,80,20);
Zebra z = *new Zebra(2.0,2.0,2.0);
void *walls;
int wallsLength = 0;

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    //inicializa posição da câmera
    posCameraX = 0.3;
    posCameraY = 0.4;
    posCameraZ = -10;
    //inicializa olhar da câmera
    pitch = 0.0;
    yaw = 0.0;
    walk = -10.0;
    
    g1.generateIsle();
    
    
    
   
    
}

// Testador de teclados
void KeyDown(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 27:		//ESC
		//PostQuitMessage(0);
		break;
	case 'a':		
		Camera.RotateY(5.0);
		break;
	case 'd':		
		Camera.RotateY(-5.0);
		break;
	case 'w':		
		Camera.MoveForward( -0.1 ) ;
		break;
	case 's':		
		Camera.MoveForward( 0.1 ) ;
		break;
	case 'x':		
		Camera.RotateX(5.0);
		break;
	case 'y':		
		Camera.RotateX(-5.0);
		break;
	case 'c':		
		Camera.StrafeRight(-0.1);
		break;
	case 'v':		
		Camera.StrafeRight(0.1);
		break;
	case 'f':
		Camera.MoveUpward(-0.3);
		break;
	case 'r':
		Camera.MoveUpward(0.3);
		break;

	case 'm':
		Camera.RotateZ(-5.0);
		break;
	case 'n':
		Camera.RotateZ(5.0);
		break;

	}
	
	glutPostRedisplay();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Camera.Render();
    glTranslatef(-1.0,-1.5,-10.0); //Posicionamento inicial
    glPopMatrix();
    
    //glColor3f (0.7, 0.7, 1.0);
    //glutWireTeapot(0.5);
    //glutWireSphere(0.5,20,20);

    
    //visualização dos eixos
    //exercício: faça um plano sob a chaleira
    glBegin(GL_LINES);
    glLineWidth(10.0);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    
    g1.drawIsle();
    z.walk(g1.walls, g1.wallsLength);
    
    

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
    glutKeyboardFunc(KeyDown);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    
    return 0;
}
