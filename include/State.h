    //
// Created by victor_moraes on 22/10/24.
//

#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <memory>
#include "Music.h"
#include "SDL.h"
#include "GameObject.h"

    class State {
    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void AddObject(GameObject* go);

    private:
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;
    };

#endif //GAME_STATE_H
