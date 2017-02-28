//
//  Zebra.hpp
//  CGLand
//
//  Created by Rodrigo Cunha on 26/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#ifndef Zebra_hpp
#define Zebra_hpp

#include <stdio.h>
#include "Wall.hpp"
#include <vector>


#endif /* Zebra_hpp */


class Zebra {
    float posX, posY, posZ;
    int weight = 500;
    int weightMAX = 1000;
    int massLoss = 1;
    
public:
    Zebra(float x, float y, float z);
    void walk(std::vector<Wall>& walls,int wallsLength);
    void display();
    void die();
    void eat();
};
