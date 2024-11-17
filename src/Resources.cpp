//
// Created by victor_moraes on 17/11/24.
//

#include "Resources.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(const std::string& file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture* texture = IMG_LoadTexture(SDL_GetRenderer(SDL_GetWindowFromID(1)), file.c_str());
    if (texture) {
        imageTable[file] = texture;
    }
    return texture;
}

Mix_Music* Resources::GetMusic(const std::string& file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (music) {
        musicTable[file] = music;
    }
    return music;
}

Mix_Chunk* Resources::GetSound(const std::string& file) {

    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if (sound) {
        soundTable[file] = sound;
    }
    return sound;
}

void Resources::ClearImages() {
    for (auto& entry : imageTable) {
        SDL_DestroyTexture(entry.second);
    }
    imageTable.clear();
}

void Resources::ClearMusics() {
    for (auto& entry : musicTable) {
        Mix_FreeMusic(entry.second);
    }
    musicTable.clear();
}

void Resources::ClearSounds() {
    for (auto& entry : soundTable) {
        Mix_FreeChunk(entry.second);
    }
    soundTable.clear();
}
