#include <ncurses.h>
#include <signal.h>

#include "termlib.h"

Vec2i termSize;

void termMaxSize(){
    getmaxyx(stdscr, termSize.y, termSize.y);
}

void termInit(){

    initscr();
    noecho();
    curs_set(FALSE);

    // get the initial termSize
    termMaxSize();

    // register termRefresh as the signal handler for SIGWINCH 
    signal(SIGWINCH, (void *)termMaxSize);
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

void drawLine(char * line, void * vec){
    Vec2f * pos = ( Vec2f* ) vec;
    mvprintw(termSize.y - (int) pos->y, (int) pos->x, line); 
}

const Vec2i * getTermSize(){
    return &termSize;
};
