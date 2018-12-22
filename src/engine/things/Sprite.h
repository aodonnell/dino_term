#ifndef SPRITE_H_
#define SPRITE_H_

#include "../util/Geometry.h"

// "sprite" consists of a vector describing its size and an ascii string;
// example: 
typedef struct _sprite {
    const Vec2i size;
    Vec2i position;
    const char * lines;
} Sprite;

//==========================================================================
// DINO
//==========================================================================

extern const int DINO_SPRITES;

extern const Sprite DINO_BASIC;

extern const Sprite DINO_RUNNING_1;

extern const Sprite DINO_RUNNING_2;

//==========================================================================
// CACTI
//==========================================================================

#define BIG_CACTUS_1 (Sprite) {(Vec2i){11,9},(Vec2i){0,0},"\
        __\0\
       │  │  _\0\
       │  │ | |\0\
     _ │  │/ /\0\
    \\ \\│   _/\0\
     \\_   │\0\
       │  │\0\
       │  │\0\
       wWWw\0"}

#define BIG_CACTUS_2 (Sprite) {(Vec2i){12,9},(Vec2i){0,0},"\
        __\0\
       │  │\0\
    _  │  │  _\0\
   | |_│  │_| |\0\
    \\__    __/\0\
       │  │\0\
       │  │\0\
       │  │\0\
       wWWw\0"}

#define SMALL_CACTUS_1 (Sprite) {(Vec2i){5,7},(Vec2i){0,0},"\
        _\n\
       │ │\n\
       │ │_n\n\
       │  _/\n\
       │ │\n\
       │ │\n\
       wWw\n\0"}

#define SMALL_CACTUS_2 (Sprite) {(Vec2i){8,7},(Vec2i){0,0},"\
        _\n\
       │ │  _\n\
       │ │ │ │\n\
     n_│ │ │ │\n\
     \\_  │/ /\n\
       │ │ │\n\
       wWwWw\n\0"}
       
//==========================================================================

#endif
