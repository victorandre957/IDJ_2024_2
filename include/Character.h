//
// Created by victor_moraes on 25/01/25.
//

#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H
#pragma once

#include <string>
#include <queue>
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "GameObject.h"
#include "AnimationSetter.h"
#include "SpriteRenderer.h"
#include "Gun.h"
#include "State.h"

class Command {
public:
    enum CommandType {
        MOVE,
        STOP,
        SHOOT
    };

    Command(CommandType type, float x, float y);

    CommandType type;
    Vec2 pos;
};

class Character : public Component {
public:
    explicit Character(GameObject& associated, const std::string& sprite);
    ~Character() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

    void Issue(Command task);
    std::weak_ptr<GameObject> GetGun() const; // New method

    static Character* player;

private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;
    Vec2 speed;
    float linearSpeed;
    int hp;
    Timer deathTimer;
};

#endif //GAME_CHARACTER_H
