//
// Created by victor_moraes on 22/10/24.
//

#include "State.h"

State::State() : bg("./public/img/Background.png"), quitRequested(false)  {}

void State::LoadAssets() {
    music.Open("./public/audio/BGM.wav");
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

    if (music.IsOpen() && Mix_PlayingMusic() == 0) {
        music.Play(-1);
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}