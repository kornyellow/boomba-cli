#pragma once

// Includes

class KornDraw {
public:

    static void drawText(WINDOW* window, int x, int y, const char* text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, x, text);
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawCharacter(WINDOW* window, int x, int y, chtype character, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwaddch(window, y, x, character);
        wattroff(window, COLOR_PAIR(color));
    }
};