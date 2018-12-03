#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// todo implement dwg tools
#include <ncurses.h>

#include "Thing.h"

Thing * newThing(){
    Thing * thing = calloc(1, sizeof(Thing));

    return thing;
};

// todo handle filenotfound error (need to add some sort of error handling mechanism)
Thing * newThingFromFile(char * fname){
    Thing * thing = calloc(1, sizeof(Thing));

    FILE * fd = fopen(fname, "r");

    if(!fd){
        printf("FILE NOT FOUND\n");
        exit(EXIT_FAILURE);
    }

    // parse the dimensions of the thing
    fscanf(fd, "%d %d", &thing->size.x, &thing->size.y);
    
    // get rid of the newline after the size in preparation for parsing the size
    getc(fd);

    // todo we should add a logfile for debugging
    #ifdef DEBUG
        printf("size: %d %d\n", thing->size.x, thing->size.y);
    #endif

    char s[thing->size.x];

    // initialize the lines

    thing->lines = calloc(thing->size.x, sizeof(char *));

    for(int i = 0; i < thing->size.y; i++){
        thing->lines[i] = calloc(thing->size.x, sizeof(char));

        fgets(thing->lines[i], thing->size.x, fd);
        thing->lines[i][thing->size.x] = '\n';

        // remove trailing newline from fgets
        strtok(thing->lines[i], "\n");
    }

    // init physics
    thing->physics.s.x = 0;
    thing->physics.s.y = 15;    
    thing->physics.ds.x = 0.5;
    thing->physics.ds.y = 0;    
    thing->physics.d2s.x = 0;
    thing->physics.d2s.y = 0-.5;

    float x = 0, y = 15.0;
    float dx = .5, dy = 0;
    float ddy = -.5;

    fclose(fd);
    return thing;
}

void destroyThing(Thing * thing){

}

void drawThing(Thing * thing){

    // in our dwg library we can have max_y and max_x as protected global variables or something
    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);

    for(int i = 0; i < thing->size.y; i++){
        mvprintw(max_y - (int) thing->physics.s.y + i, (int)thing->physics.s.x, thing->lines[i]); 
    }
}