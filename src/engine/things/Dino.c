#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/termlib.h"
#include "../util/logger.h"

#include "Sprite.h"
#include "Dino.h"

// FIXME hardcoded ground height
int _ground = 5;

Dino * newDino(){
    Dino * dino = calloc(1, sizeof(Dino));

    dino->frame = 0;
    dino->total_frames = 3;

    dino->sprites = malloc(dino->total_frames*sizeof(Sprite));

    // set the sprites
    dino->sprites[0] = malloc(sizeof(DINO_BASIC));
                       memcpy(dino->sprites[0], &DINO_BASIC, sizeof(DINO_BASIC));
    
    dino->sprites[1] = malloc(sizeof(DINO_RUNNING_1));
                       memcpy(dino->sprites[1], &DINO_RUNNING_1, sizeof(DINO_RUNNING_1));

    dino->sprites[2] = malloc(sizeof(DINO_RUNNING_2));
                       memcpy(dino->sprites[2], &DINO_RUNNING_2, sizeof(DINO_RUNNING_2));


    // initialize the physics
    dino->s.x = 20;
    dino->s.y = _ground + dino->sprites[dino->frame]->size.y - 1;
    dino->ds.x = 0;
    dino->ds.y = 0;    
    dino->d2s.x = 0;
    dino->d2s.y = 0;

    syncSprite(dino);

    dino->canJump = 1;

    return dino;
};

void destroyDino(Dino * dino){
    if(dino){
        if(dino->sprites){
            for(int i=0; i<dino->total_frames; i++){
                if(dino->sprites[i]){
                    free(dino->sprites[i]);
                }else{
                    break;
                }
            }
        }
        free(dino->sprites);
    }
    free(dino);
}

void drawDino(const Dino * dino){

    drawSprite(dino->sprites[dino->frame]);
}

void tickDino(Dino * dino){

    static int animation_counter;
    // if the dino is on the ground, animate the walking cycle
    if(dino->s.y == _ground + dino->sprites[dino->frame]->size.y - 1){
        if(!(animation_counter%5) && animation_counter){
            cycleAnimationDino(dino);    
            animation_counter = 0;
        }
        else{
            animation_counter++;
        }
    }
    logger("hereya\n");

    vaccf(&dino->s, &dino->ds);
    vaccf(&dino->ds, &dino->d2s);

    // stop if you hit the ground
    if(dino->s.y < (_ground + dino->sprites[dino->frame]->size.y - 1)){
        dino->s.y = _ground + dino->sprites[dino->frame]->size.y - 1;
        dino->d2s.y = 0;
        dino->ds.y = 0;
        dino->canJump = 1;
        cycleAnimationDino(dino);
    }

    syncSprite(dino);
}

void set_ground(int ground){
    _ground = ground;
}

void jumpDino(Dino * dino){
    if(dino->canJump){
        dino->frame = 0;
        dino->ds.y=4.7;
        dino->d2s.y=-.55;
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
}

void syncSprite(Dino * dino){
    dino->sprites[dino->frame]->position = (Vec2i){(int)dino->s.x, (int)dino->s.y};
}