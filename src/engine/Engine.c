#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

// todo ifdef windows
#include "Engine.h"
#include "things/Dino.h"
#include "things/Ground.h"
#include "util/termlib.h"
#include "util/logger.h"

#define GROUND 5

// Vec2i * termSize;

// XXX singleton?
Engine * newEngine(int fps){

    // allocate the engine
    Engine * engine = calloc(1, sizeof(Engine));
    
    // set the frames per second
    engine->fps = fps;

    // set the gameloop
    // engine->gameloop = gameloop;

    // TODO
    // engine->colors = has_colors();
    // start_color();
    // init_pair(1, COLOR_BLUE, COLOR_BLACK);

    return engine;
};

void destroyEngine(Engine * engine){
    free(engine);
}

void start(Engine * engine){

    // Dino * dolphin = newDinoFromFile("resources/dolphin.txt");
    // return;

    init(engine);
    loop(engine);
    finish(engine);
};

/* 
 * check the time
 * 
 * hanle input
 * 
 * do everydino we need to calculate the next screen
 * 
 * clear the current screen
 * 
 * draw whatever we need to
 * 
 * stall until the next frame happens 1/fps seconds from when we checked the time
 * 
 * refresh
 */
void loop(Engine * engine){

    // todo make these global?
    Dino * dino = newDinoFromFile("resources/dinoascii.txt", GROUND);
    Ground * ground = newGroundFromFile("resources/terrain.txt");

    logger("term size: {%d, %d}\n", termSize.x, termSize.y);

    while(!engine->should_close){

        // handle input
        // check to see if the escape char was pushed onto the buffer
        if(getch() == '\033'){
            // skip the '['
            getch();

            // check the key value 
            switch(getch()){
                case 'A':
                    logger("Keypress up\n");
                    break;
                case 'B':
                    logger("Keypress down\n");
                    break;
                case 'C':
                    logger("Keypress right\n");
                    break;
                case 'D':
                    logger("Keypress left\n");
                    break;
                default: 
                    break;
            }
        } 

        termClear();

        drawGround(ground);
        drawDino(dino);

        tickPhysicsf(&dino->physics);
        
        if(dino->physics.s.x + 20 >= termSize.x){
            engine->should_close = 1;
        }

        termRefresh();

        // Shorter delay between movements
        usleep(50000); 

    }
}

void init(Engine * engine){
    termInit();
}

void finish(Engine * engine){
    termFinish();
}