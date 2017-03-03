//
//  Grass.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 28/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//

#include "Grass.hpp"



Grass::Grass(int gR) {
        growthRate = gR; //com base no input do usuario
}

void Grass::grow() {
    if (size < sizeMax) {
        size = size + growthRate;
    }
    
}

void Grass::shrink() {
    size = 100;
    
}

void Grass::display() {

    
}
