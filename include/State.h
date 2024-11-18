    //
// Created by victor_moraes on 22/10/24.
//

#pragma once

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <GameObject.h>
#include <Sprite.h>
#include <Music.h>
#include "InputManager.h"
#include <vector>
#include <memory>


    class State {
    private:
        Music music;
        std::vector<std::unique_ptr<GameObject>> objectArray;

        bool quitRequested;
    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void AddObject(GameObject* go);
    };

#endif //GAME_STATE_H
