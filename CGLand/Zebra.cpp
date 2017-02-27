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

float dirX = 0.5;
float dirY = 0.5;

Zebra::Zebra(float x, float y, float z) {
    posY = y;
    posX = x;
    posZ = z;
}

float distance(float x, float y, float z, float u, float v, float w) {
    	return sqrt((x-u) * (x-u) + (y-v) * (y-v) + (z-w) * (z-w));
}

void Zebra::walk(Wall walls[], int wallsLength) {
    
    for (int i = 0; i < wallsLength; i++) {
        if ( distance(posX, posY, posZ, walls[i].posX, walls[i].posY, walls[i].posZ) < 1 ) {
            dirX = dirX * -1;
            dirY = dirY * -1;
            std::cout << distance(posX, posY, posZ, walls[i].posX, walls[i].posY, walls[i].posZ);
        }
    }

    posX = posX + 0.1;
    display();
    
}

void Zebra::display() {
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glTranslatef(posX, 0.0, posY);
    glColor3f(1.0,0.0,0.0);
    glutSolidTeapot(0.5);
    glPopMatrix();

    
}
