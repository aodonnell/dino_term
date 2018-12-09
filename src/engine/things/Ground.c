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
        fgets((ground->lines[i]+1), ground->size.x, fd);
        ground->lines[i][0] = '\0';
        strtok(ground->lines[i], "\n");
        logger("loaded line: <%s>\n", ground->lines[i]+1);
        logger("stored as: <%s>\n", ground->lines[i]);
    }
    fclose(fd);
    ground->terrainSize = termSize.x;
    ground->cyclePosition = ground->size.x - ground->terrainSize;
    logger("ground size: <%d,%d>, line len: <%d>, terrain size: <%d>\n",ground->size.x,ground->size.y, strlen(ground->lines[0] + ground->cyclePosition), ground->terrainSize);
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
        adjust.x = 0;
        if((ground->cyclePosition + ground->terrainSize) < ground->size.y){
            drawLine((ground->lines[i]+ground->cyclePosition), &adjust);
        }
        else{
            drawLine((ground->lines[i]+ground->cyclePosition), &adjust);
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
     * example: say our screen is 3 chars wide. 
     * S is the pointer to the start when the map is looped
     * C is the cycle pointer that goes through the terrain
     * E is the end of the terrain that is to be rendered
     *     E                 E                 E                 E
     *     v                 v                 v                 v
     * ... 0xxxxxxxx0   >   x0xxxxxxx0   >   xx0xxxxxx0   >   xxx0xxxxx0 ...
     * ... 0xxxxxxxx0   >   x0xxxxxxx0   >   xx0xxxxxx0   >   xxx0xxxxx0 ...
     *     ^     ^          ^      ^         ^        ^       ^  
     *     S     C          S      C         S        C      S=C
     * we need to print C and then S but we only need to print S if the 
     * to cycle we just swap the null with the adjacent character 
     * then move the pointer to the next col
     * (this may not even need to be a function)
     */

    char dummy;

    // if the cycle is at it's end (one before the actual null)
    if(ground->cyclePosition >= (ground->size.x-ground->terrainSize)){
        // swap the null with the beginning
        for(int i=0; i<ground->size.y; i++){
            // logger("before swap; <%c>, <%c>\n", ground->lines[i][0], ground->lines[i][ground->size.x]);
            dummy = ground->lines[i][0];
            ground->lines[i][0] = ground->lines[i][ground->size.x];
            ground->lines[i][ground->size.x] = dummy;
            // logger("after swap; <%c>, <%c>\n", ground->lines[i][0], ground->lines[i][ground->size.x]);
            
        }

        //reset the cycle
        ground->cyclePosition = 1;
        
    }
    else{
        // otherwise swap the null before cycle position with adjacent characters
        for(int i=ground->cyclePosition; i<ground->size.y-1; i++){
            // fixme
            dummy = ground->lines[i][i-1];
            ground->lines[i][i-1] = ground->lines[i][i];
            ground->lines[i][i-1] = dummy;
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