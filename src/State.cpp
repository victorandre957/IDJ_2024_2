//
// Created by victor_moraes on 22/10/24.
//

#include "State.h"
#include "SpriteRenderer.h"
#include "Zombie.h"

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

    auto zombieObject = std::make_unique<GameObject>();
    zombieObject->box.x = 600;
    zombieObject->box.y = 450;

    auto zombieComponent = std::make_unique<Zombie>(*zombieObject);
    zombieObject->AddComponent(std::move(zombieComponent));
    AddObject(zombieObject.release());
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

    if (music.IsOpen() && Mix_PlayingMusic() == 0) {
        music.Play(-1);
    }

    for (const auto & i : objectArray) {
        i->Update(dt);
    }

    size_t i = 0;
    while (i < objectArray.size()) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        } else {
            ++i;
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

