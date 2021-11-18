#pragma once

// Includes
#include "Entity.hpp"

class Boomba : public Entity {
private:

    // Fruits
    unsigned short int fruit_first;
    unsigned short int fruit_second;

    std::vector <unsigned short int> color_set;

    // Shooting
    unsigned long int shoot_frame;
    unsigned long int max_scope_frame;
    unsigned long int scope;

public:

    Boomba(unsigned long int x, unsigned long int y, WINDOW *window) {

        this->init(x, y, window);

        // Shooting
        this->max_scope_frame = 0;
        this->shoot_frame = 0;
        this->scope = 0;
    }

    // Fruits Functions
    unsigned short int fruitShoot() {

        unsigned short int shoot_fruit = this->fruit_first;
        this->fruit_first = this->fruit_second;
        this->fruit_second = this->color_set.at(KornRandom::randomIntRange(0, this->color_set.size() - 1));

        this->shoot_frame = 10;

        return shoot_fruit;
    }
    void fruitSwap() {

        this->fruit_first = this->fruit_second + this->fruit_first;
        this->fruit_second = this->fruit_first - this->fruit_second;
        this->fruit_first = this->fruit_first - this->fruit_second;
    }
    void initRandomColor() {

        this->fruit_first = this->color_set.at(KornRandom::randomInt(this->color_set.size() - 1));
        this->fruit_second = this->color_set.at(KornRandom::randomInt(this->color_set.size() - 1));
    }   

    // Colors
    void setColorSet(std::vector <unsigned short int> color_set) {

        this->color_set.clear();
        for(unsigned long int i = 0; i < color_set.size(); i++) {

            this->color_set.push_back(color_set.at(i));
        }
    }

    // Shoot Functions
    void setScope(unsigned long int x) {

        this->scope = x;
    }

    // Functions
    void update(chtype input) {

        if(input == 'D' && this->x - 1 > 0) this->x --;
        if(input == 'C' && (short int)this->x + 7 < this->window->_maxx) this->x ++;

        // Set Color
        bool is_match_first = false;
        bool is_match_second = false;
        for(unsigned long int i = 0; i < this->color_set.size(); i++) {

            if(this->fruit_first == this->color_set.at(i)) is_match_first = true;
            if(this->fruit_second == this->color_set.at(i)) is_match_second = true;
        }
        if(!is_match_first) this->fruit_first = this->color_set.at(KornRandom::randomInt(this->color_set.size() - 1));
        if(!is_match_second) this->fruit_second = this->color_set.at(KornRandom::randomInt(this->color_set.size() - 1));
    }
    void draw() {
        
        // Prepare Player's Strings
        std::vector <std::string> player_icon = {
            " /=O=\\",
            "(\"o|o\")",
        };

        for(unsigned long int i = 0; i < player_icon.size(); i++) {
            
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
        if(this->max_scope_frame > 0) {
            
            this->max_scope_frame --;
            for(unsigned long int i = this->y - 1; i > this->scope; i--) {

                KornDraw::drawCharacter(this->window, this->x + 3, i, '\'', this->fruit_first);
            }
        }
    }
};