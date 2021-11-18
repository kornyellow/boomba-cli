#pragma once

// Includes
#include "Music.hpp"
#include "SoundEffect.hpp"

class Mixer {
public:

    std::vector <Music*> musics;
    unsigned short int empty_music_index;
    std::vector <SoundEffect*> sound_effects;
    unsigned short int empty_sound_effect_index;
    unsigned short int max_entry;

    Music* getMusicByPath(std::string music_path) {

        for(unsigned short int i = 0; i < this->max_entry; i++) {

            if(music_path == this->musics.at(i)->getPath()) {

                return this->musics.at(i);
            }
        }
        return NULL;
    }

    SoundEffect* getSoundEffectByPath(std::string sound_effect_path) {

        for(unsigned short int i = 0; i < this->max_entry; i++) {

            if(sound_effect_path == this->sound_effects.at(i)->getPath()) {

                return this->sound_effects.at(i);
            }
        }
        return NULL;
    }

public:

    Mixer(unsigned long int frequenzy) {

        this->empty_music_index = 0;
        this->empty_sound_effect_index = 0;

        this->max_entry = 100;

        this->musics.reserve(this->max_entry);
        for(unsigned short int i = 0; i < this->max_entry; i++) this->musics.emplace_back(new Music());

        this->sound_effects.reserve(this->max_entry);
        for(unsigned short int i = 0; i < this->max_entry; i++) this->sound_effects.emplace_back(new SoundEffect());

        Mix_OpenAudio(frequenzy, MIX_DEFAULT_FORMAT, 2, 2048);
    }
    ~Mixer() {

        Mix_HaltMusic();

        for(unsigned short int i = 0; i < this->max_entry; i++) delete this->musics.at(i);
        for(unsigned short int i = 0; i < this->max_entry; i++) delete this->sound_effects.at(i);

        Mix_Quit();
    }

    bool addMusic(std::string music_path) {

        bool is_success = false;

        if(this->empty_music_index == this->max_entry) return false;
        is_success = this->musics.at(this->empty_music_index)->init(music_path);
        if(!is_success) return false;
        this->empty_music_index ++;

        return true;
    }
    bool addSoundEffect(std::string sound_effect_path) {

        bool is_success = false;

        if(this->empty_sound_effect_index == this->max_entry) return false;
        is_success = this->sound_effects.at(this->empty_sound_effect_index)->init(sound_effect_path);
        if(!is_success) return false;
        this->empty_sound_effect_index ++;

        return true;
    }

    void playSoundEffect(std::string sound_effect_path) {

        this->getSoundEffectByPath(sound_effect_path)->play();
    }

    void playMusic(std::string music_path) {

        Mix_HaltMusic();
        this->getMusicByPath(music_path)->play();
    }
    void stopMusic() {

        Mix_PauseMusic();
    }
};