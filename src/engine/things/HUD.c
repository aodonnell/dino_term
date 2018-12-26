#include <ncurses.h>
#include <stdlib.h>

#include "HUD.h"
#include "../util/termlib.h"

HUD * newHUD(){
    HUD * hud = malloc(sizeof(HUD));

    // hud->window = newwin;

    hud->scorePos = (Vec2i) {termSize.x - 15, termSize.y - 1};

    hud->state |= HUD_STATE_SCORE;
    return hud;
}

void drawHUD(HUD * hud){
    // if we drawin the main menu, that's all we drawing
    if(hud->state & HUD_STATE_MAIN_MENU){

    } else {
        if(hud->state & HUD_STATE_SCORE){
            // display score
            mvprintw(termSize.y - hud->scorePos.y, hud->scorePos.x, "SCORE: %d", hud->score); 

        }
        if(hud->state & HUD_STATE_GAME_OVER){
            // display game over screen
        }
    }

}

void tickHUD(HUD * hud){
    hud->score++;
}

