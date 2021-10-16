#pragma once

// Includes
#include <ncurses.h>
#include <string>
#include <vector>

#include "Entity.hpp"
#include "KornRandom.hpp"

class Boomba : public Entity {
private:

    int fruit_first;
    int fruit_second;

public:

    Boomba(int x, int y, WINDOW *window) {

        init(x, y, window);
        
        this->fruit_first = KornRandom::randomIntRange(3, 7);
        this->fruit_second = KornRandom::randomIntRange(3, 7);
    }

    int fruitShoot() {

        int shoot_fruit = this->fruit_first;
        this->fruit_first = this->fruit_second;
        this->fruit_second = KornRandom::randomIntRange(3, 7);

        return shoot_fruit;
    }

    void fruitSwap() {

        this->fruit_first = this->fruit_second + this->fruit_first;
        this->fruit_second = this->fruit_first - this->fruit_second;
        this->fruit_first = this->fruit_first - this->fruit_second;
    }

    void update(chtype input) {

        if(input == 'D' && this->x - 1 > 0) this->x --;
        if(input == 'C' && this->x + 5 < this->window->_maxx) this->x ++;
    }

    void draw() {

        std::vector <std::string> player_icon = {
            " _O_ ",
            "A\"\"\"A",
        };

        for(int i = 0; i < player_icon.size(); i++) {
            mvwprintw(this->window, this->y + i, this->x, player_icon.at(i).c_str());
        }

        
        wattron(this->window, COLOR_PAIR(this->fruit_first));
        mvwprintw(this->window, this->y, this->x + 2, "O");
        wattroff(this->window, COLOR_PAIR(this->fruit_first));

        wattron(this->window, COLOR_PAIR(this->fruit_second));
        mvwprintw(this->window, this->y + 1, this->x + 2, "o");
        wattroff(this->window, COLOR_PAIR(this->fruit_second));

        wattron(this->window, C_GRAY);
        mvwprintw(this->window, this->y + 1, this->x + 1, "\"");
        mvwprintw(this->window, this->y + 1, this->x + 3, "\"");
        wattroff(this->window, C_GRAY);
    }
};