#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Cactus.h"
#include "../util/termlib.h"

Cactus * newCactus(){

    Cactus * cactus = malloc(sizeof(Cactus));

    return cactus;
}

void destroyCactus(Cactus * cactus){    
    if(cactus){
        free(cactus);
    }
}

void drawCactus(const Cactus * cactus){
    drawSprite(&cactus->sprite);
}

// void drawCactusHere(const Cactus * cactus, const Vec2i * here){
//     drawSprite(&big1);
// }

void tickCactus(Cactus * cactus){

}

// bool collideCactus(Cactus * cactus, Dino * dino){
//     return false;
// }
