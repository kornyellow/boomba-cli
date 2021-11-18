// Config
#define SCREEN_WIDTH   49
#define SCREEN_HEIGHT  20

// Define Sounds
#define MUS_MENU    "resources/music/menu.ogg"
#define MUS_HIGH    "resources/music/highscore.ogg"
#define MUS_GAME_1  "resources/music/game_1.ogg"
#define MUS_GAME_2  "resources/music/game_2.ogg"
#define MUS_GAME_3  "resources/music/game_3.ogg"
#define MUS_GAME_4  "resources/music/game_4.ogg"
#define MUS_GAME_5  "resources/music/game_5.ogg"

#define SFX_SELECT   "resources/sound_effects/select.wav"
#define SFX_ENTER    "resources/sound_effects/enter.wav"
#define SFX_CHOOSE   "resources/sound_effects/choose.wav"
#define SFX_SHOOT    "resources/sound_effects/shoot.wav"
#define SFX_INSERT   "resources/sound_effects/insert.wav"
#define SFX_BREAK    "resources/sound_effects/break.wav"
#define SFX_EXPLODE  "resources/sound_effects/explode.wav"
#define SFX_CONNECT  "resources/sound_effects/connect.wav"

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
#define GAME_MENU            0
#define GAME_MENU_PLAY       1
#define GAME_MENU_HIGHSCORE  2
#define GAME_RUN             3
#define GAME_END             4
#define GAME_QUIT            5

// Define Maps
#define ROAD      0
#define SPIRAL    1
#define STAIRS    2
#define MOUNTAIN  3

// Define Difficulty
#define EASY        0
#define NORMAL      1
#define HARD        2
#define EXTREMES    3
#define IMPOSSIBLE  4

// Includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <ncurses.h>

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