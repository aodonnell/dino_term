#ifndef CACTUS_H_
#define CACTUS_H_

#include <stdbool.h>

#include "../util/Geometry.h"
#include "Sprite.h"

typedef struct _cactus {
    // the sprite itself provides this functionality
    // Vec2i size;
    // Vec2i position;
    Sprite sprite;
} Cactus;

Cactus * newCactus();

void destroyCactus(Cactus * cactus);

void drawCactus(const Cactus * cactus);

// void drawCactusHere(const Cactus * cactus, const Vec2i * here);

void tickCactus(Cactus * cactus);

#endif