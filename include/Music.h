//
// Created by victor_moraes on 22/10/24.
//

#ifndef GAME_MUSIC_H
#define GAME_MUSIC_H

#include <string>
#include "SDL_mixer.h"

class Music {
public:
    Music();
    Music(std::string file);
    ~Music();

    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen();

private:
    Mix_Music* music;
};


#endif //GAME_MUSIC_H
