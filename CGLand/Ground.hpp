//
//  Ground.hpp
//  CGLand
//
//  Created by Rodrigo Cunha on 25/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//




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



class Ground {
    
public:
    int sizeX, sizeY, sizeZ; //tamanho da ilha
    int groundP; // porcentagem de chao
    int lakeP;
    size_t size = 100;// porcentagem de lago
    std::vector<Wall> walls; //esta matriz contem todas as walls que deverao ser evitadas pelos bixos
    int wallsLength = 0; //tamanho real da matriz
    
    // funcao chamada pelo main() para desenhar a ilha
    
    public:
    Ground(int x, int y, int z, int g, int l);
    Ground();
    void setParams(int x, int y, int z, int g, int l);
    void drawPatch(int x, int y, int color);
    void drawIsle();
    void generateIsle();
    void getWalls(); //retorna a matriz de walls
};




