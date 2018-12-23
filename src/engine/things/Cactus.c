#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Cactus.h"
#include "../util/termlib.h"

Cactus * newCactus(){

    Cactus * cactus = malloc(sizeof(Cactus));

    switch(rand() % 4){
        case 0:
            cactus->sprite = malloc(sizeof(BIG_CACTUS_1));
            memcpy(cactus->sprite, &BIG_CACTUS_1, sizeof(BIG_CACTUS_1));
            break;
        case 1:
            cactus->sprite = malloc(sizeof(BIG_CACTUS_2));
            memcpy(cactus->sprite, &BIG_CACTUS_2, sizeof(BIG_CACTUS_2));
            break;
        case 2:
            cactus->sprite = malloc(sizeof(SMALL_CACTUS_1));
            memcpy(cactus->sprite, &SMALL_CACTUS_1, sizeof(SMALL_CACTUS_1));
            break;                        
        case 3:
            cactus->sprite = malloc(sizeof(SMALL_CACTUS_2));
            memcpy(cactus->sprite, &SMALL_CACTUS_2, sizeof(SMALL_CACTUS_2));
            break;
    }

    return cactus;
}

void destroyCactus(Cactus * cactus){    
    if(cactus){
        free(cactus);
    }
}

void drawCactus(const Cactus * cactus){
    drawSprite(cactus->sprite);
}

void tickCactus(Cactus * cactus){
    // rien a faire ici pour maintenant
}

// bool collideCactus(Cactus * cactus, Dino * dino){
//     return false;
// }
