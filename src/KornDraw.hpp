#pragma once

// Includes

class KornDraw {
public:

    static void drawText(WINDOW* window, int x, int y, std::string text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, x, text.c_str());
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawText(WINDOW* window, int x, int y, const char* text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, x, text);
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawText(WINDOW* window, int x, int y, int text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, x, std::to_string(text).c_str());
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawText(WINDOW* window, int x, int y, unsigned long int text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, x, std::to_string(text).c_str());
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawText(WINDOW* window, int x, int y, float text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, x, std::to_string(text).c_str());
        wattroff(window, COLOR_PAIR(color));
    }

    static void drawTextCenter(WINDOW* window, int y, std::string text, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, (window->_maxx/2) - (text.size()/2) + 1, text.c_str());
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawTextCenter(WINDOW* window, int y, const char* text, int color = C_WHITE) {

        std::string text_string = text;
        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, (window->_maxx/2) - (text_string.size()/2) + 1, text);
        wattroff(window, COLOR_PAIR(color));
    }
    static void drawTextCenter(WINDOW* window, int y, int text, int color = C_WHITE) {

        std::string text_string = std::to_string(text);
        wattron(window, COLOR_PAIR(color));
        mvwprintw(window, y, (window->_maxx/2) - (text_string.size()/2) + 1, text_string.c_str());
        wattroff(window, COLOR_PAIR(color));
    }

    static void drawCharacter(WINDOW* window, int x, int y, chtype character, int color = C_WHITE) {

        wattron(window, COLOR_PAIR(color));
        mvwaddch(window, y, x, character);
        wattroff(window, COLOR_PAIR(color));
    }
};