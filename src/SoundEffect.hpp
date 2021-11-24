#pragma once

// Includes

class SoundEffect {
private:
    
    Mix_Chunk* mix_chunk;
    std::string sound_effect_path;

public:

    ~SoundEffect() {

        Mix_FreeChunk(this->mix_chunk);
        this->mix_chunk = NULL;
    }

    void play() {

        if(IS_PLAY_SOUND_EFFECT) Mix_PlayChannel(-1, this->mix_chunk, 0);
    }

    bool init(std::string sound_effect_path) {

        this->sound_effect_path = sound_effect_path;
        this->mix_chunk = Mix_LoadWAV(this->sound_effect_path.c_str());
        
        if(this->mix_chunk == NULL) return false;
        return true;
    }

    std::string getPath() {

        return this->sound_effect_path;
    }
};