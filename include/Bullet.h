//
// Created by victor_moraes on 26/01/25.
//

#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#pragma once

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Resources.h"
#include <cmath>
#include "AnimationSetter.h"

class Bullet : public Component {
public:
    explicit Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance);
    void Update(float dt) override;
    void Render() override;
    [[nodiscard]] bool Is(const std::string& type) const override;
    int GetDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif //GAME_BULLET_H
