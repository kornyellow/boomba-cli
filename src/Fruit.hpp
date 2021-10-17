#pragma once

// Includes
#include "Entity.hpp"

class Fruit : public Entity {
private:

    int fruit_color;

public:

    Fruit(int x, int y, WINDOW *window) {

        init(x, y, window);
        
        int fruit_color = 1;
    }

    void setFruitColor(int color) {

        this->fruit_color = color;
    }

    void update() {

        if(this->y - 1 > 0) this->y -= 0.2;
    }

    void draw() {

        wattron(this->window, COLOR_PAIR(this->fruit_color));
        mvwprintw(this->window, (int)this->y + 1, (int)this->x, "[]");
        wattroff(this->window, COLOR_PAIR(this->fruit_color));
        
        wattron(this->window, C_GRAY);
        mvwprintw(this->window, (int)this->y + 2, (int)this->x, "\"\"");
        wattroff(this->window, C_GRAY);
    }
};