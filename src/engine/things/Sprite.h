#ifndef SPRITE_H_
#define SPRITE_H_

#include "../util/Geometry.h"

// "sprite" consists vectors describing its size and poition 
// as well as an ascii string describing what it looks like
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

extern const Sprite DINO_DEAD;

//==========================================================================
// CACTI
//==========================================================================

extern const Sprite BIG_CACTUS_1;

extern const Sprite BIG_CACTUS_2;

extern const Sprite SMALL_CACTUS_1;

extern const Sprite SMALL_CACTUS_2;
       
//==========================================================================

#endif
