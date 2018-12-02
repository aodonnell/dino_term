#include "cowbot.h"

#define FPS 10

int main(int argc, char * argv[]){
    Engine * engine = newEngine(FPS);
    run(engine);
}