#pragma once

// Includes
#include "GoombaManager.hpp"
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

    // Goomba
    GoombaManager *goomba_manager;

    // Window
    WINDOW* window;

public:

    BoombaGame() {

        // Board
        this->board = new BoombaBoard(39, 20);
        
        // Window
        this->window = this->board->getWindow();

        // Boomba
        this->boomba = new Boomba(16, 17, this->window);
        
        // Goomba
        this->goomba_manager = new GoombaManager(this->window);
        
        this->goomba_manager->addPath(4 , 2);
        this->goomba_manager->addPath(34, 5);
        this->goomba_manager->addPath(34, 5);
        this->goomba_manager->addPath(4 , 5);
        this->goomba_manager->addPath(4 , 8);
        this->goomba_manager->addPath(34, 8);
        this->goomba_manager->addPath(34, 11);
        this->goomba_manager->addPath(4 , 11);
        this->goomba_manager->addPath(4 , 14);
        this->goomba_manager->addPath(34, 14);
        this->goomba_manager->calculatePath();
        
        this->goomba_manager->spawnGoomba();

        this->is_running = true;
    }
    ~BoombaGame() {

        // Clear Memory
        delete this->board;
        delete this->boomba;
        delete this->goomba_manager;
    }

    void processInput() {
        
        // Get Input
        this->input = this->board->getInput();

        // Close Game
        if(this->input == 'q') this->is_running = false;

        // Shoot Fruit
        if(this->input == 'x') { 

            int fruit_color = this->boomba->fruitShoot();

            Fruit fruit(this->boomba->getX() + 3, this->boomba->getY() - 1, this->window);
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

            // Check If Fruit Collide With Goomba
            for(int j = 0; j < this->goomba_manager->getGoombas().size(); j++) {

                int goomba_progress = this->goomba_manager->getGoombas().at(j)->getProgress();
                Position goomba_position = this->goomba_manager->getGoombas().at(j)->getPosition(goomba_progress);
            
                if((int)this->fruits.at(i).getX() == goomba_position.x && (int)this->fruits.at(i).getY() + 1 == goomba_position.y) {
                       
                    // Get Highest Progress
                    int highest_progress = 0;
                    for(int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

                        int progress = this->goomba_manager->getGoombas().at(k)->getProgress();
                        if(progress > highest_progress) highest_progress = progress;
                    }

                    // Move Progress
                    if(goomba_progress == highest_progress) {

                        goomba_progress ++;
                    }

                    // Move
                    int last_progress = this->goomba_manager->getMaxProgress(goomba_progress);
                    for(int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

                        if(this->goomba_manager->getGoombas().at(k)->getProgress() >= goomba_progress && this->goomba_manager->getGoombas().at(k)->getProgress() < last_progress) {
                            
                            this->goomba_manager->getGoombas().at(k)->moveForward();
                        }
                    }

                    // Insert New One
                    Goomba* goomba = new Goomba(this->window, this->goomba_manager->getPathPoints());
                    goomba->setProgress(goomba_progress);
                    goomba->setPosition(goomba_progress);
                    goomba->setInsertDelay(10);
                    goomba->setColor(this->fruits.at(i).getColor());
                    this->goomba_manager->addGoomba(goomba);

                    // Find Matches
                    int match = 1;
                    int match_color = this->fruits.at(i).getColor();
                    int find_left = 1;
                    int find_right = 1;
                    bool left_found = true;
                    bool right_found = true;

                    while(true) {
                        
                        // Find Left
                        int old_find_left = find_left;
                        if(left_found) {

                            for(int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

                                if(this->goomba_manager->getGoombas().at(k)->getProgress() == goomba_progress - find_left) {

                                    if(this->goomba_manager->getGoombas().at(k)->getColor() == match_color) {

                                        find_left ++;
                                        match ++;
                                        
                                        break;
                                    }
                                    else {

                                        left_found = false;
                                    }
                                }
                            }
                        }
                        if(left_found && old_find_left == find_left) left_found = false;

                        // Find Right
                        int old_find_right = find_right;
                        if(right_found) {

                            for(int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

                                if(this->goomba_manager->getGoombas().at(k)->getProgress() == goomba_progress + find_right) {

                                    if(this->goomba_manager->getGoombas().at(k)->getColor() == match_color) {

                                        find_right ++;
                                        match ++;
                                        
                                        break;
                                    }
                                    else {

                                        right_found = false;
                                    }
                                }
                            }
                        }
                        if(right_found && old_find_right == find_right) right_found = false;

                        if(!left_found && !right_found) break;
                    }   

                    // Destroy Matches
                    if(match >= 3) {

                        for(int k = -find_left + 1; k <= find_right - 1; k++) {

                            for(int l = 0; l < this->goomba_manager->getGoombas().size(); l++) {

                                if(this->goomba_manager->getGoombas().at(l)->getProgress() == goomba_progress + k) {

                                    this->goomba_manager->deleteGoomba(l);
                                    
                                    break;
                                }
                            }
                        }
                    }

                    // Remove Fruit
                    this->fruits.erase(this->fruits.begin() + i);

                    break;
                }
            }
        }

        // Update Goomba
        this->goomba_manager->update();
    }
    void reDraw() {
        
        // Clear Buffer
        this->board->boardClear();

        // Draw Goomba
        this->goomba_manager->draw();

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