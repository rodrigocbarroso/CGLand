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
    size = size + growthRate;
}

void Grass::shrink() {
    size = size - 25;
}

void Grass::display() {

    
}
