//
// Created by victor_moraes on 22/10/24.
//

#include "State.h"
#include "Zombie.h"
#include "TileSet.h"
#include "TileMap.h"

State::State() : quitRequested(false) {}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    music.Open("./public/audio/BGM.wav");

    auto tileSet = std::make_unique<TileSet>(64, 64, "./public/img/Tileset.png");
    auto mapObject = std::make_unique<GameObject>();
    auto tileMap = std::make_unique<TileMap>(*mapObject, "./public/map/map.txt", std::move(tileSet));

    mapObject->AddComponent(std::move(tileMap));
    AddObject(mapObject.release());

    auto zombieObject1 = std::make_unique<GameObject>();
    zombieObject1->box.x = 600;
    zombieObject1->box.y = 450;

    auto zombieComponent1 = std::make_unique<Zombie>(*zombieObject1);
    zombieObject1->AddComponent(std::move(zombieComponent1));
    AddObject(zombieObject1.release());

    auto zombieObject2 = std::make_unique<GameObject>();
    zombieObject2->box.x = 800;
    zombieObject2->box.y = 550;

    auto zombieComponent2 = std::make_unique<Zombie>(*zombieObject2);
    zombieObject2->AddComponent(std::move(zombieComponent2));
    AddObject(zombieObject2.release());

    auto zombieObject3 = std::make_unique<GameObject>();
    zombieObject3->box.x = 1000;
    zombieObject3->box.y = 650;

    auto zombieComponent3 = std::make_unique<Zombie>(*zombieObject3);
    zombieObject3->AddComponent(std::move(zombieComponent3));
    AddObject(zombieObject3.release());

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

