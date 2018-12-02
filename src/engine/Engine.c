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
    int max_x, max_y;
    float x = 0, y = 25.0;
    float dx = .5, dy = 0;
    float ddy = .3;

    while(!engine->should_close){

        getmaxyx(stdscr, max_y, max_x);

        static int fno;
        if(y>=max_y){
            dy=-0.9*dy;
        }
        x+=dx; // Advance the ball to the right
        y+=dy;
        dy+=ddy;

        clear();
        mvprintw(max_y - (int)y, (int)x, "o"); // Print our "ball" at the current xy position 
        refresh();

        if(x >= max_x){
            engine->should_close = 1;
        }
        usleep(30000); // Shorter delay between movements
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