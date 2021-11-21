#pragma once

// Includes
#include "Entity.hpp"
#include "KornDraw.hpp"

class Fruit : public Entity {
private:

    // Color
    unsigned short int fruit_color;

    // Movement
    unsigned long int move_delay;
    unsigned long int move_speed;

public:

    Fruit(unsigned long int x, unsigned long int y, WINDOW *window) {

        this->init(x, y, window);

        this->move_delay = 0;
        this->move_speed = 2;
    }

    // Functions
    void update() {

        if(this->move_delay <= 0) {

            this->move_delay = this->move_speed;
            this->y --;
        }
        else this->move_delay --;
    }
    void draw() {

        KornDraw::drawCharacter(this->window, (unsigned long int)this->x, (unsigned long int)this->y + 1, '@', this->fruit_color);
        KornDraw::drawCharacter(this->window, (unsigned long int)this->x, (unsigned long int)this->y + 2, '|', C_GRAY);
    }

    // Speed
    void setMoveSpeed(unsigned long int move_speed) {
        
        this->move_speed = move_speed;
    }
    unsigned long int getMoveSpeed() {

        return this->move_speed;
    }

    // Colors
    void setFruitColor(unsigned short int color) {

        this->fruit_color = color;
    }  
    void setColor(unsigned short int color) {

        this->fruit_color = color;
    }
    unsigned short int getColor() {

        return this->fruit_color;
    }
};