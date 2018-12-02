#include <ncurses.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "Engine.h"

// singleton?
Engine * newEngine(int fps){

    Engine * engine = calloc(1, sizeof(Engine));
    engine->fps = fps;

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
 * do everything we need to calculate the next screen
 * 
 * clear the previous screen
 * 
 * draw the next screen
 * 
 * stall until the next frame happens 1/fps seconds from when we checked the time
 */
void loop(Engine * engine){
    int x = 0, y = 0;

    while(!engine->should_close){
        static int fno;
        sleep(1);
        engine->should_close = 1;
    }
}

void init(Engine * engine){
    initscr();
    noecho();
    curs_set(FALSE);
}

void finish(Engine * engine){
    endwin(); // Restore normal terminal behavior
}