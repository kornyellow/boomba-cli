#pragma once

// Includes

class BoombaUI {
private:

    // Window
    WINDOW *window;

    // Score
    int score;

public:

    BoombaUI(WINDOW* window) {

        // Window
        this->window = window;

        // Score
        this->score = 0;
    }
    ~BoombaUI() {

    }

    // Functions
    void update(chtype character) {

    }
    void draw() {

        // Draw Score
        KornDraw::drawText(this->window, 5, 0, " SCORE ");
        
        std::string score_string = std::to_string(score);
        while(score_string.size() < 8) score_string.insert(score_string.begin(), '0');
        score_string.push_back(' ');

        for(int i = 0; i < score_string.size(); i++) {
            
            KornDraw::drawCharacter(this->window, 12 + i, 0, score_string.at(i));
        }
    }
};