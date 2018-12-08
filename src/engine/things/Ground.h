#ifndef GROUND_H_
#define GROUND_H_


typedef struct _ground {
    Vec2i size;
    char ** lines;
} Ground;

Ground * newGroundFromFile(const char * fname);

void destroyGround(Ground * ground);

void drawGround(Ground * ground);

void cycleGround(Ground * ground);

#endif
