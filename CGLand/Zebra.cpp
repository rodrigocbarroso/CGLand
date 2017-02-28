//
//  Zebra.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 26/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#include "Zebra.hpp"
#include "Ground.hpp"
#include <math.h>
#include <iostream>

float dirX = 0.1;
float dirY = 0.1;

Zebra::Zebra(float x, float y, float z) {
    posY = y;
    posX = x;
    posZ = z;
}

float distance(float x, float y, float u, float v) {
    float calc = ((x-u) * (x-u) + (y-v) * (y-v));
    if (calc < 0) {
        calc = calc * -1.0;
    }
    return sqrt(calc);
}

float distance2 (float x, float u) {
    float calc = ((x-u) * (x-u));
    if (calc < 0) {
        calc = calc * -1.0;
    }
    return sqrt(calc);
}


void Zebra::walk(std::vector<Wall>& walls, int wallsLength) {
    
    for (int i = 0; i < wallsLength; i++) {
        if ( distance2(posX,walls[i].posX) < 0.6) {
            dirX = dirX * -1;
        }
        if ( distance2(posY,walls[i].posY) < 0.7) {
            dirY = dirY * -1;
        }
    }
    posX = posX + dirX;
    posY = posY + dirY;
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
