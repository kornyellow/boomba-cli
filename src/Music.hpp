#pragma once

// Includes

class Music {
private:
    
    Mix_Music* mix_music;
    std::string music_path;

public:

    ~Music() {

        Mix_FreeMusic(this->mix_music);
        this->mix_music = NULL;
    }

    void play() {

        if(IS_PLAY_MUSIC) Mix_PlayMusic(this->mix_music, -1);
    }

    bool init(std::string music_path) {

        this->music_path = music_path;
        this->mix_music = Mix_LoadMUS(this->music_path.c_str());

        if(this->mix_music == NULL) return false;
        return true;
    }

    std::string getPath() {

        return this->music_path;
    }
};