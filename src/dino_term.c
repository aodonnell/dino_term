#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "engine/Engine.h"
#include "engine/util/logger.h"

#include "dino_term.h"

int main(int argc, char * argv[]){

    // seed random numbers
    srand(time(NULL));

    setLogfile("./log.txt");

    Engine * engine = newEngine(FPS);
    start(engine);
    destroyEngine(engine);
}