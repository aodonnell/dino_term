#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/termlib.h"
#include "../util/logger.h"
#include "../util/tools.h"


#include "Ground.h"

Ground * newGroundFromFile(const char * fname){
    Ground * ground = calloc(1, sizeof(Ground));
    FILE * fd = fopen(fname, "r");
    if(!fd){
        logbroke("FILE NOT FOUND\n");
        exit(EXIT_FAILURE);
    }
    logger("opened: %s\n", fname);
    fscanf(fd, "%d %d", &ground->size.x, &ground->size.y);    
    getc(fd);
    getc(fd);
    ground->lines = calloc(ground->size.x, sizeof(char *));
    for(int i = 0; i < ground->size.y; i++){
        // allocate 1 extra byte to store the extra null that lets us cycle through the ground
        ground->lines[i] = calloc(ground->size.x+1, sizeof(char));
        fgets(ground->lines[i]+1, termSize.x, fd);
        ground->lines[i][0] = '\0';
        strtok(ground->lines[i], "\n");
    }
    fclose(fd);

    ground->cyclePosition = 1;
    return ground;
};

void destroyGround(Ground * ground){
    if(ground){
        if(ground->lines){
            for(int i=0; i<ground->size.y; i++){
                if(ground->lines[i]){
                    free(ground->lines[i]);
                }else{
                    break;
                }
            }
        }
        free(ground->lines);
    }
    free(ground);
};

void drawGround(Ground * ground){
    // todo change me to match the cycleGround function
    Vec2i adjust = vec2i(0, ground->size.y); 
    for(int i = 0; i < ground->size.y; i++){
        if(!ground->lines[i][0]){
            logger("complete cycle!\n");
            drawLine(((char *)ground->lines[i]+ground->cyclePosition), &adjust);
        }
        else{
            Vec2i adjust2 = vec2i(adjust.x + ground->cyclePosition, adjust.y);
            drawLine(((char *)ground->lines[i]+ground->cyclePosition), &adjust);
            adjust.x = ground->cyclePosition;
            drawLine(ground->lines[i], &adjust);
        };
        adjust.y--;
    }
};

void cycleGround(Ground * ground){
    /* we just change where the start of the ground is
     * have a column of null characters that rotates with a pointer 
     * then print out each line as two strings, from the start and from the pointer
     * 
     * ... xxxxx0xxx0   >   xxxxxx0xx0   >   xxxxxxx0x0   >   0xxxxxxxx0 ...
     * ... xxxxx0xxx0   >   xxxxxx0xx0   >   xxxxxxx0x0   >   0xxxxxxxx0 ...
     *           ^                 ^                 ^         ^ 
     * 
     * to cycle we just swap the null with the adjacent character 
     * then move the pointer to the next col
     * (this may not even need to be a function)
     */

    logger("cycle ground!\n");

    // if the cycle is at it's end (one before the actual null)
    if(ground->cyclePosition >= (ground->size.x-1)){
        // swap the null with the beginning
        for(int i=0; i<ground->size.y; i++){
            SWAP(ground->lines[i][0], ground->lines[i][ground->size.x]);
        }

        //reset the cycle
        ground->cyclePosition = 1;
        
    }
    else{
        // otherwise swap the null before cycle position with adjacent characters
        for(int i=0; i<ground->size.y; i++){
            if(ground->lines[i][ground->cyclePosition-1]){
                logger("you were wrong!\n");
            }
            SWAP(ground->lines[i][ground->cyclePosition-1], ground->lines[i][ground->cyclePosition]);
        }
        ground->cyclePosition++;
    }
}

void tickGround(Ground * ground){
    // static int animation_buffer = 0;
    // if(animation_buffer && !(animation_buffer%3)){
    //     cycleGround(ground);
    //     animation_buffer = 0;
    // }
    // else{
    //     animation_buffer++;
    // }
    cycleGround(ground);
}