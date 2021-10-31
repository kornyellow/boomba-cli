#pragma once

// Includes
#include "GoombaManager.hpp"
#include "BoombaBoard.hpp"
#include "BoombaUI.hpp"
#include "Boomba.hpp"
#include "Fruit.hpp"

class BoombaGame {
private:

    // Game
    BoombaBoard *board;
    
    bool is_running;
    chtype input;

    // Boomba UI
    BoombaUI *boomba_ui;
    
    // Boomba
    Boomba *boomba;
    std::vector <Fruit> fruits;
    std::vector <int> color_set;

    // Goomba
    GoombaManager *goomba_manager;

    // Window
    WINDOW* window;

public:

    BoombaGame() {

        // Board
        this->board = new BoombaBoard(49, 20);
        
        // Window
        this->window = this->board->getWindow();

        // Boomba UI
        this->boomba_ui = new BoombaUI();

        // Goomba
        this->goomba_manager = new GoombaManager(this->window);
        
        this->goomba_manager->addPath(8 , 2);
        this->goomba_manager->addPath(40, 2);
        this->goomba_manager->addPath(40, 5);
        this->goomba_manager->addPath(8 , 5);
        this->goomba_manager->addPath(8 , 8);
        this->goomba_manager->addPath(40, 8);
        this->goomba_manager->addPath(40, 11);
        this->goomba_manager->addPath(8 , 11);
        this->goomba_manager->addPath(8 , 14);
        this->goomba_manager->addPath(40, 14);
        this->goomba_manager->calculatePath();

        this->goomba_manager->addGoombaSet("YYYYGGGGGRRRGGGG#");
        this->goomba_manager->addGoombaSet("YYYYGGGGGRRRGGGG#");
        this->goomba_manager->addGoombaSet("YYYYGGGGGRRRGGGG#");
        this->goomba_manager->addGoombaSet("YYYYGGGGGRRRGGGG#");
        
        this->is_running = true;
        this->colorSet("RGY");

        // Boomba
        this->boomba = new Boomba(16, 17, this->window, this->color_set);
    }
    ~BoombaGame() {

        // Clear Memory
        delete this->board;
        delete this->boomba;
        delete this->boomba_ui;
        delete this->goomba_manager;
    }

    // Colors
    void colorSet(std::string color) {

        for(int i = 0; i < color.size(); i++) {

            switch(color.at(i)) {
            
            case 'R' :
                this->color_set.push_back(C_RED);
                break;
            case 'Y' :
                this->color_set.push_back(C_YELLOW);
                break;
            case 'G' :
                this->color_set.push_back(C_GREEN);
                break;
            }
        }
    }

    // Fruit
    void destroyMatch(int goomba_progress, int match_color, bool is_insert = true) {

        // Get Highest Progress
        int highest_progress = 0;
        for(int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

            int progress = this->goomba_manager->getGoombas().at(k)->getProgress();
            if(progress > highest_progress) highest_progress = progress;
        }

        // Move Progress
        goomba_progress ++;

        // Move
        int last_progress = this->goomba_manager->getMaxProgress(goomba_progress);
        for(int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

            if(this->goomba_manager->getGoombas().at(k)->getProgress() >= goomba_progress && this->goomba_manager->getGoombas().at(k)->getProgress() < last_progress) {
                
                this->goomba_manager->getGoombas().at(k)->moveForward();
            }
        }

        // Insert New One
        if(is_insert) {
            Goomba* goomba = new Goomba(this->window, this->goomba_manager->getPathPoints());
            goomba->setProgress(goomba_progress);
            goomba->setPosition(goomba_progress);
            goomba->setInsertDelay(10);
            goomba->setColor(match_color);
            this->goomba_manager->addGoomba(goomba);
        }

        // Find Matches
        int match = 1;
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
    }

    // Functions
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
        if(!this->goomba_manager->getAllColor().empty()) this->boomba->setColorSet(this->goomba_manager->getAllColor());

        // Update Boomba Scope
        int scope = this->boomba->getY();
        while(true) {

            scope --;

            // Check If Scope Hit The Goomba
            bool is_collide = false;
            for(int i = 0; i < this->goomba_manager->getGoombas().size(); i++) {

                int goomba_progress = this->goomba_manager->getGoombas().at(i)->getProgress();
                if(this->boomba->getX() + 3 == this->goomba_manager->getGoombas().at(i)->getPosition(goomba_progress).x && scope == this->goomba_manager->getGoombas().at(i)->getPosition(goomba_progress).y + 1) {
                    
                    is_collide = true;
                    break;
                }
            }
            if(is_collide || scope <= 1) break;
        }
        this->boomba->setScope(scope);

        // Update Boomba UI
        this->boomba_ui->update(this->input);

        // Update Fruit
        for(int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).update();

            // Check If Fruit Collide With Goomba
            for(int j = 0; j < this->goomba_manager->getGoombas().size(); j++) {

                int goomba_progress = this->goomba_manager->getGoombas().at(j)->getProgress();
                Position goomba_position = this->goomba_manager->getGoombas().at(j)->getPosition(goomba_progress);
            
                if((int)this->fruits.at(i).getX() == goomba_position.x && (int)this->fruits.at(i).getY() + 1 == goomba_position.y) {
                       
                    // Destroy Match
                    this->destroyMatch(goomba_progress, this->fruits.at(i).getColor());

                    // Remove Fruit
                    this->fruits.erase(this->fruits.begin() + i);

                    break;
                }
            }
        }

        // Update Collided Goombas
        for(int i = 0; i < this->goomba_manager->getGoombas().size(); i++) {

            if(!this->goomba_manager->getGoombas().at(i)->getFoundMatch()) continue;

            // Check If Not Leader
            bool is_leader = true;
            int goomba_progress = this->goomba_manager->getGoombas().at(i)->getProgress();
            for(int j = 0; j < this->goomba_manager->getGoombas().size(); j++) {

                if(this->goomba_manager->getGoombas().at(j)->getProgress() == goomba_progress - 1) {

                    is_leader = false;
                    break;
                }
            }
            if(is_leader) continue;

            // Remove Match
            this->destroyMatch(this->goomba_manager->getGoombas().at(i)->getProgress(), this->goomba_manager->getGoombas().at(i)->getColor(), false);

            break;
        }

        // Update Goomba
        this->goomba_manager->update();
    }
    void reDraw() {
        
        // Clear Buffer
        this->board->boardClear();

        // Draw UI
        this->boomba_ui->draw();

        // Draw Goomba
        this->goomba_manager->draw();

        // Draw Boomba
        this->boomba->draw();

        // Draw Fruit
        for(int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).draw();
        }

        // Put Buffer To Console
        this->board->boardRefresh();
    }
    bool isRunning() {

        return this->is_running;
    }
};