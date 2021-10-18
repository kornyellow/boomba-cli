#pragma once

// Includes
#include "Goomba.hpp"
#include "KornDraw.hpp"

class GoombaManager {
private:

    // Paths
    std::vector<Position> paths;
    std::vector<Position> path_points;
    
    // Goombas
    std::vector<Goomba> goombas;
    int goomba_speed;
    int goomba_rate;

    // Window
    WINDOW* window;

public:

    GoombaManager(WINDOW* window) {

        this->window = window;

        this->goomba_speed = 30;
        this->goomba_rate = 0;
    }

    // Paths
    void addPath(int x, int y) {

        Position position(x, y);
        this->paths.push_back(position);
    }
    Position getPath(int index) {

        return this->paths.at(index);
    }
    void calculatePath() {

        for(int i = 0; i < this->paths.size(); i++) {

            if(i < this->paths.size() - 1) {

                for(int y = this->paths.at(i).y; y <= this->paths.at(i + 1).y; y++) {
                    for(int x = this->paths.at(i).x; x <= this->paths.at(i + 1).x; x++) {
                        
                        bool is_duplicate = false;
                        for(int j = 0; j < this->path_points.size(); j++) {

                            if(x == this->path_points.at(j).x && y == this->path_points.at(j).y) {
                                
                                is_duplicate = true;
                                break;
                            }
                        }
                        if(is_duplicate) continue;

                        Position position(x, y);
                        this->path_points.push_back(position);
                    }
                }
            }
        }
    }

    // Goombas
    void spawnGoomba() {

        for(int i = 0; i < this->goombas.size(); i++) {

            if(this->goombas.at(i).getProgress() < 2) return;
        }

        Goomba goomba(this->window, this->path_points);
        this->goombas.push_back(goomba);
    }
    void updateGoombas() {

        // Move Goombas
        if(this->goomba_rate < 0) {
            for(int i = 0; i < this->goombas.size(); i++) {

                this->goomba_rate = this->goomba_speed;
                this->goombas.at(i).moveForward();
                this->spawnGoomba();
            }
        }
        this->goomba_rate --;

        // Update Goombas
        for(int i = 0; i < this->goombas.size(); i++) {

            this->goombas.at(i).update();
        }
    }
    void drawGoombas() {

        for(int i = 0; i < this->goombas.size(); i++) {

            this->goombas.at(i).draw();
        }
    }
    
    // Functions
    void update() {

        // Update Goombas
        updateGoombas();
    }
    void draw() {

        // Draw Start Point, End Point
        int path_points_size = this->path_points.size();
        for(int i = 0; i < path_points_size; i++) {

            // Start Point
            if(i == 0) KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, 'S');

            // Draw Path
            if(i < path_points_size - 1) {

                KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, '.');
            }

            // End Point
            if(i == path_points_size - 1) KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, 'E');
        }

        // Draw Goombas
        drawGoombas();
    }   
};