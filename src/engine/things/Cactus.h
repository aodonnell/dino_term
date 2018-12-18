#ifndef CACTUS_H_
#define CACTUS_H_

#include <stdbool.h>

#include "../util/Geometry.h"
#include "../util/Physics.h"
#include "Dino.h"

typedef struct _cactus {
    Vec2i size;
    Physics2f physics;
    char ** lines;
} Cactus;

Cactus * newCactus();

void destroyCactus(Cactus * cactus);

// void drawCactus(const Cactus * cactus);

void drawCactusHere(const Cactus * cactus, const Vec2i * here);

void tickCactus(Cactus * cactus);

bool collideCactus(Cactus * cactus, Dino * dino);

#endif