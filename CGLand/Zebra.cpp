//
//  Zebra.cpp
//  CGLand
//
//  Created by Rodrigo Cunha on 26/02/17.
//  Copyright © 2017 Rodrigo Cunha. All rights reserved.
//


#include "Zebra.hpp"
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>



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
void Zebra::walk(std::vector<Wall>& walls, int wallsLength, std::vector<Grass>& grasses, int grassesLength, std::vector<Zebra> &zebras, int zebrasLength) {
    
    int randDir = rand()%10;
    
    switch (randDir) {
        case 0:
            dirX= 1;
            dirY= 0;
 
            break;
        case 1:
            dirX= 0;
            dirY= 1;

            break;
        case 2:
            dirX= -1;
            dirY= 0;
  
            break;
        case 3:
            dirX= 0;
            dirY= -1;
         
            break;
        case 4:
            dirX= 1;
            dirY= 0;
       
            break;
        case 5:
            dirX= 0;
            dirY= -1;
        
            break;
        case 6:
            dirX= 1;
            dirY= 0;
        
            break;
        case 7:
            dirX= -1;
            dirY= 0;
          
            break;
        case 8:
            dirX= 0;
            dirY= 1;
            
            break;
        case 9:
            dirX= 0;
            dirY= -1;
           
            break;
        case 10:
            dirX= 0;
            dirY= 1;
          
            break;
        default:
            dirX= -1;
            dirY= 0;
          
            break;
    }
    
    
    //colisao com walls
    for (int i = 0; i < wallsLength; i++) {
        //se a proxima posicao esta ocupada
        if (((posX + dirX) == walls[i].posX) && ((posY + dirY) == walls[i].posY)) {
            dirX = 0;
            dirY = 0;
        }
    }
    
    //colisao com ZEBRAS
    for (int i = 0; i < zebrasLength; i++) {
        //se a proxima posicao esta ocupada
        if (((posX + dirX) == zebras[i].posX) && ((posY + dirY) == zebras[i].posY)) {
            dirX = 0;
            dirY = 0;
        }
    }
    
    
    if (dead == false) {
        //gira antes de se mover, se aplicavel.
        if (dirX == 0) {
            if (dirY == 1) {
                rotation = -90.0;
            }
            if (dirY == -1){
                rotation = 90.0;
            }
        } else {
            if (dirX == 1) {
                rotation = 0.0;
            }
            if (dirX == -1){
                rotation = 180.0;
            }
        }
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



    
}


//se a zebra eh uma leao, entao ela anda como um leao
void Zebra::lionWalk(std::vector<Zebra> &zebras, int zebrasLength, std::vector<Wall> &walls, int wallsLength, std::vector<Zebra>& lions, int lionsLength) {
    
    
    int randDir = rand()%10;
    
    switch (randDir) {
        case 0:
            dirX= 1;
            dirY= 0;
            break;
        case 1:
            dirX= 0;
            dirY= 1;
            break;
        case 2:
            dirX= -1;
            dirY= 0;
            break;
        case 3:
            dirX= 0;
            dirY= -1;
            break;
        case 4:
            dirX= 1;
            dirY= 0;
            break;
        case 5:
            dirX= 0;
            dirY= -1;
            break;
        case 6:
            dirX= 1;
            dirY= 0;
            break;
        case 7:
            dirX= -1;
            dirY= 0;
            break;
        case 8:
            dirX= 0;
            dirY= 1;
            break;
        case 9:
            dirX= 0;
            dirY= -1;
            break;
        case 10:
            dirX= 0;
            dirY= 1;
            break;
        default:
            dirX= -1;
            dirY= 0;
            break;
    }
    
    
    //colisao com walls
    for (int i = 0; i < wallsLength; i++) {
        //se a proxima posicao esta ocupada
        if (((posX + dirX) == walls[i].posX) && ((posY + dirY) == walls[i].posY)) {
            dirX = 0;
            dirY = 0;
        }
    }
    
    //colisao com leoes
    for (int i = 0; i < lionsLength; i++) {
        //se a proxima posicao esta ocupada
        if (((posX + dirX) == lions[i].posX) && ((posY + dirY) == lions[i].posY)) {
            dirX = 0;
            dirY = 0;
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
    

    
}







