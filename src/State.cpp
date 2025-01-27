//
// Created by victor_moraes on 22/10/24.
//

#include "State.h"


State* State::instance = nullptr;

State::State() : quitRequested(false), started(false) {
    instance = this;
}

void State::Start() {
    LoadAssets();

    for (auto& obj : objectArray) {
        obj->Start();
    }
    started = true;
}

State::~State() {
    objectArray.clear();
    if (instance == this) {
        instance = nullptr;
    }
}

void State::LoadAssets() {
    music.Open("./public/audio/BGM.wav");

    auto tileSet = std::make_unique<TileSet>(64, 64, "./public/img/Tileset.png");
    auto mapObject = std::make_unique<GameObject>();
    auto tileMap = std::make_unique<TileMap>(*mapObject, "./public/map/map.txt", std::move(tileSet));

    mapObject->AddComponent(std::move(tileMap));
    AddObject(mapObject.release());

    auto characterObject = std::make_unique<GameObject>();
    auto character = std::make_shared<Character>(*characterObject, "./public/img/Player.png");
    characterObject->AddComponent(character);
    characterObject->box.x = 550; // Posição inicial X
    characterObject->box.y = 400; // Posição inicial Y

    // Adicione a PlayerController ao personagem
    auto playerController = std::make_shared<PlayerController>(*characterObject);
    characterObject->AddComponent(playerController);

    AddObject(characterObject.release());
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

    // Sort objects based on their Y position
    std::sort(objectArray.begin(), objectArray.end(), CompareGameObject);

    // Update all objects
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
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

State& State::GetInstance() {
    return *instance;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    auto sharedGo = std::shared_ptr<GameObject>(go);
    return AddObject(sharedGo);
}

std::weak_ptr<GameObject> State::AddObject(const std::shared_ptr<GameObject>& go) {
    objectArray.push_back(go);
    if (started) {
        go->Start();
    }
    return go;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (auto& sharedGo : objectArray) {
        if (sharedGo.get() == go) {
            return sharedGo;
        }
    }
    return std::weak_ptr<GameObject>(); // Retorna um weak_ptr vazio
}

bool State::CompareGameObject(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) {
    return a->box.y < b->box.y;
}
