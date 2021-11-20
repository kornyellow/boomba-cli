#pragma once

// Includes

class Score {
private:

    std::string name;
    unsigned long score;
    
public:

    Score(std::string name, unsigned long score) {

        this->name = name;
        this->score = score;
    }

    void setName(std::string name) {

        this->name = name;
    }
    std::string getName() {

        return this->name;
    }

    void setScore(unsigned long score) {

        this->score = score;
    }
    unsigned long getScore() {

        return this->score;
    }
};