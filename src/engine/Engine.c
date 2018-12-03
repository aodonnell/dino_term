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

    // Thing * gorilla = newThingFromFile("resources/gorilla.txt");
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
    int max_x, max_y;

    Thing * gorilla = newThingFromFile("resources/dolphin.txt");

    while(!engine->should_close){

        getmaxyx(stdscr, max_y, max_x);

        clear();
        // mvprintw(max_y - (int)y, (int)x, "--------"); // Print our "ball" at the current xy position 
        drawThing(gorilla);

        tickf(&gorilla->physics);

        refresh();
        usleep(40000); // Shorter delay between movements

        if(gorilla->physics.s.x + 18 >= max_x){
            engine->should_close = 1;
        }
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