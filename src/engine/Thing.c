#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/termlib.h"
#include "util/logger.h"

#include "Thing.h"


Thing * newThing(){
    Thing * thing = calloc(1, sizeof(Thing));

    return thing;
};

// todo handle filenotfound error (need to add some sort of error handling mechanism)
// it would be cool to load the thing from a file once than store it in a resource header
Thing * newThingFromFile(const char * fname){
    Thing * thing = calloc(1, sizeof(Thing));

    FILE * fd = fopen(fname, "r");

    if(!fd){
        logbroke("FILE NOT FOUND\n");
        exit(EXIT_FAILURE);
    }

    logger("opened: %s\n", fname);

    // parse the dimensions of the thing

    // XXX: it would be nicer to calculate it. It would make it way easier to make resources.
    // I guess ideally we wouldn't have to load in from files anyway
    // we'd have all of the resources in a header or something.
    fscanf(fd, "%d %d", &thing->size.x, &thing->size.y);
    
    // get rid of the newline after the size
    getc(fd);

    // initialize the lines

    thing->lines = calloc(thing->size.x, sizeof(char *));

    for(int i = 0; i < thing->size.y; i++){
        thing->lines[i] = calloc(thing->size.x, sizeof(char));

        fgets(thing->lines[i], termSize.x, fd);

        // remove trailing newline from fgets
        strtok(thing->lines[i], "\n");
    }

    // init dummy physics
    thing->physics.s.x = 0;
    thing->physics.s.y = 50;    
    thing->physics.ds.x = 1;
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
    if(thing){
        if(thing->lines){
            for(int i=0; i<thing->size.y; i++){
                if(thing->lines[i]){
                    free(thing->lines[i]);
                }else{
                    break;
                }
            }
        }
        free(thing->lines);
    }
    free(thing);
}

void drawThingHere(const Thing * thing, const Vec2i * here){
    // in our dwg library we can have max_y and max_x as protected global variables or something
    Vec2i adjust = vec2i((int)thing->physics.s.x, (int)thing->physics.s.y); 
    for(int i = 0; i < thing->size.y; i++){
        drawLine(thing->lines[i], &adjust);
        adjust.y--;
    }
}

void drawThing(const Thing * thing){
    // in our dwg library we can have max_y and max_x as protected global variables or something
    Vec2i adjust = vec2i((int)thing->physics.s.x, (int)thing->physics.s.y); 
    for(int i = 0; i < thing->size.y; i++){
        drawLine(thing->lines[i], &adjust);
        adjust.y--;
    }
}