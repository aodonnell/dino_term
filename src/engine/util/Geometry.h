#ifndef GEOMETRY_H_
#define GEOMETRY_H_

typedef struct _vec2i {
    int x;
    int y;
} Vec2i;

typedef struct _vec2f {
    float x;
    float y;
} Vec2f;

// constuctors (nondynamic)
Vec2i vec2i(int x, int y);
Vec2f vec2f(float x, float y);

// add
Vec2i vaddi(Vec2i * v1, Vec2i * v2);
Vec2f vaddf(Vec2f * v1, Vec2f * v2);

// accumulate
void vacci(Vec2i * v1, Vec2i * v2);
void vaccf(Vec2f * v1, Vec2f * v2);

#endif
