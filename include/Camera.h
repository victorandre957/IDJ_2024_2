//
// Created by victor_moraes on 18/11/24.
//

#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#pragma once

#include "Vec2.h"
#include "GameObject.h"
#include "InputManager.h"

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;

private:
    static GameObject* focus;
};

#endif //GAME_CAMERA_H
