#include <ncurses.h>
#include <signal.h>
#include <locale.h>

#include "termlib.h"
#include "logger.h"

void adjustTermSize(){
    getmaxyx(stdscr, termSize.y, termSize.x);
}

void termMaxSize(){
    getmaxyx(stdscr, termSize.y, termSize.x);
}

void termInit(){

    setlocale(LC_ALL,"");

    initscr();
    noecho();
    curs_set(FALSE);

    // get the initial termSize
    termMaxSize();
    logger("term size: {%d, %d}\n", termSize.x, termSize.y);

    // register termRefresh as the signal handler for SIGWINCH this doesn't really do what I think it does
    // (it gets called but the window size doesn't change)
    // signal(SIGWINCH, (void *)adjustTermSize);
}

void termFinish(){
    endwin();
}

void termClear(){
    clear();
}

void termRefresh(){
    refresh();
}

// TODO make spaces until you hit the first nonspace transparent
void drawLine(char * line, Vec2i * pos){
    logger("print pos: {%d, %d}\n", pos->x, pos->y);
    mvprintw(termSize.y - (int) pos->y, (int) pos->x, line); 
}

const Vec2i * getTermSize(){
    return &termSize;
};
