#include "cowbot.h"

int main(int argc, char * argv[]){
    Engine * engine = newEngine(FPS);
    start(engine);
    destroyEngine(engine);
}