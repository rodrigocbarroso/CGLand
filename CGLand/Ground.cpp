//
//  Ground.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 25/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include "Ground.hpp"




//Construtor
Ground::Ground(int x, int y, int z, int g, int l) {
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    groundP = g;
    lakeP = l;
    walls.reserve(size);
    gridIsle[x][y];
    
    
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

//chamado uma vez, para criar a matriz de walls
void Ground::generateIsle() {
    //calcula proporcoes da ilha
    //quantidade de ground patches:
    int qtdG = (groundP * (sizeX-2) * (sizeZ-2))/100;
    int qtdL = (lakeP * (sizeX-2) * (sizeZ-2))/100;
    int proportion = qtdG/qtdL;
    //int counter = 0;
    int wallsIndex = 0;
    int i = 0;
    int p = 0;
    // std::vector<Ground*> grounds;
    for (i=0;i<sizeX;i+=(sizeX-1)) {
        for (p=0;p<sizeZ;p++){
            gridIsle[i][p] = 1;
        }
    }
    for (p=0;p<sizeZ;p+=(sizeZ-1)) {
        for (i=1;i<sizeX;i++){
            gridIsle[i][p] = 1;
        }
    }
    
    for (p=1;p<(sizeZ-1);p++){
        for (i=1;i<(sizeX-1);i++){
            gridIsle[i][p] = 0;
        }
    }
    srand(time(NULL)); //gera a seed do rng
    for (i = 0; i < qtdL; i++){
        int x = rand()%sizeX; //coordenada aleatoria x
        int y = rand()%sizeZ; //coordenada aleatoria y
        if (gridIsle[x][y] == 1) {
            i -= 1;
            continue;
        }
        else {
            gridIsle[x][y] = 1; //ocupa a coordenada com um obstaculo
        }
    }
    
    //Posicionar as walls----------------------------------------
    for (p = 0; p < sizeZ; p++) {
        for (int i = 0; i < sizeX; i++) {
            if (gridIsle[i][p] == 1) {
                Wall aux;
                aux.posX = i + 0.5;
                aux.posY = p + 0.5;
                walls.push_back(aux);
                wallsIndex++;
            } else {
                
            }
        }
    }
    wallsLength = wallsIndex;
}

//chamado sempre para desenhar a ilha
void Ground::drawIsle() {
    //calcula proporcoes da ilha
    //quantidade de ground patches:
    //int qtdG = (groundP * (sizeX-2) * (sizeZ-2))/100;
    //int qtdL = (lakeP * (sizeX-2) * (sizeZ-2))/100;
    //int proportion = qtdG/qtdL;
    //int counter = 0;
    
    // std::vector<Ground*> grounds;
    //-----------------------------------------------------------------
    int i = 0;
    int p = 0;
     
    //Desenhar o chao----------------------------------------------
    for (p = 0; p < sizeZ; p++) {
        for (int i = 0; i < sizeX; i++) {
            if (gridIsle[i][p] == 1) {
                drawPatch(i, p, 4); //adiciona lago   
            } else {
                drawPatch(i, p, 1); //adiciona terra
            }
        }
    }
}

void Ground::setParams(int x, int y,int  z, int g,int  l) {
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    groundP = g;
    lakeP = l;
    gridIsle[x][y];
}

