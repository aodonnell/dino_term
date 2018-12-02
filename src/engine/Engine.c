#include <ncurses.h>
#include <stdlib.h>

#include "Engine.h"

static int _the_engine_exists = 0;
static Engine * _the_engine;

// singleton?
Engine * newEngine(int fps){

    if(!_the_engine_exists){
        _the_engine = calloc(1, sizeof(Engine));
        _the_engine_exists = 1;
    }

    _the_engine->fps = fps;

    return _the_engine;
};

void destroy(Engine * engine){
    free(engine);
    _the_engine_exists = 0;
}

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
void run(Engine * engine){
    if(engine != _the_engine){
        printf("The engine you're attempting to run does not match the true engine.\n");
    }

    init();

    while(!engine->should_close){
        static int fno;
        sleep(1);
        engine->should_close = 1;
    }
};

void init(){
    initscr();
    noecho();
    curs_set(FALSE);
}

void finish(){
    endwin(); // Restore normal terminal behavior
}