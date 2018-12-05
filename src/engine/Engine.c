#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Engine.h"
#include "Thing.h"
#include "util/termlib.h"
#include "util/logger.h"

// Vec2i * termSize;

// XXX singleton?
Engine * newEngine(int fps){

    Engine * engine = calloc(1, sizeof(Engine));
    engine->fps = fps;

    // engine->colors = has_colors();

    // start_color();
    // init_pair(1, COLOR_BLUE, COLOR_BLACK);

    return engine;
};

void destroyEngine(Engine * engine){
    free(engine);
}

void start(Engine * engine){

    // Thing * dolphin = newThingFromFile("resources/dolphin.txt");
    // return;

    init(engine);
    loop(engine);
    finish(engine);
};

/* 
 * check the time
 * 
 * do everything we need to calculate the next screen
 * 
 * clear whatever we need to
 * 
 * draw whatever we need to
 * 
 * stall until the next frame happens 1/fps seconds from when we checked the time
 * 
 * refresh
 */
void loop(Engine * engine){

<<<<<<< HEAD
    Thing * sprite = newThingFromFile("resources/dino.txt");
    Thing * ground = newThingFromFile("resources/terrain.txt");

    ground->physics.s.x = 0;
    ground->physics.s.y = 9;
    ground->physics.ds.x = 0;
    ground->physics.ds.y = 0;
    ground->physics.d2s.x = 0;
    ground->physics.d2s.y = 0;
=======
    Thing * dolphin = newThingFromFile("resources/dolphin.txt");
>>>>>>> 201282d0dfbe7639aca1c9e081c0e432b77c2803

    logger("term size: {%d, %d}\n", termSize.x, termSize.y);

    while(!engine->should_close){

        termClear();

<<<<<<< HEAD
        drawThing(ground);
        drawThing(sprite);

        tickf(&sprite->physics);
=======
        drawThing(dolphin);

        tickf(&dolphin->physics);
>>>>>>> 201282d0dfbe7639aca1c9e081c0e432b77c2803

        termRefresh();
        usleep(40000); // Shorter delay between movements

<<<<<<< HEAD
        if(sprite->physics.s.x + 20 >= termSize.x){
=======
        if(dolphin->physics.s.x + 18 >= termSize.x){
>>>>>>> 201282d0dfbe7639aca1c9e081c0e432b77c2803
            engine->should_close = 1;
        }
    }
}

void init(Engine * engine){
    termInit();
}

void finish(Engine * engine){
    termFinish();
}