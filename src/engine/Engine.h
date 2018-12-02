#ifndef ENGINE_H_
#define ENGINE_H_

typedef struct engine {
    int fps;
    int should_close;
} Engine;

Engine * newEngine(int fps);

void destroy(Engine * engine);

void run(Engine * engine);

void init();

void finish();

#endif
