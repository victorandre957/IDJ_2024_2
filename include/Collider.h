//
// Created by victor_moraes on 17/02/25.
//

#ifndef GAME_COLLIDER_H
#define GAME_COLLIDER_H

#pragma once

#include <cmath>
#include <Component.h>
#include "GameObject.h"
#include "Collision.h"
#include <Vec2.h>
#include <Rect.h>
#include <iostream>

class Collider: public Component {
public:
    Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    virtual ~Collider();
    Rect box;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
private:
    Vec2 scale;
    Vec2 offset;
};



#endif //GAME_COLLIDER_H
