//
//  Lion.hpp
//  CGLand
//
//  Created by Rodrigo Cunha on 01/03/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#ifndef Lion_hpp
#define Lion_hpp

#include <stdio.h>

#endif /* Lion_hpp */


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

class Lion {
    
    float posX, posY, posZ;
    int weight = 500;
    int weightMAX = 1000;
    int massLoss = 1;
    
public:
    Lion(float x, float y, float z, int massLoss);
    void walk(std::vector<Wall>& walls,int wallsLength); //sera chamada pelo main.
    void display();
    void die();
    void eat();

};
