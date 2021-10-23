#pragma once

// Includes

class BoombaBoard {
private:

    WINDOW *window;
    int window_width;
    int window_height;
    int console_width;
    int console_height;

public:

    BoombaBoard(int window_width, int window_height) {

        // Get Console Size
        getmaxyx(stdscr, this->console_height, this->console_width);

        // Window
        this->window_width = window_width;
        this->window_height = window_height;
        this->window = newwin(this->window_height, this->window_width, 2, (this->console_width/2) - (this->window_width/2));

        boardInitialize();
    }

    WINDOW* getWindow() {

        return this->window;
    }
    
    // Board
    void boardInitialize() {

        // Framerate
        wtimeout(this->window, 10);

        // Initialize Board
        boardClear();
        boardRefresh();
    }
    void boardAddBorder() {

        box(this->window, 0, 0);
    }
    void boardClear() {

        wclear(this->window);
        boardAddBorder();
    }
    void boardRefresh() {

        wrefresh(this->window);
    }

    // Input
    chtype getInput() {

        return wgetch(this->window);
    }
};