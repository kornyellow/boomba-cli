#pragma once

// Includes

class Entity {
protected:

    float x;
    float y;

    bool is_show;

    WINDOW *window;

public:

    // Initialize Function
    void init(float x, float y, WINDOW *window) {

        this->x = x;
        this->y = y;

        this->is_show = true;

        this->window = window;
    }

    // Accessors
    float getX() {

        return this->x;
    }
    float getY() {

        return this->y;
    }
    void setX(float) {

        this->x = x;
    }
    void setY(float) {

        this->y = y;
    }
    WINDOW* getWindow() {

        return this->window;
    }
    bool isShow() {

        return this->is_show;
    }
    void setShow(bool is_show) {

        this->is_show = is_show;
    }
};