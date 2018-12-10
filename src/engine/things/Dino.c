#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/termlib.h"
#include "../util/logger.h"

#include "Dino.h"

int _ground;

Dino * newDino(){
    Dino * dino = calloc(1, sizeof(Dino));
    return dino;
};

// todo hardcode the sprite to avoid files
// it would be cool to load the dino from a file once than store it in a resource header
// like have a loader utility that writes c code to include a sprite.
Dino * newDinoFromFile(const char * fname, int ground){
    Dino * dino = calloc(1, sizeof(Dino));

    FILE * fd = fopen(fname, "r");

    if(!fd){
        logbroke("FILE NOT FOUND\n");
        exit(EXIT_FAILURE);
    }

    logger("opened: %s\n", fname);

    // parse the dimensions of the dino

    // XXX: it would be nicer to calculate it. It would make it way easier to make resources.
    // I guess ideally we wouldn't have to load in from files anyway
    // we'd have all of the resources in a header or something.
    fscanf(fd, "%d %d %d", &dino->size.x, &dino->size.y, &dino->frames);
    
    // get rid of the newlines after the size (HACKS)
    getc(fd);
    getc(fd);

    // initialize the frames
    dino->lines = calloc(dino->frames, sizeof(char **));

    // initialize the lines
    for(int f = 0; f < dino->frames; f++){
        dino->lines[f] = calloc(dino->size.x, sizeof(char *));
        
        for(int i = 0; i < dino->size.y; i++){

            dino->lines[f][i] = calloc(dino->size.x, sizeof(char));

            fgets(dino->lines[f][i], termSize.x, fd);
            // (MORE HACKS)
            strtok(dino->lines[f][i], "\n");

            // logger("Frame %d loaded line: %s\n",f, dino->lines[f][i]);

        }
    }

    // init dummy physics
    dino->physics.s.x = 20;
    dino->physics.s.y = ground + dino->size.y - 1;
    dino->physics.ds.x = 0;
    dino->physics.ds.y = 0;    
    dino->physics.d2s.x = 0;
    dino->physics.d2s.y = 0;

    dino->canJump = 1;

    _ground = ground;

    fclose(fd);
    return dino;
}

void destroyDino(Dino * dino){
    if(dino){
        if(dino->lines){
            for(int i=0; i<dino->frames; i++){
                if(dino->lines[i]){
                    for(int j=0; j<dino->size.y; j++){
                        if(dino->lines[i][j]){
                            free(dino->lines[i][j]);
                        }else{
                            break;
                        }
                    }
                    free(dino->lines[i]);
                }else{
                    break;
                }
            }
        }
        free(dino->lines);
    }
    free(dino);
}

void drawDinoHere(const Dino * dino, const Vec2i * here){
    Vec2i adjust = vec2i((int)dino->physics.s.x, (int)dino->physics.s.y); 
    for(int i = 0; i < dino->size.y; i++){
        drawLine(dino->lines[dino->frame][i], &adjust);
        adjust.y--;
    }
}

void drawDino(const Dino * dino){
    Vec2i adjust = vec2i((int)dino->physics.s.x, (int)dino->physics.s.y); 
    for(int i = 0; i < dino->size.y; i++){
        drawLine(dino->lines[dino->frame][i], &adjust);
        adjust.y--;
    }
}

void tickDino(Dino * dino){

    static int animation_counter;
    
    // if the dino is on the ground, animate the walking cycle
    if(dino->physics.s.y == _ground + dino->size.y - 1){
        if(!(animation_counter%5) && animation_counter){
            cycleAnimationDino(dino);    
            animation_counter = 0;
        }
        else{
            animation_counter++;
        }
    }

    tickPhysicsf(&dino->physics);

    // stop if you hit the ground
    if(dino->physics.s.y < (_ground + dino->size.y - 1)){
        dino->physics.s.y = _ground + dino->size.y - 1;
        dino->physics.d2s.y = 0;
        dino->physics.ds.y = 0;
        dino->canJump = 1;
        cycleAnimationDino(dino);
    }
}

void set_ground(int ground){
    _ground = ground;
}

void jumpDino(Dino * dino){
    if(dino->canJump){
        // logger("Jumping\n");
        dino->frame = 0;
        dino->physics.ds.y=6;
        dino->physics.d2s.y=-.9;
        dino->canJump = 0;
    }
}

void cycleAnimationDino(Dino * dino){
    static int walkCycle = 1;
    if(walkCycle == 1){
        walkCycle = 2;
    }
    else{
        walkCycle = 1;
    }
    dino->frame = walkCycle;
    // logger("switching to frame %d\n", dino->frame);
}