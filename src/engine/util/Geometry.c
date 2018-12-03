#include <stdio.h>
#include <string.h>

#include "Geometry.h"

// XXX could all of this duplicated code be fixed with macros?

Vec2i vec2i(int x, int y){
    return (Vec2i) {x, y};
}

Vec2f _vec2f(float x, float y){
    return (Vec2f) {x, y};
}

Vec2i vaddi(Vec2i * v1, Vec2i * v2){
    return vec2i(v1->x+v2->x, v1->x+v2->y);
}

Vec2f vaddf(Vec2f * v1, Vec2f * v2){
    return _vec2f(v1->x+v2->x, v1->x+v2->y);
}

void vacci(Vec2i * v1, Vec2i * v2){
    v1->x += v2->x;
    v1->y += v2->y;
}

void vaccf(Vec2f * v1, Vec2f * v2){
    v1->x += v2->x;
    v1->y += v2->y;
}

// fixme
char * pveci(Vec2i * v, char * s){
    sprintf(s, "{x: %d, y: %d}", v->x, v->y);
    return s;
}

char * pvecf(Vec2f * v, char * s){
    sprintf(s, "{x: %2.2f, y: %2.2f}", v->x, v->y);
    return s;
}