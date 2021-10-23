#pragma once

// Includes
#include "Entity.hpp"
#include "KornDraw.hpp"

class Fruit : public Entity {
private:

    int fruit_color;

    int move_delay;
    int move_speed;

public:

    Fruit(int x, int y, WINDOW *window) {

        init(x, y, window);

        this->move_delay = 0;
        this->move_speed = 1;
    }

    void setFruitColor(int color) {

        this->fruit_color = color;
    }

    void update() {

        if(this->move_delay < 0) {

            this->move_delay = this->move_speed;
            this->y --;
        }
        else this->move_delay --;
    }

    void draw() {

        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_color));
        KornDraw::drawCharacter(this->window, (int)this->x, (int)this->y + 1, 'O');
        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_color));
        
        KornDraw::drawColorOn(this->window, C_GRAY);
        KornDraw::drawCharacter(this->window, (int)this->x, (int)this->y + 2, '|');
        KornDraw::drawColorOff(this->window, C_GRAY);
    }

    // Colors
    void setColor(int color) {

        this->fruit_color = color;
    }
    int getColor() {

        return this->fruit_color;
    }
};