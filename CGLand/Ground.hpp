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
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif



class Ground {
    
    int sizeX, sizeY, sizeZ; //tamanho da ilha
    int groundP; // porcentagem de chao
    int lakeP; // porcentagem de lago
    
    // funcao chamada pelo main() para desenhar a ilha
    
    public:
    Ground(int x, int y, int z, int g, int l);
    void drawPatch(int x, int y, int color);
    void drawIsle();
    void generateIsle();
    
};




