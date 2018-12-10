#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
    // getc(fd);
    ground->lines = calloc(ground->size.x, sizeof(char *));
    for(int i = 0; i < ground->size.y; i++){
        // allocate 1 extra byte to store the extra null that lets us cycle through the ground
        ground->lines[i] = calloc(ground->size.x+1, sizeof(char));
        fgets((ground->lines[i]+1), ground->size.x, fd);
        logger("loaded: <%s>", ground->lines[i]+1);
        ground->lines[i][0] = '\0';
        strtok(ground->lines[i], "\n");
    }
    fclose(fd);
    ground->terrainSize = termSize.x;
    ground->terrainPosition = ground->size.x - ground->terrainSize;
    ground->terrainEnd = 0;
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
    Vec2i a1 = vec2i(0, ground->size.y); 
    // logger("c: <%s>\n", c);
   
    if(ground->terrainEnd > ground->terrainPosition){
        for(int i = 0; i < ground->size.y; i++){
            drawLine((ground->lines[i]+ground->terrainPosition), &a1);
            a1.y--;
        }
    }
    else
    {

        Vec2i a2 = vec2i(ground->terrainSize-1-ground->terrainEnd, ground->size.y); 
        // int l1 = strlen(ground->lines[0]+ground->terrainPosition);
        // int l2 = strlen(ground->lines[0]);
        logger("a2.x: <%d>, position: <%d>\n", a2.x, ground->terrainPosition);
        for(int i = 0; i < ground->size.y; i++){
            drawLine((ground->lines[i]+ground->terrainPosition), &a1);
            drawLine(ground->lines[i], &a2);
            a1.y--;
            a2.y--;
        }
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

    // fixme then end should always be null
    // assert(!ground->lines[0][ground->terrainEnd]);

    if(ground->terrainEnd == ground->size.x-1){
        // swap the null with the beginning once the cycle is complete
        for(int i=0; i<ground->size.y; i++){
            dummy = ground->lines[i][0];
            ground->lines[i][0] = ground->lines[i][ground->terrainEnd-1];
            ground->lines[i][ground->terrainEnd-1] = dummy;
        }
    }
    else{
        for(int i=0; i<ground->size.y; i++){
            dummy = ground->lines[i][ground->terrainEnd];
            ground->lines[i][ground->terrainEnd] = ground->lines[i][ground->terrainEnd+1];
            ground->lines[i][ground->terrainEnd+1] = dummy;
        }
    }
    ground->terrainPosition=(ground->terrainPosition+1)%(ground->size.x);
    ground->terrainEnd=(ground->terrainEnd+1)%(ground->size.x);


    // logger("ground: %d, end: %d\n", ground->terrainPosition, ground->terrainEnd);

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