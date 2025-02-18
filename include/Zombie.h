//
// Created by victor_moraes on 06/11/24.
//

#ifndef GAME_ZOMBIE_H
#define GAME_ZOMBIE_H

#pragma once

#include <string>
#include <utility>
#include "Component.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "AnimationSetter.h"
#include "Camera.h"
#include "Sound.h"
#include "Collider.h"
#include "Bullet.h"

class Zombie : public Component {
public:
    explicit Zombie(GameObject& associated);
    ~Zombie();
    void Damage(int damage);
    void Update(float dt) override;
    void Render() override;
    [[nodiscard]] bool Is(const std::string& type) const override;
    void NotifyCollision(GameObject& other);

    static int zombieCount;
private:
    int hitpoints;
    bool isDying{};
    bool isTakingDamage{};
    float deathDelay;
    float damageTimer{};
    float deathTimer{};
    Sound deathSound;
    Sound hitSound;
};

#endif // GAME_ZOMBIE_H
