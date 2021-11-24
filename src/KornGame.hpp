#pragma once

// Config
#define IS_PLAY_MUSIC         false
#define IS_PLAY_SOUND_EFFECT  true

// Define Screen
#define SCREEN_WIDTH   48
#define SCREEN_HEIGHT  20
#define TIMEOUT        10

// Define Sounds
#define MUS_MENU    "resources/music/menu.ogg"
#define MUS_HIGH    "resources/music/highscore.ogg"
#define MUS_GAME_1  "resources/music/game_1.ogg"
#define MUS_GAME_2  "resources/music/game_2.ogg"
#define MUS_GAME_3  "resources/music/game_3.ogg"
#define MUS_GAME_4  "resources/music/game_4.ogg"
#define MUS_GAME_5  "resources/music/game_5.ogg"
#define MUS_GAME_6  "resources/music/game_6.ogg"
#define MUS_TENSE   "resources/music/tense.ogg"
#define MUS_END     "resources/music/end.ogg"

#define SFX_SELECT   "resources/sound_effects/select.wav"
#define SFX_ENTER    "resources/sound_effects/enter.wav"
#define SFX_CHOOSE   "resources/sound_effects/choose.wav"
#define SFX_SHOOT    "resources/sound_effects/shoot.wav"
#define SFX_INSERT   "resources/sound_effects/insert.wav"
#define SFX_BREAK    "resources/sound_effects/break.wav"
#define SFX_EXPLODE  "resources/sound_effects/explode.wav"
#define SFX_CONNECT  "resources/sound_effects/connect.wav"
#define SFX_COLLECT  "resources/sound_effects/collect.wav"
#define SFX_EYE      "resources/sound_effects/eye.wav"
#define SFX_SCORE    "resources/sound_effects/score.wav"
#define SFX_SLOW     "resources/sound_effects/slow.wav"
#define SFX_STOP     "resources/sound_effects/stop.wav"
#define SFX_PAUSE    "resources/sound_effects/pause.wav"
#define SFX_DAMAGE   "resources/sound_effects/damage.wav"
#define SFX_CHOIR    "resources/sound_effects/choir.wav"
#define SFX_BEAM     "resources/sound_effects/beam.wav"
#define SFX_CHARGE   "resources/sound_effects/charge.wav"
 
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
#define GAME_PAUSE           4
#define GAME_END             5
#define GAME_QUIT            6

// Define Items
#define ITEM_EYE        '@'
#define ITEM_SLOW       '+'
#define ITEM_STOP       '!'
#define ITEM_SCORE      '$'
#define ITEM_LIGHTNING  '/'
#define ITEM_BOMB       '&'
#define ITEM_COLLECTOR  '~'

// Define Maps
#define ROAD      0
#define SPIRAL    1

// Define Difficulty
#define EASY        0
#define NORMAL      1
#define HARD        2
#define EXTREMES    3
#define IMPOSSIBLE  4

// Includes
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include <ncurses.h>

#include "KornDebug.hpp"
#include "KornMath.hpp"
#include "KornDraw.hpp"
#include "KornRandom.hpp"
#include "Position.hpp"
#include "Particle.hpp"
#include "BoombaGame.hpp"

namespace KornGame {

    static void gameSetup() {

        srand(time(0));
        initscr();
        raw();
        noecho();
        use_default_colors();
        resizeterm(33, 119);
        curs_set(false);
        mouseinterval(0);
        mousemask(ALL_MOUSE_EVENTS |REPORT_MOUSE_POSITION, NULL);
    }
    static void gameRun() {

        BoombaGame game;
        while(game.isRunning()) game.run();
        endwin();
    }
}