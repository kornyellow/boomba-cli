#pragma once

// Includes
#include "Entity.hpp"

class Particle : public Entity {
private:

    unsigned short int move_delay;
    unsigned short int move_speed;

    short int h_speed;
    short int v_speed; 

    unsigned short int move_frame;
    std::string frame;
    
    unsigned short int color;

public:
    
    Particle(unsigned long int x, unsigned long int y, WINDOW* window) {

        this->init(x, y, window);

        this->move_delay = 0;
        this->move_speed = 0;
        this->move_frame = 0;

        this->h_speed = 0;
        this->v_speed = 0;

        this->color = C_WHITE;
    }

    void update() {

        if(this->is_show && this->move_delay == 0) {

            this->x += this->h_speed;
            this->y += this->v_speed;

            this->move_delay = this->move_speed;
            if(this->move_frame < this->frame.size() - 1) this->move_frame ++;
            else this->is_show = false;

            long x = this->x;
            if(x + this->h_speed > SCREEN_WIDTH - 2 || x + this->h_speed < 0) this->is_show = false;
            long y = this->y;
            if(y + this->v_speed > SCREEN_HEIGHT - 2 || y + this->v_speed < 0) this->is_show = false;
        }
        else this->move_delay --;
    }
    void draw() {

        if(this->is_show) KornDraw::drawCharacter(this->window, this->x, this->y, this->frame.at(this->move_frame), this->color);
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
    short int getHSpeed() {

        return this->h_speed;
    }
    void setHSpeed(short int h_speed) {

        this->h_speed = h_speed;
    }
    short int getVSpeed() {

        return this->v_speed;
    }
    void setVSpeed(short int v_speed) {

        this->v_speed = v_speed;
    }   
    unsigned short int getMoveFrame() {

        return this->move_frame;
    }
    void setMoveFrame(unsigned short int move_frame) {

        this->move_frame = move_frame;
    }
    std::string getFrame() {

        return this->frame;
    }
    void setFrame(std::string frame) {

        this->frame = frame;
    }
    unsigned short int getColor() {

        return this->color;
    }   
    void setColor(unsigned short int color) {

        this->color = color;
    }
};