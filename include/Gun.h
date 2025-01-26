//
// Created by victor_moraes on 25/01/25.
//

#ifndef GAME_GUN_H
#define GAME_GUN_H

#pragma once

#include <memory>
#include <string>
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include "Sound.h"
#include "AnimationSetter.h"
#include "SpriteRenderer.h"

class Gun : public Component {
public:
    Gun(GameObject& associated, std::weak_ptr<GameObject> character);

    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;
    void Shoot(Vec2 target);
    void SetTarget(Vec2 target); // New method

private:
    Sound shotSound;
    Sound reloadSound;
    int cooldown;
    Timer cdTimer;
    std::weak_ptr<GameObject> character;
    float angle;
    Vec2 target; // New member variable
};

#endif //GAME_GUN_H
