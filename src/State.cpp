//
// Created by victor_moraes on 22/10/24.
//

#include "State.h"

State::State() : quitRequested(false) {}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    music.Open("./public/audio/BGM.wav");

    auto bgObject = std::make_unique<GameObject>();
    auto bgRenderer = std::make_unique<SpriteRenderer>(*bgObject, "./public/img/Background.png", 1, 1);
    bgObject->AddComponent(std::move(bgRenderer));
    AddObject(bgObject.release());

    auto tileSet = std::make_unique<TileSet>(64, 64, "./public/img/Tileset.png");
    auto mapObject = std::make_unique<GameObject>();
    auto tileMap = std::make_unique<TileMap>(*mapObject, "./public/map/map.txt", std::move(tileSet));

    mapObject->AddComponent(std::move(tileMap));
    AddObject(mapObject.release());
}

void State::Update(float dt) {
    Camera::Update(dt);
    InputManager& input = InputManager::GetInstance();

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    if (music.IsOpen()) {
        if (Mix_PlayingMusic() == 0) {
            music.Play(-1);
        }
    }

    if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
        auto zombieObject = std::make_unique<GameObject>();
        zombieObject->AddComponent(std::make_unique<Zombie>(*zombieObject));
        zombieObject->box.x = input.GetMouseX();
        zombieObject->box.y = input.GetMouseY();
        AddObject(zombieObject.release());
    }

    for (auto& object : objectArray) {
        object->Update(dt);
    }

    for (const auto& obj : objectArray) {
        if (obj->GetComponent<Zombie>()) {
            obj->box.x += Camera::speed.x;
            obj->box.y += Camera::speed.y;
        }
    }

    auto it = objectArray.begin();
    while (it != objectArray.end()) {
        if ((*it)->IsDead()) {
            it = objectArray.erase(it);
        } else {
            ++it;
        }
    }
}

void State::Render() {
    for (auto& go : objectArray) {
        go->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(std::unique_ptr<GameObject>(go));
}

