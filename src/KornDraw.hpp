#pragma once

// Includes

class KornDraw {
public:

    static void drawText(WINDOW* window, int x, int y, const char* text) {

        mvwprintw(window, y, x, text);
    }
    static void drawCharacter(WINDOW* window, int x, int y, chtype character) {

        mvwaddch(window, y, x, character);
    }
    static void drawColorOn(WINDOW* window, int color) {

        wattron(window, color);
    }
    static void drawColorOff(WINDOW* window, int color) {

        wattroff(window, color);
    }
};