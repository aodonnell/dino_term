#ifndef ENGINE_H_
#define ENGINE_H_

typedef struct _engine {
    int fps;
    int should_close;
} Engine;

Engine * newEngine(int fps);

void destroyEngine(Engine * engine);

void start(Engine * engine);

void loop(Engine * engine);

void init(Engine * engine);

void finish(Engine * engine);

#endif
