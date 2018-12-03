#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Geometry.h"

typedef struct _physics2i {
    Vec2i s;
    Vec2i ds;
    Vec2i d2s;
} Physics2i;

typedef struct _physics2f {
    Vec2f s;
    Vec2f ds;
    Vec2f d2s;
} Physics2f;

void ticki(Physics2i * physics);

void tickf(Physics2f * physics);

#endif
