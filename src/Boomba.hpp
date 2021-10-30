#pragma once

// Includes
#include "Entity.hpp"

class Boomba : public Entity {
private:

    // Fruits
    int fruit_first;
    int fruit_second;

    // Shooting
    int shoot_frame;
    int max_scope_frame;
    int scope;

public:

    Boomba(int x, int y, WINDOW *window) {

        init(x, y, window);

        // Fruits
        this->fruit_first = KornRandom::randomIntRange(3, 7);
        this->fruit_second = KornRandom::randomIntRange(3, 7);

        // Shooting
        this->shoot_frame = 0;
        this->scope = 0;
    }

    // Fruits Functions
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

    // Shoot Functions
    void setScope(int x) {

        this->scope = x;
    }

    // Functions
    void update(chtype input) {

        if(input == 'D' && this->x - 1 > 0) this->x --;
        if(input == 'C' && this->x + 7 < this->window->_maxx) this->x ++;
    }
    void draw() {
        
        // Prepare Player's Strings
        std::vector <std::string> player_icon = {
            " /=O=\\",
            "(\"o|o\")",
        };

        for(int i = 0; i < player_icon.size(); i++) {
            
            KornDraw::drawText(this->window, this->x, this->y + i, player_icon.at(i).c_str());
        }

        // Draw Player
        KornDraw::drawCharacter(this->window, this->x + 1, this->y + 1, '\"', C_GRAY);
        KornDraw::drawCharacter(this->window, this->x + 5, this->y + 1, '\"', C_GRAY);

        KornDraw::drawCharacter(this->window, this->x + 3, this->y, '@', this->fruit_first);

        KornDraw::drawCharacter(this->window, this->x + 2, this->y + 1, 'o', this->fruit_second);
        KornDraw::drawCharacter(this->window, this->x + 4, this->y + 1, 'o', this->fruit_second);
        
        if(this->shoot_frame > 0) {

            this->shoot_frame --;

            KornDraw::drawCharacter(this->window, this->x + 3, this->y + 1, '-');

            KornDraw::drawCharacter(this->window, this->x + 3, this->y, '|');

            KornDraw::drawCharacter(this->window, this->x + 2, this->y + 1, '*', this->fruit_second);
            KornDraw::drawCharacter(this->window, this->x + 4, this->y + 1, '*', this->fruit_second);
        }

        // Draw Scope
        KornDraw::drawCharacter(this->window, this->x + 3, this->scope, '^', this->fruit_first);
        if(max_scope_frame > 0) {
            
            max_scope_frame --;
            for(int i = this->y - 1; i > this->scope; i--) {

                KornDraw::drawCharacter(this->window, this->x + 3, i, '\'', this->fruit_first);
            }
        }
    }
};