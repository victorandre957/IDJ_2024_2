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
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Camera.h"
#include "Character.h"
#include <vector>
#include <memory>
#include "PlayerController.h"
#include <algorithm>
#include "Collider.h"
#include "WaveSpawner.h"

class State {
private:
    Music music;
    std::vector<std::shared_ptr<GameObject>> objectArray;
    bool started;
    bool quitRequested;

    static State* instance;

    // Sorting function
    static bool CompareGameObject(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b);

public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();

    static State& GetInstance();

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> AddObject(const std::shared_ptr<GameObject>& go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};

#endif //GAME_STATE_H
