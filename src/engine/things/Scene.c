#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../util/termlib.h"
#include "../util/logger.h"
#include "../util/tools.h"

#include "Scene.h"

Scene * newSceneFromFile(const char * fname){
    Scene * scene = calloc(1, sizeof(Scene));
    FILE * fd = fopen(fname, "r");
    if(!fd){
        logger("file not found: %s\n", fname);
        exit(EXIT_FAILURE);
    }
    fscanf(fd, "%d %d", &scene->size.x, &scene->size.y);    
    getc(fd);
    // getc(fd);
    scene->lines = calloc(scene->size.x, sizeof(char *));
    for(int i = 0; i < scene->size.y; i++){
        // allocate 1 extra byte to store the extra null that lets us cycle through the scene
        scene->lines[i] = calloc(scene->size.x+1, sizeof(char));
        fgets((scene->lines[i]+1), scene->size.x, fd);
        scene->lines[i][0] = '\0';
        strtok(scene->lines[i], "\n");
    }
    fclose(fd);
    scene->terrainSize = termSize.x;
    scene->terrainPosition = scene->size.x - scene->terrainSize;
    scene->terrainEnd = 0;

    scene->obstacles = NULL;


    return scene;
};

void destroyScene(Scene * scene){
    if(scene){
        if(scene->lines){
            for(int i=0; i<scene->size.y; i++){
                if(scene->lines[i]){
                    free(scene->lines[i]);
                }else{
                    break;
                }
            }
        }
        free(scene->lines);
    }
    free(scene);
};

void drawScene(Scene * scene){
    // todo change me to match the cycleScene function
    Vec2i a1 = vec2i(0, scene->size.y); 
   
    if(scene->terrainEnd > scene->terrainPosition){
        for(int i = 0; i < scene->size.y; i++){
            drawLine((scene->lines[i]+scene->terrainPosition), &a1);
            a1.y--;
        }
    }
    else
    {
        Vec2i a2 = vec2i(scene->terrainSize-1-scene->terrainEnd, scene->size.y); 
        for(int i = 0; i < scene->size.y; i++){
            drawLine((scene->lines[i]+scene->terrainPosition), &a1);
            drawLine(scene->lines[i], &a2);
            a1.y--;
            a2.y--;
        }
    }

    drawObstacles(scene);
};

void cycleScene(Scene * scene){
    /* we just change where the start of the scene is
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
    // assert(!scene->lines[0][scene->terrainEnd]);

    if(scene->terrainEnd == scene->size.x-1){
        // swap the null with the beginning once the cycle is complete
        for(int i=0; i<scene->size.y; i++){
            dummy = scene->lines[i][0];
            scene->lines[i][0] = scene->lines[i][scene->terrainEnd-1];
            scene->lines[i][scene->terrainEnd-1] = dummy;
        }
    }
    else{
        for(int i=0; i<scene->size.y; i++){
            dummy = scene->lines[i][scene->terrainEnd];
            scene->lines[i][scene->terrainEnd] = scene->lines[i][scene->terrainEnd+1];
            scene->lines[i][scene->terrainEnd+1] = dummy;
        }
    }
    scene->terrainPosition=(scene->terrainPosition+1)%(scene->size.x);
    scene->terrainEnd=(scene->terrainEnd+1)%(scene->size.x);
}

void tickScene(Scene * scene){
    // static int animation_buffer = 0;
    // if(animation_buffer && !(animation_buffer%3)){
    //     cycleScene(scene);
    //     animation_buffer = 0;
    // }
    // else{
    //     animation_buffer++;
    // }

    Obstacles * p = scene->obstacles;
    while(p){
        p->cactus->sprite->position.x--;
        p = p->next;
    }

    if(rand()%25 == 3){
        addObstacle(scene);
    }


    cycleScene(scene);
}

void drawObstacles(Scene * scene){
    cleanObstacles(scene);
    Obstacles * p = scene->obstacles;
    while(p){
        drawCactus(p->cactus);
        p = p->next;
    }
}

int n_obstacles(Obstacles * obstacles){
    Obstacles * p = obstacles;
    int c = 0;
    while(p){
        c++;
        p = p->next;
    }
    return c;
}

void cleanObstacles(Scene * scene){
    Obstacles * p = scene->obstacles;
    while(p && p->cactus->sprite->position.x + p->cactus->sprite->size.x + 1< 0){
        removeObstacle(scene);
        p = p->next;
    }
}


// add obstacles to the end
void addObstacle(Scene * scene){

    // we need to make a new cactus no matter what
    Cactus * cactus = newCactus();
    cactus->sprite->position = (Vec2i){termSize.x - 2*cactus->sprite->size.x, 5 + cactus->sprite->size.y-1};

    // init the list if it is empty
    if(!scene->obstacles){
        scene->obstacles = malloc(sizeof(Obstacles));
        scene->obstacles->cactus = cactus;
        scene->obstacles->next = NULL;
        return;
    }

    Obstacles * p = scene->obstacles;

    // go to the end of the list;
    while(p->next){
        p = p->next;
    }

    p->next = malloc(sizeof(Obstacles));
    p->next->cactus = cactus;
    p->next->next = NULL;

}

// remove obstacle to the front
void removeObstacle(Scene * scene){
    if(!scene->obstacles){
        logger("no more obstacles!\n");
    } else {
        Obstacles * temp = scene->obstacles->next;
        destroyCactus(scene->obstacles->cactus);
        scene->obstacles = temp; 
    }
}