//
// Created by victor_moraes on 18/11/24.
//

#include "Camera.h"

Vec2 Camera::pos = {0, 0};
Vec2 Camera::speed = {0, 0};
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        pos.x = focus->box.Center().x - 1200 / 2;
        pos.y = focus->box.Center().y - 900 / 2;
    } else {
        InputManager& input = InputManager::GetInstance();
        speed = {0, 0};

        if (input.IsKeyDown(UP_ARROW_KEY)) {
            speed.y = 20;
        }
        if (input.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = -20;
        }
        if (input.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = 20;
        }
        if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = -20;
        }

        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }
}
