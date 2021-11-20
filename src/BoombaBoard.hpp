#pragma once

// Includes

class BoombaBoard {
private:

    WINDOW *window;
    unsigned long int window_width;
    unsigned long int window_height;
    unsigned long int console_width;
    unsigned long int console_height;

    bool is_blink;
    bool blink;
    char blink_delay;

public:

    BoombaBoard(unsigned long int window_width, unsigned long int window_height) {

        // Blink
        this->is_blink = false;
        this->blink = false;
        this->blink_delay = 0;

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
        wtimeout(this->window, TIMEOUT);

        // Initialize Board
        boardClear();
        boardRefresh();
    }
    void boardAddBorder() {

        if(!this->is_blink) this->blink_delay = 0;
        else {
            
            if(this->blink_delay == 0) {
                
                this->blink = !this->blink;
                this->blink_delay = 60;
            }
            else this->blink_delay --;

            if(this->blink) wattron(this->window, COLOR_PAIR(C_RED));
            if(!this->blink) wattron(this->window, COLOR_PAIR(C_GRAY));
        }

        mvwhline(this->window, 0, 0, '-', this->window_width);
        mvwhline(this->window, this->window_height - 1, 0, '-', this->window_width);

        mvwvline(this->window, 0, 0, '|', this->window_height);
        mvwvline(this->window, 0, this->window_width - 1, '|', this->window_height);

        mvwprintw(this->window, 0, 0, "#");
        mvwprintw(this->window, 0, this->window_width - 1, "#");
        mvwprintw(this->window, this->window_height - 1, 0, "#");
        mvwprintw(this->window, this->window_height - 1, this->window_width - 1, "#");

        wattroff(this->window, COLOR_PAIR(C_RED));
        wattroff(this->window, COLOR_PAIR(C_GRAY));
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

    // Blink
    bool isBlink() {

        return this->is_blink;
    }
    void setIsBlink(bool is_blink) {

        this->is_blink = is_blink;
    }   
};