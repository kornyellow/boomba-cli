#pragma once

// Includes
#include "Score.hpp"

class ScoreList {
private:

    std::string file_name;
    std::vector <Score> score_list;

    bool addScoreEntry(Score player) {

        for(auto entry = this->score_list.begin(); entry != this->score_list.end(); entry++) {
            
            if (player.getName() == entry->getName() && player.getScore() < entry->getScore()) {

                return false;
            }
            if (player.getName() == entry->getName() && player.getScore() != entry->getScore()) {

                this->score_list.erase(entry);
                
                break;
            }
        }

        for (auto entry = this->score_list.begin(); entry != this->score_list.end(); entry++) {

            if (player.getScore() == entry->getScore() && player.getName() == entry->getName()) {

                return false;
            }
            
            if (player.getScore() > entry->getScore()) {
                
                score_list.insert(entry, player);

                return true;
            }
        }
        
        score_list.push_back(player);

        return true;
    }

public:

    ScoreList(std::string file_name) {

        this->file_name = file_name;
    }
    
    bool loadFile() {

        std::ifstream file_read(this->file_name);

        std::string read_string;
        std::string read_name;
        std::string read_score;

        bool is_read_name = true;
        bool is_load_success = false;
        
        while(std::getline(file_read, read_string)) {
            
            if(is_read_name) {
                
                read_name = read_string;
            }
            else { 

                read_score = read_string;

                unsigned long read_score_int;
                std::stringstream ss;
                ss << read_score;
                ss >> read_score_int;

                Score score(read_name, read_score_int);
                this->score_list.push_back(score);
            }

            is_read_name = !is_read_name;

            is_load_success = true;
        }

        file_read.close();

        if(is_load_success) return true;
        return false;
    }
    void saveFile() {

        std::ofstream file_save(this->file_name);

        for(auto entry : this->score_list) {

            file_save << entry.getName() << std::endl;
            file_save << entry.getScore() << std::endl;
        }
        file_save.close();
    }
    
    bool addEntry(Score player) {

        return this->addScoreEntry(player);
    }
    bool addEntry(std::string name, unsigned long score) {

        return this->addScoreEntry(Score(name, score));
    }
    void removeEntry(unsigned long index) {

        if(!this->score_list.size()) return;

        if(index >= this->score_list.size()) {
            
            throw "- Error : Trying to reach and remove an entry that doesn't exists!";
        }

        this->score_list.erase(this->score_list.begin() + index);
    }
    Score getEntry(unsigned long index) {

        if(index >= this->score_list.size()) {
            
            throw "- Error : Trying to reach an entry that doesn't exists!";
        }

        return this->score_list.at(index);
    }

    std::string getFileName() {

        return this->file_name;
    }

    std::vector <Score> get() {

        return this->score_list;
    }
    void set(std::vector <Score> score_list) {

        this->score_list = score_list;
    }
    unsigned long clear() {

        unsigned long removed_entry = this->score_list.size();

        this->score_list.clear();

        return removed_entry;
    }
};