#pragma once

// Includes
#include "Entity.hpp"

class Item : public Entity {
private:

    unsigned short int move_delay;
    unsigned short int move_speed;

    float h_speed;
    float v_speed;

    unsigned short int color;
    char icon;

public:
    
    Item(unsigned long int x, unsigned long int y, WINDOW* window) {

        this->init(x, y, window);

        this->move_delay = 0;
        this->move_speed = 0;

        this->h_speed = 0;
        this->v_speed = 0;

        this->color = C_WHITE;
    }

    void update() {

        if(this->is_show && this->move_delay == 0) {

            this->x += this->h_speed;
            this->y += this->v_speed;
            if(this->v_speed < 1) this->v_speed += 0.1;

            this->move_delay = this->move_speed;

            long x = this->x;
            if(x + this->h_speed > SCREEN_WIDTH - 2 || x + this->h_speed < 1) this->h_speed = -this->h_speed;
            long y = this->y;
            if(y + this->v_speed > SCREEN_HEIGHT - 1) this->is_show = false;
            if(y + this->v_speed < 1)  this->y = 1;
        }
        else this->move_delay --;
    }
    void draw() {

        if(this->is_show) KornDraw::drawCharacter(this->window, this->x, this->y, this->icon
        , this->color);
    }

    unsigned short int getMoveDelay() {

        return this->move_delay;
    }
    void setMoveDelay(unsigned short int move_delay) {

        this->move_delay = move_delay;
    }
    unsigned short int getMoveSpeed() {

        return this->move_speed;
    }
    void setMoveSpeed(unsigned short int move_speed) {

        this->move_speed = move_speed;
    }
    float getHSpeed() {

        return this->h_speed;
    }
    void setHSpeed(float h_speed) {

        this->h_speed = h_speed;
    }
    float getVSpeed() {

        return this->v_speed;
    }
    void setVSpeed(float v_speed) {

        this->v_speed = v_speed;
    }   
    unsigned short int getColor() {

        return this->color;
    }   
    void setColor(unsigned short int color) {

        this->color = color;
    }
    char getIcon() {

        return this->icon;
    }
    void setIcon(char icon) {

        this->icon = icon;
    }
};