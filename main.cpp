// Define Colors
#define C_WHITE    1
#define C_GRAY     2
#define C_RED      3
#define C_GREEN    4
#define C_YELLOW   5
#define C_MAGENTA  6
#define C_CYAN     7

// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curses.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "src/KornDebug.hpp"
#include "src/KornMath.hpp"
#include "src/KornDraw.hpp"
#include "src/KornRandom.hpp"
#include "src/Position.hpp"
#include "src/BoombaGame.hpp"

int main() {

    // Initialize
    srand(time(NULL));
    initscr();
    raw();
    noecho();
    use_default_colors();
    curs_set(false);

    // Setup Colors
    start_color();
    init_pair(1, 15, COLOR_BLACK);
    init_pair(2,  8, COLOR_BLACK);
    init_pair(3,  9, COLOR_BLACK);
    init_pair(4, 10, COLOR_BLACK);
    init_pair(5, 11, COLOR_BLACK);
    init_pair(6, 13, COLOR_BLACK);
    init_pair(7, 14, COLOR_BLACK);

    // Game Loop
    BoombaGame game;
    while(game.isRunning()) {

        game.processInput();
        game.updateState();
        game.reDraw();
    }

    endwin();
    return EXIT_SUCCESS;
}