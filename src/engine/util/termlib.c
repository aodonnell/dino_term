#include <ncurses.h>
#include <signal.h>
#include <locale.h>

#include "termlib.h"
#include "logger.h"

void adjustTermSize(){
<<<<<<< HEAD
=======
    initscr();
    noecho();
>>>>>>> 201282d0dfbe7639aca1c9e081c0e432b77c2803
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

<<<<<<< HEAD
    // register termRefresh as the signal handler for SIGWINCH this doesn't really do what I think it does
    // (it gets called but the window size doesn't change)
=======
    // register termRefresh as the signal handler for SIGWINCH this doesn't really do what we think
>>>>>>> 201282d0dfbe7639aca1c9e081c0e432b77c2803
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

<<<<<<< HEAD
// TODO make spaces until you hit the first nonspace transparent
void drawLine(char * line, Vec2i * pos){
    logger("print pos: {%d, %d}\n", pos->x, pos->y);
=======
void drawLine(char * line, Vec2i * pos){
    logger("print pos: {%2.2f, %2.2f}\n", pos->x, pos->y);
>>>>>>> 201282d0dfbe7639aca1c9e081c0e432b77c2803
    mvprintw(termSize.y - (int) pos->y, (int) pos->x, line); 
}

const Vec2i * getTermSize(){
    return &termSize;
};
