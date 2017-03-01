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

float dirX = 0.1;
float dirY = 0.1;

Zebra::Zebra(float x, float y, float z, int mL) {
    posY = y;
    posX = x;
    posZ = z;
    massLoss = mL;
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
    
    //checa colisao com invisible walls (lakes e ocean)
    for (int i = 0; i < wallsLength; i++) {
        if ( distance2(posX,walls[i].posX) < 0.4) {
            std::cout << distance2(posX,walls[i].posX);
            dirX = -dirX;
            
        }
        if ( distance2(posY,walls[i].posY) < 0.4) {
            std::cout << distance2(posY,walls[i].posY);

            dirY = -dirY;
        }

        
    }
    
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
    
    //por iteracao perde massa
    weight = weight - massLoss;
    
    //movimento
    posX = posX + dirX;
    posY = posY + dirY;
    //exibir
    display();
    
}

void Zebra::display() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(posX, 0.0, posY);
    glColor3f(1.0,0.0,0.0);
    glutSolidTeapot(0.2);
    glPopMatrix();
}



