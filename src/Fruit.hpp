#pragma once

// Includes
#include "Entity.hpp"
#include "KornDraw.hpp"

class Fruit : public Entity {
private:

    // Color
    int fruit_color;

    // Movement
    int move_delay;
    int move_speed;

public:

    Fruit(int x, int y, WINDOW *window) {

        init(x, y, window);

        this->move_delay = 0;
        this->move_speed = 2;
    }

    // Functions
    void update() {

        if(this->move_delay < 0) {

            this->move_delay = this->move_speed;
            this->y --;
        }
        else this->move_delay --;
    }
    void draw() {

        KornDraw::drawCharacter(this->window, (int)this->x, (int)this->y + 1, '@', this->fruit_color);
        KornDraw::drawCharacter(this->window, (int)this->x, (int)this->y + 2, '|', C_GRAY);
    }

    // Colors
    void setFruitColor(int color) {

        this->fruit_color = color;
    }  
    void setColor(int color) {

        this->fruit_color = color;
    }
    int getColor() {

        return this->fruit_color;
    }
};