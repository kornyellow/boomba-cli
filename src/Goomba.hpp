#pragma once

// Includes
#include "KornDraw.hpp"

class Goomba {
private:

    int x;
    int y;
    
    int progress;
    int progress_max;

    int insert_delay;

    int color;

    std::vector <Position> path_points;

    WINDOW* window;

public:

    Goomba(WINDOW* window, std::vector <Position> path_points) {

        // Set Path Points
        this->path_points = path_points;
        
        // Set Progress
        this->progress = 0;
        this->progress_max = this->path_points.size();

        // Set Initial Position
        this->x = this->path_points.at(this->progress).x;
        this->y = this->path_points.at(this->progress).y;

        // Window
        this->window = window;

        // Insert Delay
        this->insert_delay = 0;

        // Color
        this->color = KornRandom::randomIntRange(3, 7);
    }

    // Move
    void setProgress(int progress) {

        this->progress = progress;
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

    }
    void draw() {

        // Draw Goomba
        KornDraw::drawColorOn(this->window, COLOR_PAIR(this->color));
        
        KornDraw::drawCharacter(this->window, this->x, this->y, 'O');
        if(this->insert_delay > 0) {

            this->insert_delay --;
            KornDraw::drawCharacter(this->window, this->x, this->y, '=');
        }

        KornDraw::drawColorOff(this->window, COLOR_PAIR(this->color));
    }

    // Color
    void setColor(int color) {

        this->color = color;
    }
    int getColor() {

        return this->color;
    }
};