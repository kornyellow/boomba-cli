// Config
#define SCREEN_WIDTH  49
#define SCREEN_HEIGHT 20

// Define Colors
#define C_RED         1
#define C_YELLOW      2
#define C_GREEN       3
#define C_CYAN        4
#define C_BLUE        5
#define C_MAGENTA     6
#define C_WHITE       7
#define C_LIGHT_GRAY  8
#define C_GRAY        9

// Define Game States
#define GAME_MENU           0
#define GAME_MENU_PLAY      1
#define GAME_MENU_HIGHSCORE 2
#define GAME_RUN            3
#define GAME_END            4
#define GAME_QUIT           5

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
    srand(time(0));
    initscr();
    raw();
    noecho();
    use_default_colors();
    resizeterm(22, 55);
    curs_set(false);

    // Game Loop
    BoombaGame game;
    while(game.isRunning()) {

        game.updateState();
        game.reDraw();
    }

    endwin();
    return EXIT_SUCCESS;
}