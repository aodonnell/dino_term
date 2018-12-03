#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "Engine.h"
#include "Thing.h"

// XXX singleton?
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
 * clear whatever we need to
 * 
 * draw whatever we need to
 * 
 * stall until the next frame happens 1/fps seconds from when we checked the time
 * 
 * refresh
 */
void loop(Engine * engine){
    int max_x, max_y;
    float x = 0, y = 15.0;
    float dx = .5, dy = 0;
    float ddy = -.5;

    while(!engine->should_close){

        getmaxyx(stdscr, max_y, max_x);

        static int fno;
        if(y < 0){
            dy=-0.85*dy;
        }
        x+=dx; // Advance the ball to the right
        y+=dy;
        dy+=ddy;

        clear();
        mvprintw(max_y - (int)y, (int)x, "--------"); // Print our "ball" at the current xy position 
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