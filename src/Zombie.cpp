//
// Created by victor_moraes on 06/11/24.
//

#include "Zombie.h"

Zombie::Zombie(GameObject& associated)
        : Component(associated), hitpoints(200),  deathDelay(70.0f) {

    auto spriteRenderer = std::make_unique<SpriteRenderer>(associated, "./public/img/Enemy.png", 3, 2);
    associated.AddComponent(std::move(spriteRenderer));

    auto animationSetter = std::make_unique<AnimationSetter>(associated);

    animationSetter->AddAnimation("walking", Animation(0, 3, 10));
    animationSetter->AddAnimation("dying", Animation(3, 5, 10));
    animationSetter->AddAnimation("dead", Animation(5, 5, 0));

    animationSetter->SetAnimation("walking");

    associated.AddComponent(std::move(animationSetter));
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;

    if (hitpoints <= 0 && !isDying) {
        auto animationSetter = associated.GetComponent<AnimationSetter>();
        if (animationSetter) {
            isDying = true;
            animationSetter->SetAnimation("dying");
            deathTimer = 0.0f;
        }
    }
}

void Zombie::Update(float dt) {
    if (!isDying) {
        Damage(1);
    } else {
        auto animationSetter = associated.GetComponent<AnimationSetter>();
        auto spriteRenderer = associated.GetComponent<SpriteRenderer>();

        if (animationSetter && spriteRenderer && spriteRenderer->IsAnimationFinished()) {
            if (animationSetter->GetCurrentAnimation() == "dying") {
                animationSetter->SetAnimation("dead");
            } else if (animationSetter->GetCurrentAnimation() == "dead") {
                deathTimer += dt;
                if (deathTimer >= deathDelay) {
                    associated.RequestDelete();
                }
            }
        }
    }
}

void Zombie::Render() {
}

bool Zombie::Is(const std::string& type) const {
    return type == "Zombie";
}