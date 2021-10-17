#pragma once

// Includes
#include "BoombaBoard.hpp"
#include "Boomba.hpp"
#include "Fruit.hpp"

class BoombaGame {
private:

    // Game
    BoombaBoard *board;
    
    bool is_running;
    chtype input;
    
    // Boomba
    Boomba *boomba;
    std::vector <Fruit> fruits;

public:

    BoombaGame() {

        this->board = new BoombaBoard(60, 30);
        this->boomba = new Boomba(27, 26, this->board->getWindow());
        this->is_running = true;
    }

    ~BoombaGame() {

        delete this->boomba;
    }

    void processInput() {
        
        // Get Input
        this->input = this->board->getInput();

        // Close Game
        if(this->input == 'q') this->is_running = false;

        // Shoot Fruit
        if(this->input == 'x') { 

            int fruit_color = this->boomba->fruitShoot();

            Fruit fruit(this->boomba->getX() + 3, this->boomba->getY() - 1, this->board->getWindow());
            fruit.setFruitColor(fruit_color);
            this->fruits.push_back(fruit);
        }

        // Swap Fruit
        if(this->input == 'c') {

            this->boomba->fruitSwap();
        }
    }

    void updateState() {

        // Update Boomba
        this->boomba->update(this->input);

        // Update Fruit
        for(int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).update();
        }
    }

    void reDraw() {
        
        // Clear Buffer
        this->board->boardClear();

        // Draw Fruit
        for(int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).draw();
        }

        // Draw Boomba
        this->boomba->draw();

        // Put Buffer To Console
        this->board->boardRefresh();
    }

    bool isRunning() {

        return this->is_running;
    }
};