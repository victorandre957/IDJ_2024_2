    //
// Created by victor_moraes on 22/10/24.
//

#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Sprite.h"
#include "Music.h"
#include "SDL.h"

class State {
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

private:
    Sprite bg;
    Music music;
    bool quitRequested;
};


#endif //GAME_STATE_H
