#ifndef DINO_H_
#define DINO_H_

#include "../util/Geometry.h"
#include "../util/Physics.h"

typedef struct _dino {
    Vec2i size;
    Physics2f physics;
    int canJump;
    char ** lines;
} Dino;

Dino * newDino();

Dino * newDinoFromFile(const char * fnames, int ground);

void destroyDino(Dino * dino);

void drawDino(const Dino * dino);

void drawDinoHere(const Dino * dino, const Vec2i * here);

void tickDino(Dino * dino);

void jumpDino(Dino * dino);

#endif
