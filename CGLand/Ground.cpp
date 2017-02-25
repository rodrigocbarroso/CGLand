//
//  Ground.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 25/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include "Ground.hpp"

//Construtor
Ground::Ground(int x, int y, int z, int g, int l) {
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    groundP = g;
    lakeP = l;
}

//Methods

//desenha um pedaco da ilha, aceita variacoes de cor.
void Ground::drawPatch(int x, int y, int color) {
    
    // color = 1 -> green1 2-> green 2 -> 3 : green 3 4: lake?
     glBegin(GL_QUADS);
    if (color == 1) glColor3f(0.0, 1.0, 0.0);
    if (color == 2) glColor3f(0.0, 0.7, 0.0);
    if (color == 3) glColor3f(0.0, 0.85, 0.0);
    if (color == 4) glColor3f(0.0, 0.0, 1.0);
     glVertex3f(x, 0.0, y);
     glVertex3f(x, 0.0, y+1);
     glVertex3f(x+1, 0.0, y+1);
     glVertex3f(x+1, 0.0, y);
     glEnd();
}

void Ground::generateIsle() {
    //calcula proporcoes da ilha
    //quantidade de ground patches:
    int qtdG = (groundP * sizeX * sizeY)/100;
    int qtdL = (lakeP * sizeX * sizeY)/100;
    int proportion = qtdG/qtdL;
    int counter = 0;
    
    for (int i = 0; i < sizeX; i++) {
        for (int u = 0; u < sizeY; u++) {
            if (counter == proportion) {
                drawPatch(i, u, 4); //adiciona lago
                counter = 0; //reseta o proporcionador
            } else {
                drawPatch(i, u, 1); //adiciona terra
            }
            counter++;
        }
    }
}
