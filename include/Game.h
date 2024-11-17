//
// Created by victor_moraes on 22/10/24.
//

#pragma once

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdexcept>
#include "State.h"

#define GAME_TITLE "Victor André de Moraes - 211026664"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

class Game {
private:
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    Game(const std::string& title, int width, int height);

public:
    ~Game();

    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
};


#endif //GAME_GAME_H
