//
// Created by victor_moraes on 22/10/24.
//

#include "Music.h"

Music::Music() : music(nullptr) {}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    Stop();
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    if (Mix_PlayingMusic()) {
        Mix_FadeOutMusic(msToStop);
    }
}

void Music::Open(std::string file) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
    }

    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        printf("Failed to load music: %s\n", Mix_GetError());
    }
}

bool Music::IsOpen() {
    return (music != nullptr);
}