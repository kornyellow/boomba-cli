#pragma once

// Includes

class Entity {
protected:

    double x;
    double y;

    bool is_show;

    WINDOW *window;

public:

    void init(int x, int y, WINDOW *window) {

        this->x = x;
        this->y = y;

        this->is_show = true;

        this->window = window;
    }   

    double getX() {

        return this->x;
    }

    double getY() {

        return this->y;
    }

    WINDOW* getWindow() {

        return this->window;
    }
};