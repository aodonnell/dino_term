#include "cowbot.h"

int main(int argc, char * argv[]){

    setLogfile("./log.txt");

    logger("starting\n");
    logger("This log goes to a file.\n");
    logsuccess("something must have went well if you're seeing this!\n");
    logalert("this is an important message so let's make it blue to stand out\n");
    logwarn("this is a warning\n");
    logbroke("broke my legs are broken. Terminating the program!\n");

    Engine * engine = newEngine(FPS);
    // start(engine);
    // destroyEngine(engine);
}