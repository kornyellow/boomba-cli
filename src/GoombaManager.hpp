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
    int goomba_spawn_cooldown;
    int goomba_spawn_rate;
    
    std::vector<std::string> goomba_set;

    // Window
    WINDOW* window;

public:

    GoombaManager(WINDOW* window) {

        this->window = window;

        this->goomba_spawn_cooldown = 0;
        this->goomba_spawn_rate = 100;
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
    void moveGoomba() {

        // Spawn Start
        if(this->spawnGoomba()) {

            // Get Progress Max
            int progress_max = 0;
            while(true) {
                int progress_max_old = progress_max;
                for(int i = 0; i < this->goombas.size(); i++) {

                    if(this->goombas.at(i)->getProgress() == progress_max) progress_max ++;
                }
                if(progress_max == progress_max_old) break;
            }
            // Move To Spawn New
            for(int i = 0; i < this->goombas.size(); i++) {

                if(this->goombas.at(i)->getProgress() >= 0 && this->goombas.at(i)->getProgress() < progress_max) {

                    this->goombas.at(i)->moveForward();
                }
            }
        }

        // Move Leader
        for(int i = 0; i < this->goombas.size(); i++) {

            // Get Leader
            if(this->goombas.at(i)->getLeader()) {
                    
                if(this->goombas.at(i)->getMoveCooldown() > 0) continue;

                int leader_progress_start = this->goombas.at(i)->getProgress();
                int leader_progress_max = leader_progress_start;
                
                // Get Progress Max
                while(true) {
                    int leader_progress_max_old = leader_progress_max;
                    for(int j = 0; j < this->goombas.size(); j++) {

                        if(this->goombas.at(j)->getProgress() == leader_progress_max) leader_progress_max ++;
                    }
                    if(leader_progress_max == leader_progress_max_old) break;
                }

                // Move Goombas In Leader
                for(int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() >= leader_progress_start && this->goombas.at(j)->getProgress() < leader_progress_max) {

                        this->goombas.at(j)->moveForward();
                    }
                }

                int progress_max = this->goombas.at(i)->getProgressMax();
                int goomba_speed = 50;
                int goomba_cooldown = ((float)leader_progress_max / (float)progress_max) * goomba_speed;
                goomba_cooldown -= (float(1) - ((float)leader_progress_max / (float)progress_max)) * ((float)goomba_speed / (float)2);
                if((float)leader_progress_max > (float)progress_max - ((float)progress_max / (float)6)) {

                    goomba_cooldown += ((float)leader_progress_max / (float)progress_max) * ((float)goomba_speed * 2);
                }
                this->goombas.at(i)->setMoveCooldown(goomba_cooldown);


                // Remove Collide Leader
                for(int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() == leader_progress_max + 1) {
                        
                        if(!this->goombas.at(j)->getLeader()) continue;

                        this->deleteGoomba(j);
                        break;
                    }
                }
            }
        }

        // Move Back
        for(int i = 0; i < this->goombas.size(); i++) {

            if(this->goombas.at(i)->getLeader()) continue;

            bool is_leader = true;
            int goomba_progress = this->goombas.at(i)->getProgress();
            
            if(this->goombas.at(i)->getMoveCooldown() > 0) continue;

            // Find Tail
            for(int j = 0; j < this->goombas.size(); j++) {

                if(this->goombas.at(j)->getProgress() == goomba_progress - 1) {

                    is_leader = false;
                    break;
                }
            }
            if(!is_leader) {

                this->goombas.at(i)->setMoveCooldownMax();
                continue;
            }

            // Find Last Group Tail Color
            int last_group_tail_color = -1;
            int search_progress = goomba_progress - 1;
            while(true) {

                for(int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() == search_progress) {

                        last_group_tail_color = this->goombas.at(j)->getColor();
                        break;
                    }
                }
                search_progress --;
                if(search_progress <= 0) break;
                if(last_group_tail_color != -1) break;
            }

            // Get Group Head Color
            int group_head_color;
            for(int j = 0; j < this->goombas.size(); j++) {
                
                if(this->goombas.at(j)->getProgress() == goomba_progress) {

                    group_head_color = this->goombas.at(j)->getColor();
                }
            }

            // Check If Match
            if(last_group_tail_color != group_head_color && last_group_tail_color != C_WHITE) continue;
            
            // Move Backward
            int leader_progress_start = this->goombas.at(i)->getProgress();
            int leader_progress_max = leader_progress_start;
            
            // Get Progress Max
            while(true) {
                int leader_progress_max_old = leader_progress_max;
                for(int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() == leader_progress_max) leader_progress_max ++;
                }
                if(leader_progress_max == leader_progress_max_old) break;
            }

            // Move Goombas In Leader
            for(int j = 0; j < this->goombas.size(); j++) {

                if(this->goombas.at(j)->getProgress() >= leader_progress_start && this->goombas.at(j)->getProgress() < leader_progress_max) {

                    this->goombas.at(j)->moveBackward();
                }
            }

            this->goombas.at(i)->setMoveCooldown();
            this->goombas.at(i)->setFoundMatch(true);

            if(last_group_tail_color == C_WHITE) this->goombas.at(i)->setFoundMatch(false);
        }
    }   
    void addGoomba(Goomba* goomba) {

        this->goombas.push_back(goomba);
    }
    bool spawnGoomba() {

        // Return If In Cooldown
        if(this->goomba_spawn_cooldown > 0) return false;

        for(int i = 0; i < this->goombas.size(); i++) {

            if(this->goombas.at(i)->getProgress() < 2) false;
        }

        // Get Goomba Color
        if(this->goomba_set.empty()) return false;
        char goomba_color_text = this->goomba_set.at(0).at(0);
        this->goomba_set.at(0).erase(this->goomba_set.at(0).begin());
        if(this->goomba_set.at(0).empty()) this->goomba_set.erase(this->goomba_set.begin());

        // Calculate Color
        int goomba_color;
        switch (goomba_color_text) {
        case '#':
            goomba_color = C_WHITE;
            break;
        case 'R':
            goomba_color = C_RED;
            break;
        case 'G':
            goomba_color = C_GREEN;
            break;
        case 'Y':
            goomba_color = C_YELLOW;
            break;
        }

        Goomba* goomba = new Goomba(this->window, this->path_points);
        if(goomba_color == C_WHITE) {
            goomba->setLeader(true);
            this->goomba_spawn_cooldown = this->goomba_spawn_rate;
        }
        goomba->setColor(goomba_color);
        this->goombas.push_back(goomba);

        return true;
    }
    void updateGoombas() {
        
        // Spawn Cooldown
        if(this->goomba_spawn_cooldown > 0) this->goomba_spawn_cooldown --;

        // Move Goombas
        this->moveGoomba();

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
    std::vector <int> getAllColor() {

        std::vector <int> colors;
        for(int i = 0; i < this->goombas.size(); i++) {

            int insert_color = this->goombas.at(i)->getColor();
            if(insert_color == C_WHITE) continue;

            bool is_push = true;
            for(int j = 0; j < colors.size(); j++) {

                if(colors.at(j) == insert_color) false;
            }   
            if(!is_push) continue;

            colors.push_back(insert_color);
        }
        return colors;
    }

    // Goomba Set
    void addGoombaSet(std::string goomba_set) {

        this->goomba_set.push_back(goomba_set);
    }
    std::vector <std::string> getGoombaSet() {

        return this->goomba_set;
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
    
    // Functions
    void update() {

        // Update Goombas
        updateGoombas();
    }
    void draw() {

        // Draw Path
        int path_points_size = this->path_points.size();
        for(int i = 0; i < path_points_size; i++) {

            // Draw Path
            if(i < path_points_size - 1) {

                KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, '.', C_GRAY);
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
};