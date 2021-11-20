#pragma once

// Includes
#include "Mixer.hpp"
#include "Goomba.hpp"
#include "KornDraw.hpp"

class GoombaManager {
private:

    // Paths
    std::vector<Position> paths;
    std::vector<Position> path_points;
    
    // Goombas
    std::vector<Goomba*> goombas;
    long int goomba_spawn_cooldown;
    long int goomba_spawn_rate;
    
    // Color
    std::string color_set;

    // Game Over
    bool is_game_over;

    // Goomba Set Generator
    std::vector<std::string> goomba_set;
    unsigned short int fuzzyness;
    unsigned short int min_length;
    unsigned short int max_length;
    unsigned short int color_min_length;
    unsigned short int color_max_length;
    unsigned short int color_max_count;
    std::string goombaSetGenerate() {

        unsigned short int total_length = KornRandom::randomIntRange(min_length, max_length);
        std::string generated_goombas = "";
        unsigned short int generated_length = 0;
        unsigned short int last_choose_color = C_GRAY;
        for(unsigned short int i = 0; i < this->color_max_count; i++) {

            if(generated_length >= total_length) break;

            unsigned short int choose_color = last_choose_color;
            while(choose_color == last_choose_color) choose_color = this->color_set.at(KornRandom::randomInt(this->color_set.size() - 1));
            
            unsigned short int total_color_length = KornRandom::randomIntRange(this->color_min_length, this->color_max_length - 1);
            for(unsigned short int j = 0; j < total_color_length; j++) {
                
                generated_goombas.push_back(choose_color);
                generated_length ++;
            }
            last_choose_color = choose_color;
        }

        return generated_goombas + "#";
    }   

    // Tense
    bool is_tense;
    unsigned short int tense_delay;

    // Mixer
    Mixer* mixer;

    // Window
    WINDOW* window;

public:

    // Constructor and Destructor
    GoombaManager(WINDOW* window, Mixer* mixer) {

        // Is Game Over
        this->is_game_over = false;

        // Mixer
        this->mixer = mixer;
        
        // Window
        this->window = window;

        // Goomba Spawn
        this->goomba_spawn_cooldown = 0;
        this->goomba_spawn_rate = 1800;

        // Goomba Set Generate Attribute
        this->min_length = 50;
        this->max_length = 80;
        this->color_min_length = 2;
        this->color_max_length = 6;
        this->color_max_count = 20;

        // Tense
        this->is_tense = false;
        this->tense_delay = 0;
    }
    ~GoombaManager() {

    }   

    // Paths Management
    void addPath(unsigned long int x, unsigned long int y) {

        Position position(x, y);
        this->paths.push_back(position);
    }
    Position getPath(unsigned long int index) {

        return this->paths.at(index);
    }
    void calculatePath() {

        for(unsigned long int i = 0; i < this->paths.size(); i++) {

            if(i < this->paths.size() - 1) {

                unsigned long int scan_y_dir = KornMath::sign(this->paths.at(i + 1).y - this->paths.at(i).y);
                if(scan_y_dir == 0) scan_y_dir = 1;
                
                if(scan_y_dir == 1) {
                    for(unsigned long int y = this->paths.at(i).y; y <= this->paths.at(i + 1).y; y++) {
                        unsigned long int scan_x_dir = KornMath::sign(this->paths.at(i + 1).x - this->paths.at(i).x);
                        if(scan_x_dir == 0) scan_x_dir = 1;
                        
                        if(scan_x_dir == 1) {
                            for(unsigned long int x = this->paths.at(i).x; x <= this->paths.at(i + 1).x; x++) {
                                
                                bool is_duplicate = false;
                                for(unsigned long int j = 0; j < this->path_points.size(); j++) {

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
                            for(unsigned long int x = this->paths.at(i).x; x >= this->paths.at(i + 1).x; x--) {
                                
                                bool is_duplicate = false;
                                for(unsigned long int j = 0; j < this->path_points.size(); j++) {

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
                    for(unsigned long int y = this->paths.at(i).y; y >= this->paths.at(i + 1).y; y--) {
                        int scan_x_dir = KornMath::sign(this->paths.at(i + 1).x - this->paths.at(i).x);
                        if(scan_x_dir == 0) scan_x_dir = 1;
                        
                        if(scan_x_dir == 1) {
                            for(unsigned long int x = this->paths.at(i).x; x <= this->paths.at(i + 1).x; x++) {
                                
                                bool is_duplicate = false;
                                for(unsigned long int j = 0; j < this->path_points.size(); j++) {

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
                            for(unsigned long int x = this->paths.at(i).x; x >= this->paths.at(i + 1).x; x--) {
                                
                                bool is_duplicate = false;
                                for(unsigned long int j = 0; j < this->path_points.size(); j++) {

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

                for(unsigned long int y = this->paths.at(i).y; y <= this->paths.at(i + 1).y; y++) {
                    for(unsigned long int x = this->paths.at(i).x; x <= this->paths.at(i + 1).x; x++) {
                        
                        bool is_duplicate = false;
                        for(unsigned long int j = 0; j < this->path_points.size(); j++) {

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
    void clearPathPoints() {

        this->path_points.clear();
        this->paths.clear();
    }

    // Goombas Management
    void moveGoomba() {

        if(this->tense_delay == 0) this->is_tense = false;
        else this->tense_delay --;

        // Spawn Start
        if(this->spawnGoomba()) {

            // Get Progress Max
            long int progress_max = 0;
            while(true) {
                long int progress_max_old = progress_max;
                for(unsigned long int i = 0; i < this->goombas.size(); i++) {

                    if(this->goombas.at(i)->getProgress() == progress_max) progress_max ++;
                }
                if(progress_max == progress_max_old) break;
            }
            // Move To Spawn New
            for(unsigned long int i = 0; i < this->goombas.size(); i++) {

                if(this->goombas.at(i)->getProgress() >= 0 && this->goombas.at(i)->getProgress() < progress_max) {

                    this->goombas.at(i)->moveForward();
                }
            }
        }

        // Move Leader
        for(unsigned long int i = 0; i < this->goombas.size(); i++) {

            // Get Leader
            if(this->goombas.at(i)->getLeader()) {
                    
                if(this->goombas.at(i)->getMoveCooldown() > 0) continue;

                long int leader_progress_start = this->goombas.at(i)->getProgress();
                long int leader_progress_max = leader_progress_start;
                
                // Get Progress Max
                while(true) {
                    long int leader_progress_max_old = leader_progress_max;
                    for(unsigned long int j = 0; j < this->goombas.size(); j++) {

                        if(this->goombas.at(j)->getProgress() == leader_progress_max) leader_progress_max ++;
                    }
                    if(leader_progress_max == leader_progress_max_old) break;
                }

                // Move Goombas In Leader
                for(unsigned long int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() >= leader_progress_start && this->goombas.at(j)->getProgress() < leader_progress_max) {

                        this->goombas.at(j)->moveForward();
                        this->goombas.at(j)->setMoveCooldownMax();
                    }
                }

                long int progress_max = this->goombas.at(i)->getProgressMax();
                unsigned long int goomba_speed = 50;
                long int goomba_cooldown = ((float)leader_progress_max / (float)progress_max) * goomba_speed;
                goomba_cooldown -= (float(1) - ((float)leader_progress_max / (float)progress_max)) * ((float)goomba_speed / (float)2);
                if((float)leader_progress_max > (float)progress_max - ((float)progress_max / (float)6)) {

                    goomba_cooldown += ((float)leader_progress_max / (float)progress_max) * ((float)goomba_speed);
                    this->is_tense = true;
                    this->tense_delay = 500;
                }
                this->goombas.at(i)->setMoveCooldown(goomba_cooldown);


                // Remove Collide Leader
                bool is_found_collided_leader = false;
                for(unsigned long int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() == leader_progress_max + 1) {
                        
                        if(!this->goombas.at(j)->getLeader()) continue;

                        this->deleteGoomba(j);
                        this->mixer->playSoundEffect(SFX_CONNECT);
                        is_found_collided_leader = true;
                        break;
                    }
                }
                if(is_found_collided_leader) {

                    this->moveGoomba();
                }
            }
        }

        // Move Back
        for(unsigned long int i = 0; i < this->goombas.size(); i++) {

            if(this->goombas.at(i)->getLeader()) continue;

            bool is_leader = true;
            long int goomba_progress = this->goombas.at(i)->getProgress();
            
            if(this->goombas.at(i)->getMoveCooldown() > 0) continue;

            // Find Tail
            for(unsigned long int j = 0; j < this->goombas.size(); j++) {

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
            short int last_group_tail_color = -1;
            long int search_progress = goomba_progress - 1;
            while(true) {

                for(unsigned long int j = 0; j < this->goombas.size(); j++) {

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
            unsigned short int group_head_color;
            for(unsigned long int j = 0; j < this->goombas.size(); j++) {
                
                if(this->goombas.at(j)->getProgress() == goomba_progress) {

                    group_head_color = this->goombas.at(j)->getColor();
                }
            }

            // Check If Match
            if(last_group_tail_color != group_head_color && last_group_tail_color != C_GRAY) continue;
            
            // Move Backward
            long int leader_progress_start = this->goombas.at(i)->getProgress();
            long int leader_progress_max = leader_progress_start;
            
            // Get Progress Max
            while(true) {
                long int leader_progress_max_old = leader_progress_max;
                for(unsigned long int j = 0; j < this->goombas.size(); j++) {

                    if(this->goombas.at(j)->getProgress() == leader_progress_max) leader_progress_max ++;
                }
                if(leader_progress_max == leader_progress_max_old) break;
            }

            // Move Goombas In Leader
            for(unsigned long int j = 0; j < this->goombas.size(); j++) {

                if(this->goombas.at(j)->getProgress() >= leader_progress_start && this->goombas.at(j)->getProgress() < leader_progress_max) {

                    this->goombas.at(j)->moveBackward();
                }
            }

            this->goombas.at(i)->setMoveCooldown();
            this->goombas.at(i)->setFoundMatch(true);

            if(last_group_tail_color == C_GRAY) this->goombas.at(i)->setFoundMatch(false);
        }
    }   
    void addGoomba(Goomba* goomba) {

        this->goombas.push_back(goomba);
    }
    bool spawnGoomba() {

        // Return If In Cooldown
        if(this->goomba_spawn_cooldown > 0) return false;

        // Get Goomba Color
        if(this->goomba_set.empty()) {

            if(this->is_game_over) return false;
            this->addGoombaSet(this->goombaSetGenerate());
            return false;
        }
        char goomba_color_text = this->goomba_set.at(0).at(0);
        this->goomba_set.at(0).erase(this->goomba_set.at(0).begin());
        if(this->goomba_set.at(0).empty()) this->goomba_set.erase(this->goomba_set.begin());

        // Calculate Color
        unsigned short int goomba_color;
        switch (goomba_color_text) {
        case '#':
            goomba_color = C_GRAY;
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
        case 'B':
            goomba_color = C_BLUE;
            break;
        case 'M':
            goomba_color = C_MAGENTA;
            break;
        case 'W':
            goomba_color = C_WHITE;
            break;
        }

        Goomba* goomba = new Goomba(this->window, this->path_points);
        if(goomba_color == C_GRAY) {
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
        for(unsigned long int i = 0; i < this->goombas.size(); i++) {

            this->goombas.at(i)->update();
        }
    }
    void drawGoombas() {

        for(unsigned long int i = 0; i < this->goombas.size(); i++) {

            this->goombas.at(i)->draw();
        }
    }
    std::vector <unsigned short int> getAllColor() {

        std::vector <unsigned short int> colors;
        for(unsigned long int i = 0; i < this->goombas.size(); i++) {

            unsigned short int insert_color = this->goombas.at(i)->getColor();
            if(insert_color == C_GRAY) continue;

            bool is_push = true;
            for(unsigned long int j = 0; j < colors.size(); j++) {

                if(colors.at(j) == insert_color) is_push = false;
            }   
            if(!is_push) continue;

            colors.push_back(insert_color);
        }
        return colors;
    }

    // Goomba Set Management
    void addGoombaSet(std::string goomba_set) {

        this->goomba_set.push_back(goomba_set);
    }
    std::vector <std::string> getGoombaSet() {

        return this->goomba_set;
    }   

    // Get Goomba Lists Management
    std::vector <Goomba*> getGoombas() {

        return this->goombas;
    }
    void deleteGoomba(unsigned long int index) {

        this->goombas.erase(this->goombas.begin() + index);
    }
    long int getMaxProgressLeader(unsigned long int start) {

        long int last_progress = start;
        long int lastest_progress = start;
        while(true) {
            
            last_progress ++;
            for(unsigned long int i = 0; i < this->goombas.size(); i++) {

                if(this->goombas.at(i)->getProgress() == last_progress) {

                    if(this->goombas.at(i)->getLeader()) {
                        return lastest_progress;
                    }
                    lastest_progress = last_progress;
                    break;
                }
            }
            if((unsigned long int)last_progress >= this->getPathPoints().size()) break;
        }
        return lastest_progress;
    }
    long int getMaxProgress(long int start) {

        long int last_progress = start;
        while(true) {

            long int last_find = last_progress;
            for(unsigned long int i = 0; i < this->goombas.size(); i++) {

                if(this->goombas.at(i)->getProgress() == last_progress) {
                    
                    last_progress ++;
                }
            }
            if(last_find == last_progress) break;
        }
        return last_progress;
    }
    
    // Color Manament
    void setColorSet(std::string color_set) {

        this->color_set = color_set;
    }   

    // Game Over Accessors
    bool isGameOver() {

        return this->is_game_over;
    }
    void setGameOver(bool is_game_over) {

        this->is_game_over = is_game_over;  
    }

    // Tense Accessors
    bool isTense() {

        return this->is_tense;
    }   
    void setTense(bool is_tense) {

        this->is_tense = is_tense;
    }

    // Functions
    void update() {

        // Check Game Over
        for(unsigned long int i = 0; i < this->goombas.size(); i++) {
            
            Position last_position = this->path_points.at(this->path_points.size() - 1);
            if(this->goombas.at(i)->getPosition(this->goombas.at(i)->getProgress()) == last_position) {

                this->is_game_over = true;
                this->mixer->stopMusic();
                this->deleteGoomba(i);
                break;
            }
        }

        // Perform Game Over
        if(this->is_game_over) {
            
            for(unsigned int i = 0; i < this->goombas.size(); i++) {

                this->goombas.at(i)->setMoveCooldown(0);
            }
        }

        // Update Rate
        if(this->goombas.empty()) {
            
            this->is_tense = false;
            this->tense_delay = 0;
            this->goomba_spawn_cooldown = 0;
        }

        // Update Goombas
        this->updateGoombas();
    }
    void draw() {

        // Draw Path
        unsigned long int path_points_size = this->path_points.size();
        for(unsigned long int i = 0; i < path_points_size; i++) {

            // Draw Path
            if(i < path_points_size - 1) {

                KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, '.', C_GRAY);
            }
        }

        // Draw Goombas
        drawGoombas();

        // Draw Start Point And End Point
        for(unsigned long int i = 0; i < path_points_size; i++) {

            // Start Point
            if(i == 0) KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, 'S');

            // End Point
            if(i == path_points_size - 1) KornDraw::drawCharacter(this->window, this->path_points.at(i).x, this->path_points.at(i).y, 'E');
        }
    }
};