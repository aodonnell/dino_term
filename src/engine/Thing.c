#include "Thing.h"

Thing * newThing(){
    Thing * thing = calloc(1, sizeof(Thing));

    return thing;
};

Thing * newThingFromFile(char * fname){
    Thing * thing = calloc(1, sizeof(Thing));

    FILE * fd = fopen(fname, "r");

    // todo


    return thing;
};

void destroyThing(Thing * thing);

void drawThing(Thing * thing);