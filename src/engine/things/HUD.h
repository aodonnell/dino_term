#ifndef HUD_H_
#define HUD_H_

#include <ncurses.h>

#include "../util/Geometry.h"

#define HUD_STATE_MAIN_MENU 1
#define HUD_STATE_SCORE 2
#define HUD_STATE_GAME_OVER 4
// #define HUD_STATE_SCORE 8

typedef struct _hud {
    int state;
    int score;
    Vec2i scorePos;
    WINDOW * window; 
} HUD;

HUD * newHUD();

void drawHUD(HUD * hud);

void tickHUD(HUD * hud);

#endif