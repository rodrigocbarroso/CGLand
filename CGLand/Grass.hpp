//
//  Grass.hpp
//  CGLand
//
//  Created by Rodrigo Cunha on 28/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#pragma once
#ifndef Grass_hpp
#define Grass_hpp

#include <stdio.h>

#endif /* Grass_hpp */

class Grass{
public:float posX,posY,posZ;
    int growthRate;
    int size = 200;
    int sizeMax = 1000;
    
public:
    Grass(int growthRate);
    void grow(); //chamado por iteracao
    void shrink(); //chamado quando alguem come
    void display();
};


