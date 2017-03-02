//
//  Zebra.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 26/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//


#include "Zebra.hpp"
#include <math.h>
#include <iostream>
#include "carregadorObj.cpp"

float spd = 0.25;
float dirX = 0.1;
float dirY = 0.1;
int dir = 1; //direcao (1 a 4);
Modelo* zeb; //ponteiro para o modelo


Zebra::Zebra(float x, float y, float z, int mL) {
    posY = y;
    posX = x;
    posZ = z;
    massLoss = mL;
    zeb = Modelo::carregarObj("OBJs/ZEBRA.OBJ","OBJs/ZEBRA_Fotor.bmp");
    
}

//distancia entre pontos (considerando x e y)
float distance(float x, float y, float u, float v) {
    float calc = ((x-u) * (x-u) + (y-v) * (y-v));
    if (calc < 0) {
        calc = calc * -1.0;
    }
    return sqrt(calc);
}

//distancia entre pontos, considerando so um eixo;
float distance2 (float x, float u) {
    float calc = ((x-u) * (x-u));
    if (calc < 0) {
        calc = calc * -1.0;
    }
    return sqrt(calc);
}

//walk calcula o movimento e chama a funcao display
void Zebra::walk(std::vector<Wall>& walls, int wallsLength, std::vector<Grass>& grasses, int grassesLength) {
    
    
    
    /*checa colisao com invisible walls (lakes e ocean)
    for (int i = 0; i < wallsLength; i++) {
        if ( distance2(posX,walls[i].posX) < 0.2) {
            //std::cout << distance2(posX,walls[i].posX);
            dirX = -dirX;
        }

        if ( distance2(posY,walls[i].posY) < 0.2) {
            //std::cout << distance2(posY,walls[i].posY);
            dirY = -dirY;
        }
        
    }*/
    
    
    
    //checa colisao com GRAMA;
    for (int i = 0; i < wallsLength; i++) {
        
        if ( distance2(posX,grasses[i].posX) < 0.4) {
            grasses[i].shrink();
            weight = weight + 25; //equivalente a eat()
            break;
        }
        if ( distance2(posY,grasses[i].posY) < 0.3) {
            dirY = dirY * -1;
            grasses[i].shrink();
            weight = weight + 25; //equivalente a eat()
            break;
        }
    }
    
    for (int i = 0; i < wallsLength; i++) {
        
        float dist = distance(posX,posY,walls[i].posX,walls[i].posY);
        std::cout << dist << std::endl;
        std::cout << walls[i].posX << std::endl;
        if ( distance(posX,posY,walls[i].posX,walls[i].posY) < 0.8)
        {
            if (dir <=3 ) {
                dir = dir + 1;
            } else {
                dir = 1;
            }
            
        }
    }
    
    
    //por iteracao perde massa
    weight = weight - massLoss;
    
    //movimento
    switch (dir) {
        case 1:
            posX = posX + spd;
            posY = posY + 0;
            break;
        case 2:
            posX = posX + 0;
            posY = posY + spd;
            break;
        case 3:
            posX = posX + -spd;
            posY = posY + 0;
            break;
        case 4:
            posX = posX + 0;
            posY = posY + -spd;
            break;
        default:
            break;
    }
    

    //exibir
    display();
    
}

void Zebra::display() {
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 30.0 };
    
    //glPushAttrib (GL_LIGHTING);
    
    //atribui caracter√≠sticas ao material
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
    
    //glEnable(GL_LIGHTING);
    
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.3,0.3,0.3);
    glTranslatef(posX, 0.0, posY);
    //glColor3f(1.0,0.0,0.0);
    zeb->desenhar();
    glPopMatrix();
    //glDisable(GL_LIGHTING);
}



