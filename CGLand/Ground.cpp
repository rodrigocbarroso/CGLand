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
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>



//Construtor
Ground::Ground(int x, int y, int z, int g, int l, int grass, int zebra, int lion, int ZIt, int LIt, int PIt) {
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    groundP = g;
    lakeP = l;
    qtGrass = grass;
    qtLion = lion;
    qtZebra = zebra;
    walls.reserve(size);
    gridIsle[x][y];
    PlantaIt = PIt; //perdas de massa por iteracao
    LeaoIt = LIt;
    ZebraIt = ZIt;
    
    
    
    
    
}

//Methods

//desenha um pedaco da ilha, aceita variacoes de cor.
void Ground::drawPatch(int x, int y, int color) {
    
    // color = 1 -> green1 2-> green 2 -> 3 : green 3 4: lake?
     glBegin(GL_QUADS);
    if (color == 1) glColor3f(0.94, 0.92, 0.62);
    if (color == 2) glColor3f(0.0, 0.7, 0.0);
    if (color == 3) glColor3f(0.1, 0.57, 0.90);
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
    /* Criação do grid com os objetos
     * 0 - Areia
     * 1 - Agua
     * 2 - Planta
     * 3 - Zebra
     * 4 - Leao
     * 5 - Oceano
     * */
    for (i=0;i<sizeX;i+=(sizeX-1)) {
        for (p=0;p<sizeZ;p++){
            gridIsle[i][p] = 5;
        }
    }
    for (p=0;p<sizeZ;p+=(sizeZ-1)) {
        for (i=1;i<sizeX;i++){
            gridIsle[i][p] = 5;
        }
    }
    
    for (p=1;p<(sizeZ-1);p++){
        for (i=1;i<(sizeX-1);i++){
            gridIsle[i][p] = 0;
        }
    }
    srand(time(NULL)); //gera a seed do rng
    for (i = 0; i < qtdL; i++){ //Criacao dos lagos
        int x = rand()%sizeX; //coordenada aleatoria x
        int y = rand()%sizeZ; //coordenada aleatoria y
        if ((gridIsle[x][y] == 1) || (gridIsle[x][y] == 5)) {
            i -= 1;
            continue;
        }
        else {
            gridIsle[x][y] = 1; //ocupa a coordenada com um lago
        }
    }
    
    for (i = 0; i < qtGrass; i++){ //Criacao das plantas
        int x = rand()%sizeX; //coordenada aleatoria x
        int y = rand()%sizeZ; //coordenada aleatoria y
        if ((gridIsle[x][y] == 1) || (gridIsle[x][y] == 5)) {
            i -= 1;
            continue;
        }
        else {
            gridIsle[x][y] = 2; //ocupa a coordenada com uma planta
        }
    }
    
    for (i = 0; i < qtZebra; i++){ //Criacao das zebras
        int x = rand()%sizeX; //coordenada aleatoria x
        int y = rand()%sizeZ; //coordenada aleatoria y
        if ((gridIsle[x][y] == 1) || (gridIsle[x][y] == 2) || (gridIsle[x][y] == 5)) {
            i -= 1;
            continue;
        }
        else {
            gridIsle[x][y] = 3; //ocupa a coordenada com uma zebra
        }
    }
    
    for (i = 0; i < qtLion; i++){ //Criacao dos leoes
        int x = rand()%sizeX; //coordenada aleatoria x
        int y = rand()%sizeZ; //coordenada aleatoria y
        if ((gridIsle[x][y] == 1) || (gridIsle[x][y] == 2) || (gridIsle[x][y] == 3) || (gridIsle[x][y] == 5)) {
            i -= 1;
            continue;
        }
        else {
            gridIsle[x][y] = 4; //ocupa a coordenada com um leao
        }
    }
    
    //Posicionar as walls----------------------------------------
    for (p = 0; p < sizeZ; p++) {
        for (int i = 0; i < sizeX; i++) {
            switch (gridIsle[i][p]) {
                case 1: {
					Wall aux;
					aux.posX = i + 0.5;
					aux.posY = p + 0.5;
					walls.push_back(aux);
					wallsIndex++;
					lakes.push_back(aux);
					lakesLength++;
					break;
				}
				case 2: {
					Grass aux(PlantaIt);
					aux.posX = i + 0.5;
					aux.posY = p + 0.5;
					grasses.push_back(aux);
					grassesLength++;
					break;
				}
				case 3: {
					Zebra aux((i+0.5), (p+0.5), 0 ,ZebraIt);
					zebras.push_back(aux);
					zebrasLength++;
                    break;
				}
                case 4: {
                    Zebra aux((i+0.5), (p+0.5), 0 ,LeaoIt);
                    lions.push_back(aux);
                    lionsLength++;
                    break;
                }
                case 5: {
					Wall aux;
					aux.posX = i + 0.5;
					aux.posY = p + 0.5;
					walls.push_back(aux);
					wallsIndex++;
					break;
				}
			}
        }
    }
    wallsLength = wallsIndex;
    
    //Posicionar GRAMASS
    Grass test(10);
    test.posX = 12;
    test.posY = 12;
    grasses.push_back(test);
    
}

void drawGrass(int i, int p) {

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
            } else if (gridIsle[i][p] == 5) { 
				drawPatch(i, p, 3); //adiciona oceano   
			}
            else {
                drawPatch(i, p, 1); //adiciona terra
            }
        }
    }

}

void Ground::setParams(int x, int y,int  z, int g,int  l, int grass, int zebra, int lion) {
    sizeX = x;
    sizeY = y;
    sizeZ = z;
    groundP = g;
    lakeP = l;
    qtGrass = grass;
    qtLion = lion;
    qtZebra = zebra;
    gridIsle[x][y];
}


