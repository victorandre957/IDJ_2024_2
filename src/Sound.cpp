//
// Created by victor_moraes on 17/11/24.
//

#include "Sound.h"

Sound::Sound() : chunk(nullptr), channel(-1) {}

Sound::Sound(const std::string& file) : chunk(nullptr), channel(-1) {
    Open(file);
}

Sound::~Sound() {
    Stop();
    if (chunk) {
        Mix_FreeChunk(chunk);
    }
}

void Sound::Play(int times) {
    if (chunk) {
        channel = Mix_PlayChannel(-1, chunk, times - 1);
    }
}

void Sound::Stop() {
    if (channel != -1) {
        Mix_HaltChannel(channel);
        channel = -1;
    }
}

void Sound::Open(const std::string& file) {
    chunk = Mix_LoadWAV(file.c_str());
    if (!chunk) {
        SDL_Log("Failed to load sound: %s", Mix_GetError());
    }
}

bool Sound::IsOpen() const {
    return chunk != nullptr;
}

