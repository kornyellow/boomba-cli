#pragma once

// Includes
#include "Entity.hpp"
#include "KornDraw.hpp"
#include "KornRandom.hpp"

class Boomba : public Entity {
private:

    int fruit_first;
    int fruit_second;

    int eye_blink;

public:

    Boomba(int x, int y, WINDOW *window) {

        init(x, y, window);
        
        this->fruit_first = KornRandom::randomIntRange(3, 7);
        this->fruit_second = KornRandom::randomIntRange(3, 7);

        this->eye_blink = 0;
    }

    int fruitShoot() {

        int shoot_fruit = this->fruit_first;
        this->fruit_first = this->fruit_second;
        this->fruit_second = KornRandom::randomIntRange(3, 7);

        this->eye_blink = 10;

        return shoot_fruit;
    }

    void fruitSwap() {

        this->fruit_first = this->fruit_second + this->fruit_first;
        this->fruit_second = this->fruit_first - this->fruit_second;
        this->fruit_first = this->fruit_first - this->fruit_second;
    }

    void update(chtype input) {

        if(input == 'D' && this->x - 1 > 0) this->x --;
        if(input == 'C' && this->x + 8 < this->window->_maxx) this->x ++;
    }

    void draw() {
        
        std::vector <std::string> player_icon = {
            "  _[]_  ",
            " |o--o| ",
            "[\"~[]~\"]",
        };

        for(int i = 0; i < player_icon.size(); i++) {
            
            KornDraw::drawText(this->window, this->x, this->y + i, player_icon.at(i).c_str());
        }

        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_first));
        KornDraw::drawText(this->window, this->x + 3, this->y, "[]");
        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_first));
        
        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_second));
        KornDraw::drawText(this->window, this->x + 3, this->y + 2, "[]");
        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_second));

        if(this->eye_blink > 0) {

            this->eye_blink --;

            KornDraw::drawText(this->window, this->x + 3, this->y, "\"\"");

            KornDraw::drawCharacter(this->window, this->x + 2, this->y + 1, 'X');
            KornDraw::drawCharacter(this->window, this->x + 5, this->y + 1, 'X');

            KornDraw::drawColorOn(this->window, COLOR_PAIR(this->fruit_second));
            KornDraw::drawText(this->window, this->x + 3, this->y + 1, "[]");
            KornDraw::drawColorOff(this->window, COLOR_PAIR(this->fruit_second));

            KornDraw::drawText(this->window, this->x + 3, this->y + 2, "**");
        }
    }
};