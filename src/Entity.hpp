#pragma once

// Includes

class Entity {
protected:

    unsigned long int x;
    unsigned long int y;

    bool is_show;

    WINDOW *window;

public:

    // Initialize Function
    void init(unsigned long int x, unsigned long int y, WINDOW *window) {

        this->x = x;
        this->y = y;

        this->is_show = true;

        this->window = window;
    }

    // Accessors
    unsigned long int getX() {

        return this->x;
    }
    unsigned long int getY() {

        return this->y;
    }
    WINDOW* getWindow() {

        return this->window;
    }
};