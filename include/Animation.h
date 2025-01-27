//
// Created by victor_moraes on 03/11/24.
//

#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H

#pragma once

#include "SDL.h"

class Animation {
public:
    Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip;
};

#endif //GAME_ANIMATION_H
