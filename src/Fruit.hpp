#pragma once

// Includes
#include "Entity.hpp"
#include "KornDraw.hpp"

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

        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_color));
        KornDraw::drawCharacter(this->window, (int)this->x, (int)this->y + 1, 'O');
        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_color));
        
        KornDraw::drawColorOn(this->window, C_GRAY);
        KornDraw::drawCharacter(this->window, (int)this->x, (int)this->y + 2, '|');
        KornDraw::drawColorOff(this->window, C_GRAY);
    }
};