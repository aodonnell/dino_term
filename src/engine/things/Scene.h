#ifndef SCENE_H_
#define SCENE_H_

#include "../util/Geometry.h"

typedef struct _scene {
    Vec2i size; 
    int terrainSize;
    
    int terrainPosition;
    int terrainEnd;
    char ** lines;
} Scene;

Scene * newSceneFromFile(const char * fname);

void destroyScene(Scene * scene);

void drawScene(Scene * scene);

void cycleScene(Scene * scene);

void tickScene(Scene * scene);

#endif
