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
        this->window = newwin(this->window_height, this->window_width, (this->console_height/2) - (this->window_height/2), (this->console_width/2) - (this->window_width/2));

        boardInitialize();
    }

    WINDOW* getWindow() {

        return this->window;
    }
    
    // Board
    void boardInitialize() {

        // Framerate
        intrflush(this->window, true);
        wtimeout(this->window, 20);

        // Initialize Board
        boardClear();
        boardRefresh();
    }
    void boardAddBorder() {

        mvwhline(this->window, 0, 0, '-', this->window_width);
        mvwhline(this->window, this->window_height - 1, 0, '-', this->window_width);

        mvwvline(this->window, 0, 0, '|', this->window_height);
        mvwvline(this->window, 0, this->window_width - 1, '|', this->window_height);

        mvwprintw(this->window, 0, 0, "#");
        mvwprintw(this->window, 0, this->window_width - 1, "#");
        mvwprintw(this->window, this->window_height - 1, 0, "#");
        mvwprintw(this->window, this->window_height - 1, this->window_width - 1, "#");
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