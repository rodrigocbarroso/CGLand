//
//  Ground.hpp
//  CGLand
//
//  Created by Rodrigo Cunha on 25/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//



#pragma once
#ifndef Ground_hpp
#define Ground_hpp
#endif /* Ground_hpp */


#include <stdio.h>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#include "Wall.hpp"
#include "Grass.hpp"
#include "Zebra.hpp"
//#include "Lion.hpp"


class Ground {
    
public:
    int sizeX, sizeY, sizeZ; //tamanho da ilha
    int groundP; // porcentagem de chao
    int lakeP;
    int qtGrass, qtZebra, qtLion; //quantidades iniciais de plantas, zebras e leoes
    size_t size = 100;// porcentagem de lago
    std::vector<Wall> walls; //esta matriz contem todas as walls que deverao ser evitadas pelos bixos
    std::vector<Grass> grasses; //contem as gramasss!
    std::vector<Zebra> zebras;
    //std::vector<Lion> lions;
    int grassesLength = 0;
    int zebrasLength = 0;
    int wallsLength = 0; //tamanho real da matriz
    int gridIsle[100][100];
    
    // funcao chamada pelo main() para desenhar a ilha
    
    public:
    Ground(int x, int y, int z, int g, int l, int grass, int zebra, int lion);
    Ground();
    void setParams(int x, int y, int z, int g, int l, int grass, int zebra, int lion);
    void drawPatch(int x, int y, int color);
    void drawIsle();
    void generateIsle();
    void getWalls(); //retorna a matriz de walls
};




