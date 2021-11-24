#pragma once

// Includes

class BoombaUI {
private:

    // Window
    WINDOW *window;

    // Score
    unsigned long int score;
    unsigned long int score_show;

public:

    BoombaUI(WINDOW* window) {

        // Window
        this->window = window;

        // Score
        this->score = 0;
        this->score_show = 0;
    }
    ~BoombaUI() {

    }

    // Functions
    void update(chtype character) {

        // Update Score
        this->score_show += round((this->score - this->score_show) / 10.0f);
    }
    void draw() {

        // Draw Score
        KornDraw::drawText(this->window, 5, 0, " SCORE ");
        
        std::string score_string = std::to_string(score_show);
        while(score_string.size() < 8) score_string.insert(score_string.begin(), '0');
        score_string.push_back(' ');

        for(unsigned long int i = 0; i < score_string.size(); i++) {
            
            KornDraw::drawCharacter(this->window, 12 + i, 0, score_string.at(i));
        }
    }

    // Score
    void addScore(unsigned long int score) {

        this->score += score;
        if(this->score > 99999999) this->score = 99999999;
    }
    void setScore(unsigned long int score) {

        this->score = score;
        this->score_show = 0;
    }
    unsigned long int getScore() {

        return this->score;
    }
};