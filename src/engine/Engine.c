#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

// todo ifdef windows
#include "Engine.h"
#include "things/Dino.h"
#include "things/Scene.h"
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
    Scene * scene = newSceneFromFile("resources/terrain.txt");

    logger("term size: {%d, %d}\n", termSize.x, termSize.y);

    clock_t frame_clock;
    int delay;

    while(!engine->should_close){

        // check time
        frame_clock = clock();

        // handle input
        // check to see if the escape char was pushed onto the buffer
        if(getch() == '\033'){
            // skip the '['
            getch();

            // check the key value 
            switch(getch()){
                case 'A': // up
                    jumpDino(dino);
                    break;
                case 'B': // down
                    break;
                case 'C': // right
                    break;
                case 'D':
                    break; // left
                default: 
                    break;
            }
        } 

        tickDino(dino);
        tickScene(scene);
        
        termClear();
        // draw everything here
        drawScene(scene);
        drawDino(dino);
        // drawing ends
        termRefresh();

        frame_clock = clock() - frame_clock;

        // delay between movements

        delay = (int)((1/(double)engine->fps - ((double)frame_clock)/CLOCKS_PER_SEC)*1e6);
        // logger("delay: <%d>, time to calc frame: <%2.10f>, spf: <%2.2f>\n", delay, ((double)frame_clock)/CLOCKS_PER_SEC, 1/(double)engine->fps);
        usleep(delay); 

    }
}

void init(Engine * engine){
    termInit();
}

void finish(Engine * engine){
    termFinish();
}