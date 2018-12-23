#ifndef SCENE_H_
#define SCENE_H_

#include "../util/Geometry.h"
#include "Cactus.h"

typedef struct _obstacles {
    struct _obstacles * next;
    Cactus * cactus;
} Obstacles;

typedef struct _scene {
    Vec2i size; 
    int terrainSize;
    int terrainPosition;
    int terrainEnd;
    char ** lines;
    Obstacles * obstacles;
} Scene;

Scene * newSceneFromFile(const char * fname);

void destroyScene(Scene * scene);

void drawScene(Scene * scene);

void cycleScene(Scene * scene);

void tickScene(Scene * scene);

void drawObstacles(Scene * scene);

void cleanObstacles(Scene * scene);

void addObstacle(Scene * scene);

void removeObstacle(Scene * scene);

#endif
