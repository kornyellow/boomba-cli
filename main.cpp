#define C_WHITE    COLOR_PAIR(1)
#define C_GRAY     COLOR_PAIR(2)
#define C_RED      COLOR_PAIR(3)
#define C_GREEN    COLOR_PAIR(4)
#define C_YELLOW   COLOR_PAIR(5)
#define C_MAGENTA  COLOR_PAIR(6)
#define C_CYAN     COLOR_PAIR(7)

// Includes
#include <curses.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/BoombaGame.hpp"

int main() {

    initscr();
    raw();
    noecho();
    use_default_colors();
    curs_set(false);

    start_color();

    init_pair(1, 15, COLOR_BLACK);
    init_pair(2,  8, COLOR_BLACK);
    init_pair(3,  9, COLOR_BLACK);
    init_pair(4, 10, COLOR_BLACK);
    init_pair(5, 11, COLOR_BLACK);
    init_pair(6, 13, COLOR_BLACK);
    init_pair(7, 14, COLOR_BLACK);

    BoombaGame game;

    while(game.isRunning()) {

        game.processInput();
        game.updateState();
        game.reDraw();
    }

    endwin();
    
    return 0;    
}