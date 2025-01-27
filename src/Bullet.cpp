//
// Created by victor_moraes on 26/01/25.
//

#include "Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance)
    : Component(associated), speed(Vec2(speed * cos(angle), speed * sin(angle))), distanceLeft(maxDistance), damage(damage) {
    auto spriteRenderer = std::make_unique<SpriteRenderer>(associated, "./public/img/Bullet.png");
    associated.AddComponent(std::move(spriteRenderer));
    auto animationSetter = std::make_unique<AnimationSetter>(associated);
    animationSetter->AddAnimation("idle", Animation(0, 0, 0));
    associated.AddComponent(std::move(animationSetter));

}

void Bullet::Update(float dt) {
    Vec2 displacement = speed * dt;
    associated.box.x += displacement.x;
    associated.box.y += displacement.y;
    distanceLeft -= displacement.Magnitude();
    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {
    // Does nothing
}

bool Bullet::Is(const std::string& type) const {
    return type == "Bullet";
}

int Bullet::GetDamage() {
    return damage;
}
