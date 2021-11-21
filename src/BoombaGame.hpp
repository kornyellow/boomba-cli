#pragma once

// Includes
#include "ScoreList.hpp"
#include "Item.hpp"
#include "Particle.hpp"
#include "Mixer.hpp"
#include "GoombaManager.hpp"
#include "BoombaBoard.hpp"
#include "BoombaUI.hpp"
#include "Boomba.hpp"
#include "Fruit.hpp"

class BoombaGame {
private:

    // Boomba Board
    BoombaBoard* board;

    // Scoreboard
    ScoreList* score_list;

    // Items
    std::vector <Item> items;
    void updateItems() {

        // Update Items
        for(unsigned int i = 0; i < this->items.size(); i++) this->items.at(i).update();

        // Update Item Collide Boomba
        this->itemCollideBoomba();

        // Update Item Out of Bounds
        for(unsigned int i = 0; i < this->items.size(); i++) if(!this->items.at(i).isShow()) this->items.erase(this->items.begin() + i);
    }
    void drawItems() {

        for(unsigned int i = 0; i < this->items.size(); i++) this->items.at(i).draw(); 
    }
    void itemCollideBoomba() {

        for(unsigned int i = 0; i < this->items.size(); i++) {

            if(!this->items.at(i).isShow()) continue;

            if(this->items.at(i).getX() >= this->boomba->getX() && 
               this->items.at(i).getX() <= this->boomba->getX() + 6 && 
               this->items.at(i).getY() >= this->boomba->getY() && 
               this->items.at(i).getY() <= this->boomba->getY() + 1) {

                this->mixer->playSoundEffect(SFX_COLLECT);
                this->mixer->playSoundEffect(SFX_EYE);

                switch(this->items.at(i).getIcon()) {
                case 'E' :
                    this->boomba->setItemEyeDuration(600);
                    break;
                }

                this->items.at(i).setShow(false);
            }
        }
    }

    // Mixer
    Mixer* mixer;
    std::vector <std::string> music_list;
    void loadAudio() {

        // Music
        this->mixer->addMusic(MUS_MENU);
        this->mixer->addMusic(MUS_HIGH);
        this->mixer->addMusic(MUS_GAME_1);
        this->mixer->addMusic(MUS_GAME_2);
        this->mixer->addMusic(MUS_GAME_3);
        this->mixer->addMusic(MUS_GAME_4);
        this->mixer->addMusic(MUS_GAME_5);
        this->mixer->addMusic(MUS_TENSE);
        this->mixer->addMusic(MUS_END);

        this->mixer->playMusic(MUS_MENU);

        // Sound Effects
        this->mixer->addSoundEffect(SFX_SELECT);
        this->mixer->addSoundEffect(SFX_ENTER);
        this->mixer->addSoundEffect(SFX_CHOOSE);
        this->mixer->addSoundEffect(SFX_SHOOT);
        this->mixer->addSoundEffect(SFX_INSERT);
        this->mixer->addSoundEffect(SFX_BREAK);
        this->mixer->addSoundEffect(SFX_EXPLODE);
        this->mixer->addSoundEffect(SFX_CONNECT);
        this->mixer->addSoundEffect(SFX_COLLECT);
        this->mixer->addSoundEffect(SFX_EYE);

        // Music List
        this->music_list.push_back(MUS_GAME_1);
        this->music_list.push_back(MUS_GAME_2);
        this->music_list.push_back(MUS_GAME_3);
        this->music_list.push_back(MUS_GAME_4);
        this->music_list.push_back(MUS_GAME_5);
    }      

    // Particles
    std::vector <Particle> particles;
    void updateParticles() {

        for(unsigned long int i = 0; i < this->particles.size(); i++) this->particles.at(i).update();
    }
    void drawParticles() {

        for(unsigned long int i = 0; i < this->particles.size(); i++) this->particles.at(i).draw();
    }   

    // Game
    bool is_running;
    char is_tense;
    unsigned short int chose_music;
    chtype input;

    // Boomba UI
    BoombaUI* boomba_ui;
    
    // Boomba
    Boomba* boomba;
    std::vector <unsigned short int> color_set;
    void updateBoomba() {
        
        if(!this->goomba_manager->isGameOver()) {
            
            // Move
            if(this->input == 'D' || this->input == 'a') {

                Particle particle_top(this->boomba->getX() + 7, this->boomba->getY() + 1, this->window);
                particle_top.setColor(C_GRAY);
                
                particle_top.setFrame("__.");
                particle_top.setHSpeed(1);
                particle_top.setMoveSpeed(2);
                this->particles.push_back(particle_top);
            }
            if(this->input == 'C' || this->input == 'd') {

                Particle particle_top(this->boomba->getX() - 1, this->boomba->getY() + 1, this->window);
                particle_top.setColor(C_GRAY);
                
                particle_top.setFrame("__.");
                particle_top.setHSpeed(-1);
                particle_top.setMoveSpeed(2);
                this->particles.push_back(particle_top);
            }

            // Update Boomba
            this->boomba->update(this->input);
                
            // Shoot Fruit
            this->shootFruit();

            // Update Scope
            this->updateScope();

            // Update Shoot Colors
            if(!this->goomba_manager->getAllColor().empty() && this->goomba_manager->getGoombaSet().empty()) this->boomba->setColorSet(this->goomba_manager->getAllColor());
        }
    } 
    void updateScope() {

        unsigned long int scope = this->boomba->getY();
        while(true) {

            scope --;

            // Check If Scope Hit The Goomba
            bool is_collide = false;
            for(unsigned long int i = 0; i < this->goomba_manager->getGoombas().size(); i++) {

                long int goomba_progress = this->goomba_manager->getGoombas().at(i)->getProgress();
                if(this->boomba->getX() + 3 == this->goomba_manager->getGoombas().at(i)->getPosition(goomba_progress).x && scope == this->goomba_manager->getGoombas().at(i)->getPosition(goomba_progress).y + 1) {
                    
                    is_collide = true;
                    break;
                }
            }
            if(is_collide || scope <= 1) break;
        }
        this->boomba->setScope(scope);
    }   
    void shootFruit() {

        if(this->input == 'x' && this->fruits.empty()) { 

            this->mixer->playSoundEffect(SFX_SHOOT);

            unsigned short int fruit_color = this->boomba->fruitShoot();

            Fruit fruit(this->boomba->getX() + 3, this->boomba->getY() - 1, this->window);
            fruit.setFruitColor(fruit_color);
            if(this->boomba->getItemEyeDuration() > 0) fruit.setMoveSpeed(0);
            this->fruits.push_back(fruit);

            Particle particle_top(this->boomba->getX() + 3, this->boomba->getY() - 1, this->window);
            particle_top.setColor(fruit_color);
            
            particle_top.setFrame("____");
            particle_top.setHSpeed(1);
            particle_top.setMoveSpeed(3);
            this->particles.push_back(particle_top);

            particle_top.setFrame("____");
            particle_top.setHSpeed(-1);
            particle_top.setMoveSpeed(3);
            this->particles.push_back(particle_top);

            particle_top.setFrame("..");
            particle_top.setHSpeed(1);
            particle_top.setVSpeed(-1);
            particle_top.setMoveSpeed(3);
            this->particles.push_back(particle_top);

            particle_top.setFrame("..");
            particle_top.setHSpeed(-1);
            particle_top.setVSpeed(-1);
            particle_top.setMoveSpeed(3);
            this->particles.push_back(particle_top);
        }
    }

    // Fruits
    std::vector <Fruit> fruits;
    void updateFruits() {

        for(unsigned long int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).update();

            // Delete Fruit Out Of Bound
            if(this->fruits.at(i).getY() <= 0) {

                // Remove Fruit
                this->fruits.erase(this->fruits.begin() + i);

                break;
            }

            // Check If Fruit Collide With Goomba
            for(unsigned long int j = 0; j < this->goomba_manager->getGoombas().size(); j++) {

                long int goomba_progress = this->goomba_manager->getGoombas().at(j)->getProgress();
                Position goomba_position = this->goomba_manager->getGoombas().at(j)->getPosition(goomba_progress);
            
                if((unsigned long int)this->fruits.at(i).getX() == goomba_position.x && (unsigned long int)this->fruits.at(i).getY() + 1 == goomba_position.y) {
                       
                    // Destroy Match
                    float base_score = 20.0f;

                    int matches_destroyed = this->destroyMatch(goomba_progress, this->fruits.at(i).getColor());

                    // Add Score
                    if(!this->goomba_manager->isGameOver()) this->boomba_ui->addScore(base_score * (float)matches_destroyed);

                    // Remove Fruit
                    this->fruits.erase(this->fruits.begin() + i);

                    break;
                }
            }
        }
    }
    void drawFruits() {

        for(unsigned long int i = 0; i < this->fruits.size(); i++) this->fruits.at(i).draw();
    }
    unsigned long int destroyMatch(long int goomba_progress, unsigned short int match_color, bool is_insert = true) {

        // Move Progress
        goomba_progress ++;

        // Move
        std::vector <unsigned long int> cache_moved;
        long int last_progress = this->goomba_manager->getMaxProgress(goomba_progress);
        for(unsigned long int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

            if(this->goomba_manager->getGoombas().at(k)->getProgress() >= goomba_progress && this->goomba_manager->getGoombas().at(k)->getProgress() < last_progress) {
                
                this->goomba_manager->getGoombas().at(k)->moveForward();
                cache_moved.push_back(k);
            }
        }
        if(is_insert) {

            // Insert New One
            this->mixer->playSoundEffect(SFX_INSERT);

            Goomba* goomba = new Goomba(this->window, this->goomba_manager->getPathPoints());
            goomba->setProgress(goomba_progress);
            goomba->setPosition(goomba_progress);
            goomba->setInsertDelay(5);
            goomba->setColor(match_color);
            this->goomba_manager->addGoomba(goomba);
        }

        // Find Matches
        unsigned long int match = 1;
        long int find_left = 1;
        long int find_right = 1;
        bool left_found = true;
        bool right_found = true;

        while(true) {
            
            // Find Left
            long int old_find_left = find_left;
            if(left_found) {

                for(unsigned long int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

                    if(this->goomba_manager->getGoombas().at(k)->getProgress() == (long int)(goomba_progress - find_left)) {

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
            long int old_find_right = find_right;
            if(right_found) {

                for(unsigned long int k = 0; k < this->goomba_manager->getGoombas().size(); k++) {

                    if(this->goomba_manager->getGoombas().at(k)->getProgress() == (long int)(goomba_progress + find_right)) {

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
        unsigned long int want_match = 3;
        if(!is_insert) want_match = 4;
        if(match >= want_match) {

            this->mixer->playSoundEffect(SFX_BREAK);

            for(long int k = -find_left + 1; k <= find_right - 1; k++) {

                for(unsigned long int l = 0; l < this->goomba_manager->getGoombas().size(); l++) {

                    if(this->goomba_manager->getGoombas().at(l)->getProgress() == goomba_progress + k) {

                        Position destroyed_position = this->goomba_manager->getGoombas().at(l)->getPosition(this->goomba_manager->getGoombas().at(l)->getProgress());
                        
                        Particle particle(destroyed_position.x, destroyed_position.y, this->window);
                        particle.setColor(match_color);
                        particle.setMoveSpeed(3);
                        particle.setFrame("..");
                        
                        for(int i = -1; i <= 1; i++) {

                            for(int j = -1; j <= 1; j++) {

                                particle.setVSpeed(i);
                                particle.setHSpeed(j);
                                this->particles.push_back(particle);
                            }
                        }

                        this->goomba_manager->deleteGoomba(l);
                        break;
                    }
                }
            }
            return find_left + find_right - 2;
        }
        else if(!is_insert) {

            // Return to old position
            for(unsigned long int i = 0; i < cache_moved.size(); i++) {

                this->goomba_manager->getGoombas().at(cache_moved.at(i))->moveBackward();
            }
        }
        return 0;
    }

    // Goomba
    GoombaManager* goomba_manager;
    void updateGoombaManager() {

        // Update Goomba Manager
        this->goomba_manager->update();

        // Update Dead Leader
        this->updateDeadLeader();
        
        // Update Tense Music
        this->updateTenseMusic();

        // Update Goomba Collided
        this->updateGoombaCollided();

        // Update Game Over
        this->updateGameOver();
    }
    void updateGameOver() {

        if(this->goomba_manager->isGameOver()) {

            if(this->goomba_manager->getGoombas().empty()) {

                this->game_state = GAME_END;
                this->board->setIsBlink(false);
                this->mixer->playMusic(MUS_END);
            }
        }
    }
    void updateTenseMusic() {

        if(this->goomba_manager->isGameOver()) return;

        if(this->goomba_manager->isTense() && is_tense != 1) {

            this->is_tense = 1;
            this->mixer->playMusic(MUS_TENSE);
            this->board->setIsBlink(true);
        }
        else if(!this->goomba_manager->isTense() && is_tense == 1) {

            this->is_tense = -1;
            this->mixer->playMusic(this->music_list.at(chose_music));
            this->board->setIsBlink(false);
        }
    }
    void updateDeadLeader() {

        for(unsigned long int i = 0; i < this->goomba_manager->getGoombas().size(); i++) {

            if(!this->goomba_manager->getGoombas().at(i)->getLeader()) continue;
            
            long int goomba_progress = this->goomba_manager->getGoombas().at(i)->getProgress();
            long int goomba_progress_max = this->goomba_manager->getMaxProgressLeader(goomba_progress);
            if(goomba_progress != goomba_progress_max) continue;

            // Add Score
            float base_score = 200.0f;
            if(!this->goomba_manager->isGameOver()) this->boomba_ui->addScore(base_score * this->multiplier);

            // Add Multiplier
            this->multiplier = 1;
            this->multiplier_delay = 0;

            if(!this->goomba_manager->isGameOver()) {
                
                this->mixer->playSoundEffect(SFX_EXPLODE);
                
                Item item(this->goomba_manager->getGoombas().at(i)->getPosition(goomba_progress).x, this->goomba_manager->getGoombas().at(i)->getPosition(goomba_progress).y, this->window);
                item.setHSpeed(0);
                item.setVSpeed(-0.5);
                item.setMoveSpeed(8);
                item.setColor(C_CYAN);
                item.setIcon('E');

                this->items.push_back(item);
            }

            this->goomba_manager->deleteGoomba(i);

            break;
        }   
    }
    void updateGoombaCollided() {

        for(unsigned long int i = 0; i < this->goomba_manager->getGoombas().size(); i++) {

            if(!this->goomba_manager->getGoombas().at(i)->getFoundMatch()) continue;

            // Check If Not Leader
            bool is_leader = true;
            long int goomba_progress = this->goomba_manager->getGoombas().at(i)->getProgress();
            for(unsigned long int j = 0; j < this->goomba_manager->getGoombas().size(); j++) {

                if(this->goomba_manager->getGoombas().at(j)->getProgress() == goomba_progress - 1) {

                    is_leader = false;
                    break;
                }
            }
            if(is_leader) continue;

            // Remove Match
            float base_score = 20.0f;

            unsigned long int matches_destroyed = this->destroyMatch(this->goomba_manager->getGoombas().at(i)->getProgress(), this->goomba_manager->getGoombas().at(i)->getColor(), false);
            
            if(!matches_destroyed) break; 

            // Add Score
            if(!this->goomba_manager->isGameOver()) this->boomba_ui->addScore(base_score * (float)matches_destroyed * this->multiplier);

            // Add Multiplier
            this->multiplier += 0.1;
            this->multiplier_delay = 60;

            break;
        }
    }

    // Window
    WINDOW *window;

    // Name
    std::string enter_name;
    unsigned short int time_end;
    unsigned short int time_end_delay;

    // Map List
    std::vector <std::string> map_list;

    // Difficulty List
    std::vector <std::string> difficulty_list;

    // Multiplier
    float multiplier;
    unsigned long int multiplier_delay;
    void updateMultiplier() {

        if(this->multiplier_delay == 0) this->multiplier = 1;
        else this->multiplier_delay --;
    }

    // Menu
    long int menu_selection;
    long int map_selection;
    long int difficulty_selection;

    // Color
    void initializeColor() {

        start_color();
        init_pair(C_WHITE      , 15 , COLOR_BLACK);
        init_pair(C_RED        ,  9 , COLOR_BLACK);
        init_pair(C_GRAY       ,  8 , COLOR_BLACK);
        init_pair(C_GREEN      , 10 , COLOR_BLACK);
        init_pair(C_YELLOW     , 11 , COLOR_BLACK);
        init_pair(C_MAGENTA    , 13 , COLOR_BLACK);
        init_pair(C_CYAN       , 14 , COLOR_BLACK);
        init_pair(C_LIGHT_GRAY ,  7 , COLOR_BLACK);
        init_pair(C_BLUE       , 12 , COLOR_BLACK);
    }
    void colorSet(std::string color) {

        for(unsigned long int i = 0; i < color.size(); i++) {

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
            case 'B' :
                this->color_set.push_back(C_BLUE);
                break;
            case 'M' :
                this->color_set.push_back(C_MAGENTA);
                break;
            case 'W' :
                this->color_set.push_back(C_WHITE);
                break;
            }
        }
    }

    // States
    unsigned long int game_state;
    unsigned long int state_to_change;
    long int changing_state_time;
    void setState(unsigned long int game_state) {

        this->changing_state_time = 20;
        this->state_to_change = game_state;
    }
    void transitionState() {

        // Game State
        if(this->changing_state_time > 0) this->changing_state_time --;
        else if(this->changing_state_time == 0) {
            
            this->game_state = this->state_to_change;
            this->changing_state_time --;
            this->menu_selection = 0;
            this->difficulty_selection = 0;
            this->map_selection = 0;
        }
    }

    void gameReset() {

        this->score_list->addEntry(this->enter_name, this->boomba_ui->getScore());

        this->game_state = GAME_MENU;
        this->mixer->playMusic(MUS_MENU);

        this->enter_name = "";
        this->boomba_ui->setScore(0);

        this->time_end_delay = 60;
        this->time_end = 26;

        this->goomba_manager->clearPathPoints();
        this->goomba_manager->setGameOver(false);
        this->goomba_manager->setTense(false);
    }

    // Menu State
    void gameMenu() {

        if(this->game_state != GAME_MENU) return;

        if(this->changing_state_time >= 0) return;

        // Menu Navigation
        if(this->input == 'A') {
            
            this->mixer->playSoundEffect(SFX_SELECT);

            this->menu_selection --;
            if(this->menu_selection < 0) this->menu_selection = 2;
        }
        else if(this->input == 'B') {

            this->mixer->playSoundEffect(SFX_SELECT);
            
            this->menu_selection ++;
            if(this->menu_selection > 2) this->menu_selection = 0;
        }
    
        // Menu Enter
        if(this->input == 'x') {
            
            this->mixer->playSoundEffect(SFX_ENTER);

            switch(this->menu_selection) {
            
            case 0 : // PLAY
                this->setState(GAME_MENU_PLAY);
                break;

            case 1 : // HIGH SCORE
                this->setState(GAME_MENU_HIGHSCORE);
                break;

            case 2 : // QUIT
                this->setState(GAME_QUIT);
                break;

            default :
                break;
            }
        }
    }
    void gameMenuDraw() {

        if(this->game_state != GAME_MENU) return;

        std::vector <std::string> menu_entry = {
            "Play",
            "High Score",
            "Quit",
        };

        // Print Menu Selection
        for(unsigned long int i = 0; i < menu_entry.size(); i++) {

            if((unsigned long int)this->menu_selection == i) {
            
                if(this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window, 7 + (i * 3), "*  " + menu_entry.at(i) + "  *", C_LIGHT_GRAY);
                else KornDraw::drawTextCenter(this->window, 7 + (i * 3), "->  " + menu_entry.at(i) + "  <-", C_LIGHT_GRAY);
            }
        }

        // Print Title
        KornDraw::drawTextCenter(this->window, 2, "#----------------#", C_LIGHT_GRAY);
        KornDraw::drawTextCenter(this->window, 3, "|   BoombaGame   |", C_LIGHT_GRAY);       
        KornDraw::drawTextCenter(this->window, 4, "#----------------#", C_LIGHT_GRAY);
        KornDraw::drawTextCenter(this->window, 3, "BoombaGame", C_WHITE);   

        // Print Name
        KornDraw::drawText(this->window, 3, 18, "Made by Korn (64010009)", C_LIGHT_GRAY);

        // Print Key
        KornDraw::drawText(this->window, 29, 17, "    X : OK", C_LIGHT_GRAY);
        KornDraw::drawText(this->window, 29, 18, "Arrow : Navigation", C_LIGHT_GRAY);

        // Print Menu
        KornDraw::drawTextCenter(this->window,  7, menu_entry.at(0), C_GREEN);
        KornDraw::drawTextCenter(this->window, 10, menu_entry.at(1), C_YELLOW);
        KornDraw::drawTextCenter(this->window, 13, menu_entry.at(2), C_RED);
        
        if(this->menu_selection == 0 && this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window,  7, menu_entry.at(0), C_GRAY);
        if(this->menu_selection == 1 && this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window, 10, menu_entry.at(1), C_GRAY);
        if(this->menu_selection == 2 && this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window, 13, menu_entry.at(2), C_GRAY);
    }

    // Menu Play State
    void gameMenuPlay() {

        if(this->game_state != GAME_MENU_PLAY) return;

        // Menu Navigation
        if(this->input == 'A') {
            
            this->mixer->playSoundEffect(SFX_SELECT);

            this->menu_selection --;
            if(this->menu_selection < 0) this->menu_selection = 3;
        }
        else if(this->input == 'B') {

            this->mixer->playSoundEffect(SFX_SELECT);

            this->menu_selection ++;
            if(this->menu_selection > 3) this->menu_selection = 0;
        }

        // Menu Enter
        switch(this->menu_selection) {
        
        case 0 : // MAP SELECTION
            if(this->input == 'D') {

                this->mixer->playSoundEffect(SFX_CHOOSE);

                this->map_selection --;
                if(map_selection < 0) map_selection = 3;
            }
            else if(this->input == 'C') {

                this->mixer->playSoundEffect(SFX_CHOOSE);

                this->map_selection ++;
                if(map_selection > 3) map_selection = 0;
            }
            break;

        case 1 : // DIFFICULTY SELECTION
            if(this->input == 'D') {

                this->mixer->playSoundEffect(SFX_CHOOSE);

                this->difficulty_selection --;
                if(difficulty_selection < 0) difficulty_selection = 4;
            }
            else if(this->input == 'C') {

                this->mixer->playSoundEffect(SFX_CHOOSE);

                this->difficulty_selection ++;
                if(difficulty_selection > 4) difficulty_selection = 0;
            }
            break;

        case 2 : // START
            if(this->input == 'x') {

                this->mixer->playSoundEffect(SFX_ENTER);

                this->setState(GAME_RUN);

                // Load Difficulty
                switch(this->difficulty_selection) {
                case EASY :
                    this->colorSet("RGY");
                    this->goomba_manager->setColorSet("RGY");

                    break;

                case NORMAL :
                    this->colorSet("RGYB");
                    this->goomba_manager->setColorSet("RGYB");

                    break;

                case HARD :
                    this->colorSet("RGYB");
                    this->goomba_manager->setColorSet("RGYB");

                    break;

                case EXTREMES :
                    this->colorSet("RGYBM");
                    this->goomba_manager->setColorSet("RGYBM");

                    break;

                case IMPOSSIBLE :
                    this->colorSet("RGYBMW");
                    this->goomba_manager->setColorSet("RGYBMW");

                    break;
                }

                // Load Map
                switch(this->map_selection) {
                case ROAD:

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
                    break;

                case SPIRAL:

                    this->goomba_manager->addPath(30, 8);
                    this->goomba_manager->addPath(14, 8);
                    this->goomba_manager->addPath(14, 5);
                    this->goomba_manager->addPath(35, 5);
                    this->goomba_manager->addPath(35, 11);
                    this->goomba_manager->addPath(8 , 11);
                    this->goomba_manager->addPath(8 , 2);
                    this->goomba_manager->addPath(40, 2);
                    this->goomba_manager->addPath(40, 14);
                    this->goomba_manager->addPath(8 , 14);
                    break;

                case STAIRS:
                 
                    break;

                case MOUNTAIN:
                 
                    break;
                }
                this->goomba_manager->calculatePath();

                this->chose_music = 1;
                //this->chose_music = KornRandom::randomInt(4);
                this->mixer->playMusic(this->music_list.at(chose_music));

                this->boomba->setColorSet(this->color_set);
                this->boomba->initRandomColor();
            }
            break;

        case 3 : // BACK
            if(this->input == 'x') {

                this->mixer->playSoundEffect(SFX_ENTER);

                this->setState(GAME_MENU);
            }
            break;

        default : 
            break;
        }
    }
    void gameMenuPlayDraw() {

        if(this->game_state != GAME_MENU_PLAY) return;

        std::vector <std::string> menu_entry = {
            "Maps",
            "Difficulty",
            "Play",
            "Back",
        };

        // Print Menu Selection
        for(unsigned long int i = 0; i < menu_entry.size(); i++) {
            
            if((unsigned long int)this->menu_selection == i) {
                if(this->menu_selection == 0) {

                    KornDraw::drawTextCenter(this->window, 7 + (i * 3), "<-  " + this->map_list.at(this->map_selection) + "  ->", C_LIGHT_GRAY);
                }
                if(this->menu_selection == 1) {

                    KornDraw::drawTextCenter(this->window, 7 + (i * 3), "<-  " + this->difficulty_list.at(this->difficulty_selection) + "  ->", C_LIGHT_GRAY);
                }
                if(this->menu_selection == 2 || this->menu_selection == 3) {
                    
                    if(this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window, 7 + (i * 3), "*  " + menu_entry.at(i) + "  *", C_LIGHT_GRAY);
                    else KornDraw::drawTextCenter(this->window, 7 + (i * 3), "->  " + menu_entry.at(i) + "  <-", C_LIGHT_GRAY);
                }
            }
        }

        // Print Title
        KornDraw::drawTextCenter(this->window, 2, "#----------------#", C_LIGHT_GRAY);
        KornDraw::drawTextCenter(this->window, 3, "|     Option     |", C_LIGHT_GRAY);       
        KornDraw::drawTextCenter(this->window, 4, "#----------------#", C_LIGHT_GRAY);
        KornDraw::drawTextCenter(this->window, 3, "Option", C_WHITE);

        // Print Name
        KornDraw::drawText(this->window, 3, 18, "Made by Korn (64010009)", C_LIGHT_GRAY);

        // Print Key
        KornDraw::drawText(this->window, 29, 16, "    X : Shoot", C_LIGHT_GRAY);
        KornDraw::drawText(this->window, 29, 17, "    C : Swap", C_LIGHT_GRAY);
        KornDraw::drawText(this->window, 29, 18, "Arrow : Navigation", C_LIGHT_GRAY);

        // Print Menu
        KornDraw::drawTextCenter(this->window,  6, "Maps", C_WHITE);
        KornDraw::drawTextCenter(this->window,  7, this->map_list.at(this->map_selection), C_YELLOW);

        KornDraw::drawTextCenter(this->window,  9, "Difficulty", C_WHITE);
        KornDraw::drawTextCenter(this->window, 10, this->difficulty_list.at(this->difficulty_selection), C_GREEN);

        if(this->difficulty_selection == 0) {
            KornDraw::drawTextCenter(this->window, 10, this->difficulty_list.at(this->difficulty_selection), C_GREEN);
        }
        if(this->difficulty_selection == 1) {
            KornDraw::drawTextCenter(this->window, 10, this->difficulty_list.at(this->difficulty_selection), C_YELLOW);
        }
        if(this->difficulty_selection == 2) {
            KornDraw::drawTextCenter(this->window, 10, this->difficulty_list.at(this->difficulty_selection), C_RED);
        }
        if(this->difficulty_selection == 3) {
            KornDraw::drawTextCenter(this->window, 10, this->difficulty_list.at(this->difficulty_selection), C_MAGENTA);
        }
        if(this->difficulty_selection == 4) {
            KornDraw::drawText(this->window, 19, 10, this->difficulty_list.at(this->difficulty_selection), C_BLUE);
        }

        KornDraw::drawTextCenter(this->window, 13, "Play", C_CYAN);

        KornDraw::drawTextCenter(this->window, 16, "Back", C_RED);

        if(this->menu_selection == 2 && this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window, 13, "Play", C_GRAY);
        if(this->menu_selection == 3 && this->changing_state_time >= 0) KornDraw::drawTextCenter(this->window, 16, "Back", C_GRAY);
    }

    // Menu Highscore State
    void gameMenuHighscore() {

        if(this->game_state != GAME_MENU_HIGHSCORE) return;
    }
    void gameMenuHighscoreDraw() {

        if(this->game_state != GAME_MENU_HIGHSCORE) return;
    }

    // Game Run
    void gameRun() {

        if(this->game_state != GAME_RUN) return;

        if(this->input == 'e') this->goomba_manager->setGameOver(true); /* ! Temp */

        // Close Game
        if(this->input == 'q') this->is_running = false;

        // Update Particles
        this->updateParticles();

        // Update Boomba
        this->updateBoomba();

        // Update Boomba UI
        this->boomba_ui->update(this->input);

        // Update Multiplier
        this->updateMultiplier();

        // Update Fruit
        this->updateFruits();

        // Update Goomba Manager
        this->updateGoombaManager();

        // Update Items
        this->updateItems();  
    }
    void gameRunDraw() {

        if(this->game_state != GAME_RUN) return;

        // Draw Particles
        this->drawParticles();

        // Draw Goomba
        this->goomba_manager->draw();

        // Draw Boomba
        this->boomba->draw();

        // Draw Fruit
        this->drawFruits();

        // Draw UI
        this->boomba_ui->draw();

        // Draw Items
        this->drawItems();
    }

    // Game End
    void gameEnd() {

        if(this->game_state != GAME_END) return;

        // Decrease Time
        if(this->time_end_delay == 0) {

            this->time_end_delay = 60;
            if(this->time_end > 0) this->time_end --;
            else this->gameReset();
        }
        else this->time_end_delay --;

        // Enter name
        if((this->input >= 'A' && this->input <= 'Z') || (this->input >= 'a' && this->input <= 'z')) {

            if(this->enter_name.size() < 10) this->enter_name.push_back(this->input);
        }

        // Delete
        if(this->input == 127) {

            if(this->enter_name.size() > 0) this->enter_name.erase(this->enter_name.end() - 1);
        }

        // Enter
        if(this->input == 10) this->gameReset();
    }
    void gameEndDraw() {

        if(this->game_state != GAME_END) return;

        // Print Title
        KornDraw::drawTextCenter(this->window, 2, "#----------------#", C_LIGHT_GRAY);
        KornDraw::drawTextCenter(this->window, 3, "|    GameOver    |", C_LIGHT_GRAY);       
        KornDraw::drawTextCenter(this->window, 4, "#----------------#", C_LIGHT_GRAY);
        KornDraw::drawTextCenter(this->window, 3, "GameOver");

        KornDraw::drawTextCenter(this->window, 7, "New Highscore!", C_YELLOW);

        KornDraw::drawText(this->window, 4, 11, "Your score");
        KornDraw::drawText(this->window, 15, 11, std::to_string(this->boomba_ui->getScore()), C_GREEN);
        
        KornDraw::drawText(this->window, 4, 14, "Enter your name");
        KornDraw::drawText(this->window, 4, 15, this->enter_name + "_", C_YELLOW);

        KornDraw::drawTextCenter(this->window, 17, this->time_end, C_WHITE);
    }

    // Game Quit
    void gameQuit() {

        if(this->game_state != GAME_QUIT) return;

        this->is_running = false;
        return;
    }   

    // Game Functions
    void updateState() {

        // Get Input
        this->input = this->board->getInput();
        
        // State Transition
        this->transitionState();

        // Run Game States
        this->gameMenu();
        this->gameMenuPlay();
        this->gameMenuHighscore();
        this->gameRun();
        this->gameEnd();   
        this->gameQuit();     
    }
    void reDraw() {
        
        // Clear Buffer
        this->board->boardClear();

        // Draw Game States
        this->gameMenuDraw();
        this->gameMenuPlayDraw();
        this->gameMenuHighscoreDraw();
        this->gameRunDraw();
        this->gameEndDraw();  

        // Put Buffer To Console
        this->board->boardRefresh();
    }

public:

    // Constructor and Destructor
    BoombaGame() {

        // Score List
        this->score_list = new ScoreList("highscore.txt");
        this->score_list->loadFile();

        // Name
        this->time_end = 26;
        this->time_end_delay = 60;
        this->enter_name = "";

        // Colors
        this->initializeColor();

        // Mixer
        this->mixer = new Mixer(48000);
        this->loadAudio();

        // Board
        this->board = new BoombaBoard(SCREEN_WIDTH, SCREEN_HEIGHT);
        
        // Window
        this->window = this->board->getWindow();

        // Boomba UI
        this->boomba_ui = new BoombaUI(this->window);

        // Goomba
        this->goomba_manager = new GoombaManager(this->window, this->mixer);
        
        // Boomba
        this->boomba = new Boomba(16, 17, this->window);
        
        // Game State
        this->game_state = GAME_MENU;
        this->state_to_change = GAME_MENU;
        this->changing_state_time = -1;

        // Map List
        this->map_list = {
            "Road",
            "Spiral",
            "Stairs",
            "Mountain",
        };

        // Diffuculty List
        this->difficulty_list = {
            "Easy",
            "Normal",
            "Hard",
            "Extremes",
            "Impossible",
        };

        // Menu
        this->menu_selection = 0;
        this->difficulty_selection = 0;
        this->map_selection = 0;

        // Game
        this->is_running = true;
        this->is_tense = false;
        this->chose_music = 0;

        // Multiplier
        this->multiplier_delay = 0;
        this->multiplier = 1;
    }
    ~BoombaGame() {

        // Save
        this->score_list->saveFile();

        // Clear Memory
        delete this->score_list;
        delete this->mixer;
        delete this->boomba;
        delete this->boomba_ui;
        delete this->goomba_manager;
        delete this->board;
    }

    // Run the game
    void run() {

        this->updateState();
        this->reDraw();
    }    
    
    // Accessors
    bool isRunning() {

        return this->is_running;
    }
};