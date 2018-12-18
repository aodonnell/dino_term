#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Cactus.h"
#include "../util/termlib.h"

const char * big1 = "\
        __\0\
       │  │  _\0\
       │  │ | |\0\
     _ │  │/ /\0\
    \\ \\│   _/\0\
     \\_   │\0\
       │  │\0\
       │  │\0\
       wWWw\0";

const char * big2 = "\
        __\n\
       │  │\n\
    _  │  │  _\n\
   | |_│  │_| |\n\
    \\__    __/\n\
       │  │\n\
       │  │\n\
       │  │\n\
       wWWw\n\0";

const char * small1 = "\
        _\n\
       │ │\n\
       │ │_n\n\
       │  _/\n\
       │ │\n\
       │ │\n\
       wWw\n\0";

const char * small2 = "\
        _\n\
       │ │  _\n\
       │ │ │ │\n\
     n_│ │ │ │\n\
     \\_  │/ /\n\
       │ │ │\n\
       wWwWw\n\0";

Cactus * newCactus(){

    Cactus * cactus = malloc(sizeof(Cactus));

    return cactus;
}

void destroyCactus(Cactus * cactus){    
    if(cactus){
        free(cactus);
    }
}

// void drawCactus(const Cactus * cactus);

void drawCactusHere(const Cactus * cactus, const Vec2i * here){
    drawRawAlpha(big1, 9, here);
}

void tickCactus(Cactus * cactus){

}

bool collideCactus(Cactus * cactus, Dino * dino){
    return false;
}
