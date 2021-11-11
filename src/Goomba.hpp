#pragma once

// Includes
#include "KornDraw.hpp"

class Goomba {
private:

    int x;
    int y;
    
    int progress;
    int progress_max;
    int move_cooldown;
    int move_cooldown_max;
    int move_cooldown_max_default;

    int insert_delay;

    bool is_leader;

    bool is_found_match;
    int color;

    std::vector <Position> path_points;

    WINDOW* window;

public:

    Goomba(WINDOW* window, std::vector <Position> path_points) {

        // Set Path Points
        this->path_points = path_points;
        
        // Set Progress
        this->move_cooldown = 0;
        this->move_cooldown_max_default = 20;
        this->move_cooldown_max = this->move_cooldown_max_default;
        this->progress = 0;
        this->progress_max = this->path_points.size();

        // Set Initial Position
        this->x = this->path_points.at(this->progress).x;
        this->y = this->path_points.at(this->progress).y;

        // Window
        this->window = window;

        // Insert Delay
        this->insert_delay = 0;

        // Leader
        this->is_leader = false;

        // Color
        this->is_found_match = false;
        this->color = KornRandom::randomIntRange(3, 7);
    }

    // Movement
    int getMoveCooldownMaxDefault() {

        return this->move_cooldown_max_default;
    }
    int getMoveCooldownMax() {

        return this->move_cooldown_max;
    }
    void setMoveCooldownMax(int move_cooldown_max = 0) {

        if(move_cooldown_max == 0) {
            
            this->move_cooldown_max = this->move_cooldown_max_default;
        }
        else {

            this->move_cooldown_max = move_cooldown_max;
        }
    }
    void setMoveCooldown(int move_cooldown = 0) {

        if(this->is_leader) {
            
            this->move_cooldown = move_cooldown;
        }
        else {

            this->move_cooldown = this->move_cooldown_max;
            if(this->move_cooldown_max > 0) this->move_cooldown_max -= 4;
        }
    }
    int getMoveCooldown() {

        return this->move_cooldown;
    }
    void setProgress(int progress) {

        this->progress = progress;
    }
    int getProgressMax() {

        return this->progress_max;
    }
    int getProgress() {

        return this->progress;
    }
    void setPosition(int progress) {

        this->x = this->path_points.at(progress).x;
        this->y = this->path_points.at(progress).y;
    }
    Position getPosition(int progress) {

        return this->path_points.at(progress);
    }
    void moveForward() {

        if(this->progress + 1 == this->progress_max) return;

        this->progress++;
        this->setPosition(this->progress);
    }
    void moveBackward() {

        if(this->progress - 1 == -1) return;

        this->progress--;
        this->setPosition(this->progress);
    }
    void setInsertDelay(int insert_delay) {

        this->insert_delay = insert_delay;
    }

    // Functions
    void update() {

        // Move Cooldown
        if(this->move_cooldown > 0) this->move_cooldown --;
    }
    void draw() {

        char character = '@';

        // Is Leader
        if(is_leader) character = '#';

        // Draw Goomba
        KornDraw::drawCharacter(this->window, this->x, this->y, character, this->color);
        if(this->insert_delay > 0) {

            this->insert_delay --;
            KornDraw::drawCharacter(this->window, this->x, this->y, '*', this->color);
        }
    }

    // Color
    void setColor(int color) {

        this->color = color;
    }
    int getColor() {

        return this->color;
    }
    void setFoundMatch(bool is_found_match) {

        this->is_found_match = is_found_match;
    }
    bool getFoundMatch() {

        return this->is_found_match;
    }
    
    // Leader
    void setLeader(bool is_leader) {

        this->is_leader = is_leader;
    }
    bool getLeader() {

        return this->is_leader;
    }
};