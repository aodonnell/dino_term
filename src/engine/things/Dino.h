#ifndef DINO_H_
#define DINO_H_

#include "../util/Geometry.h"

#include "Sprite.h"

typedef struct _dino {
    // Vec2i size; // TODO size should be drawn from the current frame
    Vec2f s;
    Vec2f ds;
    Vec2f d2s;
    int canJump;
    int total_frames;
    int frame;
    Sprite ** sprites;
} Dino;

Dino * newDino();

// Dino * newDinoFromFile(const char * fnames, int ground);

void destroyDino(Dino * dino);

void drawDino(const Dino * dino);

void drawDinoHere(const Dino * dino, const Vec2i * here);

void tickDino(Dino * dino);

void jumpDino(Dino * dino);

void cycleAnimationDino(Dino * dino);

void syncSprite(Dino * dino);

#endif
