//
//  Zebra.hpp
//  CGLand
//
//  Created by Rodrigo Cunha on 26/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#ifndef Zebra_hpp
#define Zebra_hpp


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
#include <stdio.h>
#include "Wall.hpp"
#include <vector>
#include "Grass.hpp"


#endif /* Zebra_hpp */


class Zebra {
    float posX, posY, posZ;
    int weight = 500;
    int weightMAX = 1000;
    int massLoss = 1;
    
public:
    Zebra(float x, float y, float z, int massLoss);
    void walk(std::vector<Wall>& walls,int wallsLength, std::vector<Grass>& grasses, int grassesLength); //sera chamada pelo main.
    void display();
    void die();
    void eat();
};