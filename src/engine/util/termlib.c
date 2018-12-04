#include <ncurses.h>
#include <signal.h>

#include "termlib.h"
#include "logger.h"

void adjustTermSize(){
    initscr();
    noecho();
    getmaxyx(stdscr, termSize.y, termSize.x);
}

void termMaxSize(){
    getmaxyx(stdscr, termSize.y, termSize.x);
}

void termInit(){

    initscr();
    noecho();
    curs_set(FALSE);

    // get the initial termSize
    termMaxSize();
    logger("term size: {%d, %d}\n", termSize.x, termSize.y);

    // register termRefresh as the signal handler for SIGWINCH this doesn't really do what we think
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

void drawLine(char * line, Vec2i * pos){
    logger("print pos: {%2.2f, %2.2f}\n", pos->x, pos->y);
    mvprintw(termSize.y - (int) pos->y, (int) pos->x, line); 
}

const Vec2i * getTermSize(){
    return &termSize;
};
