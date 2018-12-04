#ifndef THING_H_
#define THING_H_

#include "util/Geometry.h"
#include "util/Physics.h"

typedef struct _thing {
    Vec2i size;
    Physics2f physics;
    char ** lines;
} Thing;

Thing * newThing();

Thing * newThingFromFile(const char * fnames);

void destroyThing(Thing * thing);

void drawThing(const Thing * thing);

void drawThingHere(const Thing * thing, const Vec2i * here);

#endif
