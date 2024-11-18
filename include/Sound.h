//
// Created by victor_moraes on 17/11/24.
//

#ifndef GAME_SOUND_H
#define GAME_SOUND_H

#pragma once

#include <string>
#include "SDL_mixer.h"
#include "SDL.h"

class Sound {
public:
    Sound();
    explicit Sound(const std::string& file);
    ~Sound();

    void Play(int times = 1);
    void Stop();
    void Open(const std::string& file);
    [[nodiscard]] bool IsOpen() const;

private:
    Mix_Chunk* chunk;
    int channel;
};

#endif // GAME_SOUND_H

