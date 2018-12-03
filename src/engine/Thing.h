#ifndef THING_H_
#define THING_H_

#include <stdio.h>
#include <stdlib.h>

#include "util/Geometry.h"
#include "util/Physics.h"

typedef struct _thing {
    Vec2i size;
    Physics2f physics;
    char * lines[];
} Thing;

Thing * newThing();

Thing * newThingFromFile(char * fnames);

void destroyThing(Thing * thing);

void drawThing(Thing * thing);

#endif
