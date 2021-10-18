#pragma once

// Includes
#include "KornDraw.hpp"

class Goomba {
private:

    int x;
    int y;
    
    int progress;
    int progress_max;

    int color;

    std::vector <Position> path_points;

    WINDOW* window;

public:

    Goomba(WINDOW* window, std::vector <Position> path_points) {

        this->path_points = path_points;
        
        this->progress = 0;
        this->progress_max = this->path_points.size();

        this->x = this->path_points.at(this->progress).x;
        this->y = this->path_points.at(this->progress).y;
        
        this->window = window;
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

    // Functions
    void update() {

    }
    void draw() {

        // Draw Goomba
        KornDraw::drawCharacter(this->window, this->x, this->y, 'O');
    }
};