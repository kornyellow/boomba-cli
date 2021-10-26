#pragma once

// Includes

class Entity {
protected:

    int x;
    int y;

    bool is_show;

    WINDOW *window;

public:

    // Initialize Function
    void init(int x, int y, WINDOW *window) {

        this->x = x;
        this->y = y;

        this->is_show = true;

        this->window = window;
    }   

    // Accessors
    int getX() {

        return this->x;
    }
    int getY() {

        return this->y;
    }
    WINDOW* getWindow() {

        return this->window;
    }
};