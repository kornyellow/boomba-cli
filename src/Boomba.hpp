#pragma once

// Includes
#include "Entity.hpp"

class Boomba : public Entity {
private:

    int fruit_first;
    int fruit_second;

    int shoot_frame;

public:

    Boomba(int x, int y, WINDOW *window) {

        init(x, y, window);
        
        this->fruit_first = KornRandom::randomIntRange(3, 7);
        this->fruit_second = KornRandom::randomIntRange(3, 7);

        this->shoot_frame = 0;
    }

    int fruitShoot() {

        int shoot_fruit = this->fruit_first;
        this->fruit_first = this->fruit_second;
        this->fruit_second = KornRandom::randomIntRange(3, 7);

        this->shoot_frame = 10;

        return shoot_fruit;
    }

    void fruitSwap() {

        this->fruit_first = this->fruit_second + this->fruit_first;
        this->fruit_second = this->fruit_first - this->fruit_second;
        this->fruit_first = this->fruit_first - this->fruit_second;
    }

    void update(chtype input) {

        if(input == 'D' && this->x - 1 > 0) this->x --;
        if(input == 'C' && this->x + 7 < this->window->_maxx) this->x ++;
    }

    void draw() {
        
        std::vector <std::string> player_icon = {
            " /=O=\\",
            "(\"o|o\")",
        };

        for(int i = 0; i < player_icon.size(); i++) {
            
            KornDraw::drawText(this->window, this->x, this->y + i, player_icon.at(i).c_str());
        }

        KornDraw::drawColorOn(this->window, C_GRAY);
        KornDraw::drawCharacter(this->window, this->x + 1, this->y + 1, '\"');
        KornDraw::drawCharacter(this->window, this->x + 5, this->y + 1, '\"');
        KornDraw::drawColorOff(this->window, C_GRAY);

        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_first));
        KornDraw::drawCharacter(this->window, this->x + 3, this->y, 'O');
        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_first));

        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_second));
        KornDraw::drawCharacter(this->window, this->x + 2, this->y + 1, 'o');
        KornDraw::drawCharacter(this->window, this->x + 4, this->y + 1, 'o');
        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_second));
        
        if(this->shoot_frame > 0) {

            this->shoot_frame --;

            KornDraw::drawCharacter(this->window, this->x + 3, this->y + 1, '-');

            KornDraw::drawCharacter(this->window, this->x + 3, this->y, '|');

            KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_second));
            KornDraw::drawCharacter(this->window, this->x + 2, this->y + 1, '*');
            KornDraw::drawCharacter(this->window, this->x + 4, this->y + 1, '*');
            KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_second));
        }
    }
};