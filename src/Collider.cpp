//
// Created by victor_moraes on 17/02/25.
//

#include "Collider.h"

Collider::~Collider() {
}

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset):
        Component(associated), scale(scale), offset(offset), box() {}

void Collider::Start() {}

void Collider::Update(float dt) {
    box.w = associated.box.w * scale.x;
    box.h = associated.box.h * scale.y;
    box.Center(associated.box.Center() + offset);
}

bool Collider::Is(const std::string& type) const {
    return type == "Collider";
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}

void Collider::Render() {}