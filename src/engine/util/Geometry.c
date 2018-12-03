#include "Geometry.h"

Vec2i vec2i(int x, int y){
    Vec2i vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

Vec2f _vec2f(float x, float y){
    Vec2f vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

Vec2i vaddi(Vec2i * v1, Vec2i * v2){
    return vec2i(v1->x+v2->x, v1->x+v2->y);
}

Vec2f vaddf(Vec2f * v1, Vec2f * v2){
    return _vec2f(v1->x+v2->x, v1->x+v2->y);
}

void vacci(Vec2i * v1, Vec2i * v2){

}

void vaccf(Vec2f * v1, Vec2f * v2){

}