//
//  Zebra.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 26/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//


#include "Zebra.hpp"
#include <math.h>
#include <iostream>


float spd = 0.25;




Zebra::Zebra(float x, float y, float z, int mL) {
    posY = y;
    posX = x;
    posZ = z;
    massLoss = mL;
	float dirX = 1;
	float dirY = 0;
	int dir = 1; //direcao (1 a 4);
    
}

//distancia entre pontos (considerando x e y)
float distance(float x, float y, float u, float v) {
    float calc = ((x-u) * (x-u) + (y-v) * (y-v));
    if (calc < 0) {
        calc = calc * -1.0;
    }
    return sqrt(calc);
}

//distancia entre pontos, considerando so um eixo;
float distance2 (float x, float u) {
    float calc = ((x-u) * (x-u));
    if (calc < 0) {
        calc = calc * -1.0;
    }
    return sqrt(calc);
}



//walk calcula o movimento e chama a funcao display
void Zebra::walk(std::vector<Wall>& walls, int wallsLength, std::vector<Grass>& grasses, int grassesLength) {
    
    /*checa colisao com invisible walls (lakes e ocean)
    for (int i = 0; i < wallsLength; i++) {
        if ( distance2(posX,walls[i].posX) < 0.2) {
            //std::cout << distance2(posX,walls[i].posX);
            dirX = -dirX;
        }

        if ( distance2(posY,walls[i].posY) < 0.2) {
            //std::cout << distance2(posY,walls[i].posY);
            dirY = -dirY;
        }
        
    }*/
    
    for (int i = 0; i < wallsLength; i++) {
        
        //se a proxima posicao esta ocupada
        if (((posX + dirX) == walls[i].posX) && ((posY + dirY) == walls[i].posY)) {
            /* std::cout << "parede: X ";
            std::cout << walls[i].posX;
            std::cout << " Y : ";
            std::cout << walls[i].posY; */
            if ((dirX == 1) && (dirY == 0)) {
                dirX = 0;
                dirY = 1;
                rotation = 0.0;
            } else if ((dirX == -1) && (dirY == 0)) {
                dirX = 0;
                dirY = -1;
                rotation = 180.0;
            } else if ((dirX == 0) && (dirY == 1)) {
                dirX = -1;
                dirY = 0;
                rotation = -90.0;
            } else if ((dirX == 0) && (dirY == -1)) {
                dirX = 1;
                dirY = 0;
                rotation =  90.0;
            }
        }
    }
    
    if (dead == false) {
        posX = posX + dirX;
        posY = posY + dirY;
        
    }

    /*std::cout << " X: ";
    std::cout << posX;
    std::cout << " Y: ";
    std::cout << posY;
    std::cout << std::endl; */
    
    
    //checa colisao com GRAMA;
    for (int i = 0; i < wallsLength; i++) {
        
        if ((posX == grasses[i].posX) && (posY == grasses[i].posY)) {
            //std::cout << "essa comeu grama";
            grasses[i].shrink();
            if (weight < weightMAX) {
                weight = weight + 25; //equivalente a eat()
            }

            break;
        }
    }
    
    //por iteracao perde massa
    weight = weight - massLoss;
    
    /*/movimento
    switch (dir) {
        case 1:
            posX = posX + spd;
            posY = posY + 0;
            break;
        case 2:
            posX = posX + 0;
            posY = posY + spd;
            break;
        case 3:
            posX = posX + -spd;
            posY = posY + 0;
            break;
        case 4:
            posX = posX + 0;
            posY = posY + -spd;
            break;
        default:
            break;
    }
    */


    
}


//se a zebra eh uma leao, entao ela anda como um leao
void Zebra::lionWalk(std::vector<Zebra> &zebras, int zebrasLength, std::vector<Wall> &walls, int wallsLength) {
    
    
    for (int i = 0; i < wallsLength; i++) {
        
        //se a proxima posicao esta ocupada
        if (((posX + dirX) == walls[i].posX) && ((posY + dirY) == walls[i].posY)) {
            /* std::cout << "parede: X ";
             std::cout << walls[i].posX;
             std::cout << " Y : ";
             std::cout << walls[i].posY; */
            if ((dirX == 1) && (dirY == 0)) {
                dirX = 0;
                dirY = 1;
                rotation = 0.0;
            } else if ((dirX == -1) && (dirY == 0)) {
                dirX = 0;
                dirY = -1;
                rotation = 180.0;
            } else if ((dirX == 0) && (dirY == 1)) {
                dirX = -1;
                dirY = 0;
                rotation = -90.0;
            } else if ((dirX == 0) && (dirY == -1)) {
                dirX = 1;
                dirY = 0;
                rotation =  90.0;
            }
        }
    }
    
    posX = posX + dirX;
    posY = posY + dirY;
    
    
    //checa colisao com ZEBRAS de verdade;
    for (int i = 0; i < zebrasLength; i++) {
        
        if ((posX == zebras[i].posX) && (posY == zebras[i].posY)) {
            //std::cout << "Comeu Zebra";
            zebras[i].dead = true;
            zebras[i].posX = -120;
            zebras[i].posY = -120;
            if (weight < weightMAX) {
                weight = weight + 250; //equivalente a eat()
            }
            break;
        }
    }
    
    //por iteracao perde massa
    weight = weight - massLoss;
    
    /*/movimento
     switch (dir) {
     case 1:
     posX = posX + spd;
     posY = posY + 0;
     break;
     case 2:
     posX = posX + 0;
     posY = posY + spd;
     break;
     case 3:
     posX = posX + -spd;
     posY = posY + 0;
     break;
     case 4:
     posX = posX + 0;
     posY = posY + -spd;
     break;
     default:
     break;
     }
     */
    
}







