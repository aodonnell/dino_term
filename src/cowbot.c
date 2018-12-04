#include "cowbot.h"

int main(int argc, char * argv[]){

    setLogfile("./log.txt");

    Engine * engine = newEngine(FPS);
    start(engine);
    destroyEngine(engine);
}