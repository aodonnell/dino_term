#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/termlib.h"
#include "../util/logger.h"

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
    ground->lines = calloc(ground->size.x, sizeof(char *));
    for(int i = 0; i < ground->size.y; i++){
        ground->lines[i] = calloc(ground->size.x, sizeof(char));
        fgets(ground->lines[i], termSize.x, fd);
        strtok(ground->lines[i], "\n");
    }
    fclose(fd);
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
    Vec2i adjust = vec2i(0, ground->size.y); 
    for(int i = 0; i < ground->size.y; i++){
        drawLine(ground->lines[i], &adjust);
        adjust.y--;
    }
};

void cycleGround(Ground * ground){
    /* we just change where the start of the ground is
     * have a column of null characters that rotates with a pointer 
     * then print out each line as two strings, from the start and from the pointer
     * 
     * xxxxx0xxx0   >   xxxxxx0xx0
     * xxxxx0xxx0   >   xxxxxx0xx0
     *       ^                 ^
     * 
     * to cycle we just swap the null with the adjacent character 
     * then move the pointer to the next col
     */
}
