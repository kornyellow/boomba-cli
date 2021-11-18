#pragma once

// Includes
#include "Mixer.hpp"
#include "GoombaManager.hpp"
#include "BoombaBoard.hpp"
#include "BoombaUI.hpp"
#include "Boomba.hpp"
#include "Fruit.hpp"

class BoombaGame {
private:

    // Game
    BoombaBoard* board;

    // Mixer
    Mixer* mixer;
    
    bool is_running;
    chtype input;

    // Boomba UI
    BoombaUI *boomba_ui;
    
    // Boomba
    Boomba *boomba;
    std::vector <Fruit> fruits;
    std::vector <unsigned short int> color_set;

    // Goomba
    GoombaManager *goomba_manager;

    // Window
    WINDOW *window;

    // Map List
    std::vector <std::string> map_list;

    // Difficulty List
    std::vector <std::string> difficulty_list;

    // Multiplier
    float multiplier;
    long int multiplier_delay;

    // Menu
    long int menu_selection;
    long int map_selection;
    long int difficulty_selection;

    // Load Audio
    void loadAudio() {

        // Music
        this->mixer->addMusic(MUS_MENU);
        this->mixer->addMusic(MUS_HIGH);
        this->mixer->addMusic(MUS_GAME_1);
        this->mixer->addMusic(MUS_GAME_2);
        this->mixer->addMusic(MUS_GAME_3);
        this->mixer->addMusic(MUS_GAME_4);
        this->mixer->addMusic(MUS_GAME_5);

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
    }   

    // Initialize
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

    // Game Functions
    unsigned long int game_state;
    long int changing_state;
    unsigned long int state_to_change;

    void gameMenu() {

        if(this->game_state != GAME_MENU) return;

        if(this->changing_state >= 0) return;

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
            
                if(this->changing_state >= 0) KornDraw::drawTextCenter(this->window, 7 + (i * 3), "*  " + menu_entry.at(i) + "  *", C_LIGHT_GRAY);
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
        
        if(this->menu_selection == 0 && this->changing_state >= 0) KornDraw::drawTextCenter(this->window,  7, menu_entry.at(0), C_GRAY);
        if(this->menu_selection == 1 && this->changing_state >= 0) KornDraw::drawTextCenter(this->window, 10, menu_entry.at(1), C_GRAY);
        if(this->menu_selection == 2 && this->changing_state >= 0) KornDraw::drawTextCenter(this->window, 13, menu_entry.at(2), C_GRAY);
    }

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
                    this->goomba_manager->addGoombaSet("RGYBRGYBRGYBRGYBRGYBRGYB#");

                    break;

                case HARD :
                    this->colorSet("RGYB");
                    this->goomba_manager->addGoombaSet("RGYBRGYBRGYBRGYBRGYBRGYB#");

                    break;

                case EXTREMES :
                    this->colorSet("RGYBM");
                    this->goomba_manager->addGoombaSet("RGYBMRGYBMRGYBMRGYBMRGYBMRGYBM#");

                    break;

                case IMPOSSIBLE :
                    this->colorSet("RGYBMW");
                    this->goomba_manager->addGoombaSet("RGYBMWRGYBMWRGYBMWRGYBMWRGYBMWRGYBMW#");

                    break;
                }

                // Load Map
                switch(this->map_selection) {
                case ROAD:

                    break;

                case SPIRAL:
                 
                    break;

                case STAIRS:
                 
                    break;

                case MOUNTAIN:
                 
                    break;
                }

                std::string music_list[5] = {
                    MUS_GAME_1,
                    MUS_GAME_2,
                    MUS_GAME_3,
                    MUS_GAME_4,
                    MUS_GAME_5
                };
                this->mixer->playMusic(music_list[KornRandom::randomInt(4)]);

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
                    
                    if(this->changing_state >= 0) KornDraw::drawTextCenter(this->window, 7 + (i * 3), "*  " + menu_entry.at(i) + "  *", C_LIGHT_GRAY);
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

        if(this->menu_selection == 2 && this->changing_state >= 0) KornDraw::drawTextCenter(this->window, 13, "Play", C_GRAY);
        if(this->menu_selection == 3 && this->changing_state >= 0) KornDraw::drawTextCenter(this->window, 16, "Back", C_GRAY);
    }

    void gameMenuHighscore() {

        if(this->game_state != GAME_MENU_HIGHSCORE) return;
    }
    void gameMenuHighscoreDraw() {

        if(this->game_state != GAME_MENU_HIGHSCORE) return;
    }

    void gameRun() {

        if(this->game_state != GAME_RUN) return;

        // Close Game
        if(this->input == 'q') this->is_running = false;

        // Shoot Fruit
        if(this->input == 'x' && this->fruits.empty()) { 

            this->mixer->playSoundEffect(SFX_SHOOT);

            unsigned short int fruit_color = this->boomba->fruitShoot();

            Fruit fruit(this->boomba->getX() + 3, this->boomba->getY() - 1, this->window);
            fruit.setFruitColor(fruit_color);
            this->fruits.push_back(fruit);
        }

        // Swap Fruit
        if(this->input == 'c') {

            this->boomba->fruitSwap();
        }

        // Update Boomba
        this->boomba->update(this->input);
        if(!this->goomba_manager->getAllColor().empty() && this->goomba_manager->getGoombaSet().empty()) this->boomba->setColorSet(this->goomba_manager->getAllColor());

        // Update Multiplier
        if(this->multiplier_delay < 0) this->multiplier = 1;
        else this->multiplier_delay --;

        // Update Boomba Scope
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

        // Update Boomba UI
        this->boomba_ui->update(this->input);

        // Update Dead Leader
        for(unsigned long int i = 0; i < this->goomba_manager->getGoombas().size(); i++) {

            if(!this->goomba_manager->getGoombas().at(i)->getLeader()) continue;
            
            long int goomba_progress = this->goomba_manager->getGoombas().at(i)->getProgress();
            long int goomba_progress_max = this->goomba_manager->getMaxProgressLeader(goomba_progress);
            if(goomba_progress != goomba_progress_max) continue;

            this->goomba_manager->deleteGoomba(i);

            // Add Score
            float base_score = 200.0f;
            this->boomba_ui->addScore(base_score * this->multiplier);

            // Add Multiplier
            this->multiplier = 1;
            this->multiplier_delay = 0;

            this->mixer->playSoundEffect(SFX_EXPLODE);

            break;
        }   

        // Update Fruit
        for(unsigned long int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).update();

            // Update Fruit Out Of Bound
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
                    this->boomba_ui->addScore(base_score * (float)matches_destroyed);

                    // Remove Fruit
                    this->fruits.erase(this->fruits.begin() + i);

                    break;
                }
            }
        }

        // Update Collided Goombas
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
            
            // Add Score
            this->boomba_ui->addScore(base_score * (float)matches_destroyed * this->multiplier);

            // Add Multiplier
            this->multiplier += 0.1;
            this->multiplier_delay = 60;

            break;
        }

        // Update Goomba
        this->goomba_manager->update();
    }
    void gameRunDraw() {

        if(this->game_state != GAME_RUN) return;

        // Draw Goomba
        this->goomba_manager->draw();

        // Draw Boomba
        this->boomba->draw();

        // Draw Fruit
        for(unsigned long int i = 0; i < this->fruits.size(); i++) {

            this->fruits.at(i).draw();
        }

        // Draw UI
        this->boomba_ui->draw();
    }

    void gameEnd() {

        if(this->game_state != GAME_END) return;
    }
    void gameEndDraw() {

        if(this->game_state != GAME_END) return;
    }

    void gameQuit() {

        if(this->game_state != GAME_QUIT) return;

        this->is_running = false;
        return;
    }   

public:

    BoombaGame() {

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
        this->changing_state = -1;

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

        this->is_running = true;
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

    // Fruit
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
            goomba->setInsertDelay(10);
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

                        this->goomba_manager->deleteGoomba(l);
                        
                        break;
                    }
                }
            }
            return find_left + find_right - 2;
        }
        if(!is_insert) {

            // Return to old position
            for(unsigned long int i = 0; i < cache_moved.size(); i++) {

                this->goomba_manager->getGoombas().at(cache_moved.at(i))->moveBackward();
            }
        }
        return 0;
    }

    // States
    void setState(unsigned long int game_state) {

        this->changing_state = 10;
        this->state_to_change = game_state;
    }

    // Functions
    void updateState() {

        // Get Input
        this->input = this->board->getInput();
        
        // Game State
        if(this->changing_state > 0) this->changing_state --;
        else if(this->changing_state == 0) {
            
            this->game_state = this->state_to_change;
            this->changing_state --;
            this->menu_selection = 0;
            this->difficulty_selection = 0;
            this->map_selection = 0;
        }

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
    bool isRunning() {

        return this->is_running;
    }
};