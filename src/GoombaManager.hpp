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
    std::vector<Goomba*> goombas;
    int goomba_speed;
    int goomba_rate;

    // Window
    WINDOW* window;

public:

    GoombaManager(WINDOW* window) {

        this->window = window;

        this->goomba_speed = 120;
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

                int scan_y_dir = KornMath::sign(this->paths.at(i + 1).y - this->paths.at(i).y);
                if(scan_y_dir == 0) scan_y_dir = 1;
                
                if(scan_y_dir == 1) {
                    for(int y = this->paths.at(i).y; y <= this->paths.at(i + 1).y; y++) {
                        int scan_x_dir = KornMath::sign(this->paths.at(i + 1).x - this->paths.at(i).x);
                        if(scan_x_dir == 0) scan_x_dir = 1;
                        
                        if(scan_x_dir == 1) {
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
                        else {
                            for(int x = this->paths.at(i).x; x >= this->paths.at(i + 1).x; x--) {
                                
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
                else {
                    for(int y = this->paths.at(i).y; y >= this->paths.at(i + 1).y; y--) {
                        int scan_x_dir = KornMath::sign(this->paths.at(i + 1).x - this->paths.at(i).x);
                        if(scan_x_dir == 0) scan_x_dir = 1;
                        
                        if(scan_x_dir == 1) {
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
                        else {
                            for(int x = this->paths.at(i).x; x >= this->paths.at(i + 1).x; x--) {
                                
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
    std::vector <Position> getPathPoints() {

        return this->path_points;
    }   

    // Goombas
    void addGoomba(Goomba* goomba) {

        this->goombas.push_back(goomba);
    }
    void spawnGoomba() {

        for(int i = 0; i < this->goombas.size(); i++) {

            if(this->goombas.at(i)->getProgress() < 2) return;
        }

        Goomba* goomba = new Goomba(this->window, this->path_points);
        this->goombas.push_back(goomba);
    }
    void updateGoombas() {

        // Move Goombas
        if(this->goomba_rate < 0) {
            
            // Move
            int last_progress = this->getMaxProgress(1);

            for(int i = 0; i < this->goombas.size(); i++) {

                this->goomba_rate = this->goomba_speed;
                
                if(this->goombas.at(i)->getProgress() <= last_progress) {
                    
                    this->goombas.at(i)->moveForward();
                }
                
                this->spawnGoomba();
            }
        }
        this->goomba_rate --;

        // Update Goombas
        for(int i = 0; i < this->goombas.size(); i++) {

            this->goombas.at(i)->update();
        }
    }
    void drawGoombas() {

        for(int i = 0; i < this->goombas.size(); i++) {

            this->goombas.at(i)->draw();
        }
    }
    
    // Functions
    void update() {

        // Set Speed
        this->goomba_speed = (((float)this->getMaxProgress(1) / (float)this->path_points.size()) * 200);

        // Update Goombas
        updateGoombas();
    }
    void draw() {

        // Draw Path
        int path_points_size = this->path_points.size();
        for(int i = 0; i < path_points_size; i++) {

            // Draw Path
            if(i < path_points_size - 1) {

                KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, '.');
            }
        }

        // Draw Goombas
        drawGoombas();

        // Draw Start Point And End Point
        for(int i = 0; i < path_points_size; i++) {

            // Start Point
            if(i == 0) KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, 'S');

            // End Point
            if(i == path_points_size - 1) KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, 'E');
        }
    }

    // Get Goomba Lists
    std::vector <Goomba*> getGoombas() {

        return this->goombas;
    }
    void deleteGoomba(int index) {

        this->goombas.erase(this->goombas.begin() + index);
    }
    int getMaxProgress(int start) {

        int last_progress = start;
        while(true) {

            int last_find = last_progress;
            for(int i = 0; i < this->goombas.size(); i++) {

                if(this->goombas.at(i)->getProgress() == last_progress) {
                    
                    last_progress ++;
                }
            }
            if(last_find == last_progress) break;
        }
        return last_progress;
    }
};