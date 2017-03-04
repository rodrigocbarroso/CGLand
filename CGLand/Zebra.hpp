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
public:
    float posX, posY, posZ;
    int weight = 500;
    int weightMAX = 1000;
    int massLoss = 1;
    float rotation = 00.0;
    float dirX = 1;
	float dirY = 0;
	int dir = 1; //direcao (1 a 4);
    bool dead = false;
    
public:
    Zebra(float x, float y, float z, int massLoss);
    void walk(std::vector<Wall>& walls,int wallsLength, std::vector<Grass>& grasses, int grassesLength, std::vector<Zebra>& zebras, int zebrasLength); //sera chamada pelo main.
    void lionWalk(std::vector<Zebra>& zebras, int zebrasLength, std::vector<Wall>& walls,int wallsLength, std::vector<Zebra>& lions, int lionsLength );
    void display();
    void die();
    void eat();
};
