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
//#include "Zebra.hpp"
#include "carregadorObj.cpp"
#include <iostream>
#include <fstream>


#define ShowUpvector

//variaveis do input.txt
std::string cena;
int x,y,z;
std::string ilhas;
int pIlha;
std::string lagos;
int pLagos;
std::string leoes;
int leoesQtd, leoesIt;
std::string zebras;
int zebrasQtd, zebrasIt;
std::string plantas;
int plantasQtd, plantasIt;

CCamera Camera;

float posCameraX,posCameraY,posCameraZ;
float pitch, yaw, walk;


Ground g1 = *new Ground(x,y,z,pIlha,pLagos, plantasQtd, zebrasQtd, leoesQtd, zebrasIt, leoesIt, plantasIt);
void *walls;
int wallsLength = 0;
Modelo* zeb;
Modelo* grassMdl;
Modelo* lion;







void init(void)
{
    //inicializa posição da câmera
    posCameraX = 0.3;
    posCameraY = 0.4;
    posCameraZ = -10;
    //inicializa olhar da câmera
    pitch = 0.0;
    yaw = 0.0;
    walk = -10.0;
    
    g1 = *new Ground(x,y,z,pIlha,pLagos, plantasQtd, zebrasQtd, leoesQtd, zebrasIt, leoesIt, plantasIt);
    g1.generateIsle();
    
    //coisas de openGL
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    
    glEnable(GL_LIGHTING);
    
    //LUZ
    // no m√≠nimo 8 fontes podem ser utilizadas
    //(iniciadas com cor preta)
    // n√∫mero de fontes de luz afeta performance
    
    //LUZ 0
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    float vAmbientLightBright[4] = {0.8, 0.8, 0.8, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, vAmbientLightBright);
    
    GLfloat light0_position[] = { 0.0, g1.sizeY, 0.0, 1.0 };
    GLfloat light0_diffuse[] = { 1.0, 1.0, 0.2, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 0.2, 1.0 };
	//GLfloat light0_ambient[] = { 0.7, 0.2, 0.2, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	
	GLfloat light1_position[] = { g1.sizeX, g1.sizeY, -g1.sizeZ, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light0_specular);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    //glEnable(GL_TEXTURE_2D);
	
    
    
   
    
}

void drawSun() {
	//Desenho do sol
    glPushAttrib (GL_LIGHTING_BIT);
   
	GLfloat mat_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_emission[] = { 1.0, 1.0, 0.0, 1.0 };
          
	//atribui características ao material
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
 
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
    
	glPushMatrix();
	glTranslatef(g1.sizeX, g1.sizeY/2, g1.sizeZ); 
	glScalef(15.0, 15.0, 15.0);
   
	glEnable(GL_LIGHTING);
	// glColor3f (1.0, 1.0, 0.0);
	glutSolidSphere(0.05,50,50);
	glDisable(GL_LIGHTING);
   
	glPopAttrib();
	glPopMatrix();
	
}

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
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    Camera.Render();
    
    //Posicionamento inicial
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    glTranslatef(15.0,-5.0,-(g1.sizeZ)/2);
    glPopMatrix();
    
    //glColor3f (0.7, 0.7, 1.0);
    //glutWireTeapot(0.5);
    //glutWireSphere(0.5,20,20);

    glDisable(GL_TEXTURE_2D);
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
    drawSun();
    g1.drawIsle();
    //z.walk(g1.walls, g1.wallsLength, g1.grasses, g1.grassesLength);
    
    //desenha zebra ------------
    /*
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.1, 1.0);
    glVertex3f(z.posX-0.5, 0.1, z.posY-0.5);
    glVertex3f(z.posX-0.5, 0.1, z.posY+0.5);
    glVertex3f(z.posX+0.5, 0.1, z.posY+0.5);
    glVertex3f(z.posX+0.5, 0.1, z.posY-0.5);
    glEnd();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(z.posX, 0.0, z.posY);
    glRotatef(z.rotation, 0.0, 1.0, 0.0);
    glScalef(0.3,0.3,0.3);
    

    //glColor3f(1.0,0.0,0.0);
    zeb->desenhar();
    glPopMatrix();
    */
    
    //explode zebras e leoes
    for (int i = 0; i < g1.zebrasLength; i++) {
        if (g1.zebras[i].weight >= g1.zebras[i].weightMAX) {

            std::cout << "Zebra explodiu!" << std::endl;
            //explodir em 4 zebras
            if ( g1.zebras[i].weight >= g1.zebras[i].weightMAX + 24) {
                Zebra auxa((g1.zebras[i].posX+1), (g1.zebras[i].posY), 0 ,10);
                g1.zebras.push_back(auxa);
                g1.zebrasLength++;
            }
            if ( g1.zebras[i].weight >= g1.zebras[i].weightMAX + 15) {
                Zebra auxb((g1.zebras[i].posX-1), (g1.zebras[i].posY), 0 ,10);
                g1.zebras.push_back(auxb);
                g1.zebrasLength++;
            }
            if ( g1.zebras[i].weight >= g1.zebras[i].weightMAX + 10) {
                Zebra auxc((g1.zebras[i].posX), (g1.zebras[i].posY+1), 0 ,10);
                g1.zebras.push_back(auxc);
                g1.zebrasLength++;
            }
            Zebra auxd((g1.zebras[i].posX), (g1.zebras[i].posY-1), 0 ,10);
            g1.zebras.push_back(auxd);
            g1.zebrasLength++;

            g1.zebras[i].weight = 100;
        }
	
    }
    for (int i = 0; i < g1.lionsLength; i++) {
        
        if (g1.lions[i].weight >= g1.lions[i].weightMAX) {
            std::cout << "Leao explodiu!" << std::endl;
            Zebra aux((g1.lions[i].posX+1), (g1.lions[i].posY), 0 ,15);
            g1.lions.push_back(aux);
            g1.lionsLength++;
            if (g1.lions[i].weight >= (g1.lions[i].weightMAX + 50)){
                Zebra auxi((g1.lions[i].posX), (g1.lions[i].posY+1), 0 ,15);
                g1.lions.push_back(auxi);
                g1.lionsLength++;
            }
        }
    }

    
    
    
    
    for (int i = 0; i < g1.zebrasLength; i++) {
        
        
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            g1.zebras[i].walk(g1.walls, g1.wallsLength, g1.grasses, g1.grassesLength, g1.zebras,g1.zebrasLength, g1.lakes, g1.lakesLength);
            glTranslatef(g1.zebras[i].posX, 0.0, g1.zebras[i].posY);
            glRotatef(g1.zebras[i].rotation, 0.0, 1.0, 0.0);

            glScalef(0.2*g1.zebras[i].weight*0.01,0.2*g1.zebras[i].weight*0.01,0.2*g1.zebras[i].weight*0.01);
            glColor3f(1.0,1.0,1.0);
            glEnable(GL_TEXTURE_2D);
            zeb->desenhar();
            glDisable(GL_TEXTURE_2D);
            g1.zebras[i].starve();
            glPopMatrix();
        

    }
    
    //desenha gramas --------------
    for (int i = 0; i < g1.grassesLength; i++) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(g1.grasses[i].posX, 0.0, g1.grasses[i].posY);
        glScalef(0.2*g1.grasses[i].size*0.001,0.2*g1.grasses[i].size*0.001,0.2*g1.grasses[i].size*0.001);
        glColor3f(0.0,0.5,0.0);
        // glEnable(GL_TEXTURE_2D);
        grassMdl->desenhar();
        //grassMdl->desenharTextura();
        //glDisable(GL_TEXTURE_2D);
        g1.grasses[i].grow();
        glPopMatrix();
    }
    
    
    //denhar leões ---------
    for (int i = 0; i < g1.lionsLength; i++) {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(g1.lions[i].posX, 0.0, g1.lions[i].posY);
        glRotatef(g1.lions[i].rotation, 0.0, 1.0, 0.0);
        g1.lions[i].lionWalk(g1.zebras, g1.zebrasLength, g1.walls, g1.wallsLength, g1.lions,g1.lionsLength, g1.lakes, g1.lakesLength);
        glScalef(0.3*g1.lions[i].weight*0.01,0.3*g1.lions[i].weight*0.01,0.3*g1.lions[i].weight*0.01);
        glColor3f(1.0,1.0,1.0);
        glEnable(GL_TEXTURE_2D);
        lion->desenhar();
        glDisable(GL_TEXTURE_2D);
        g1.lions[i].starve();
        glPopMatrix();
    }
    
    

    
    
    
    

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
    
    //leitura do arquivo de input
    std::ifstream file( "input.txt", std::ios::in );
    if( !file ) std::cerr << "Cant open " << std::endl;
    while( file >> cena >> x >> y >> z >> ilhas >> pIlha >> lagos >> pLagos >> leoes >> leoesQtd >> leoesIt >> zebras >> zebrasQtd >> zebrasIt >> plantas >> plantasQtd >> plantasIt)
    {
    }
    file.close();
    


    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (900, 900);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("CGLand");
    
    init ();
    
    //carrega modelos
    
    zeb = Modelo::carregarObj((char*)"OBJs/ZEBRA.OBJ", "OBJs/ZEBRA.bmp");
    lion = Modelo::carregarObj((char*)"OBJs/PANTHER.OBJ", "OBJs/leao.bmp");
    grassMdl = Modelo::carregarObj((char*)"OBJs/grass.obj",(char*)"OBJs/grass.bmp");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(KeyDown);
    glutReshapeFunc(reshape);
    
    glutMainLoop();

	delete zeb;
	delete grassMdl;
    return 0;
}
