//
// Created by victor_moraes on 06/11/24.
//

#include "Zombie.h"

Zombie::Zombie(GameObject& associated)
        : Component(associated), hitpoints(150), deathDelay(70.0f),
          deathSound("./public/audio/Dead.wav"), hitSound("./public/audio/Hit0.wav") {
    auto spriteRenderer = std::make_unique<SpriteRenderer>(associated, "./public/img/Enemy.png", 3, 2);
    associated.AddComponent(std::move(spriteRenderer));

    auto animationSetter = std::make_unique<AnimationSetter>(associated);
    animationSetter->AddAnimation("walking", Animation(0, 3, 10));
    animationSetter->AddAnimation("damage", Animation(4, 4, 10));
    animationSetter->AddAnimation("dying", Animation(3, 5, 10));
    animationSetter->AddAnimation("dead", Animation(5, 5, 0));
    animationSetter->SetAnimation("walking");

    associated.AddComponent(std::move(animationSetter));
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;

    if (!isDying) {
        auto animationSetter = associated.GetComponent<AnimationSetter>();
        if (animationSetter) {
            animationSetter->SetAnimation("damage");
            isTakingDamage = true;
            damageTimer = 0.0f;
        }
    }

    if (hitpoints <= 0 && !isDying) {
        auto animationSetter = associated.GetComponent<AnimationSetter>();
        if (animationSetter) {
            isDying = true;
            animationSetter->SetAnimation("dying");
            deathTimer = 0.0f;

            deathSound.Play(1);
        }
    }
}

void Zombie::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    if (!isDying) {
        if (input.MousePress(LEFT_MOUSE_BUTTON)) {
            int mouseX = input.GetMouseX();
            int mouseY = input.GetMouseY();
            if (associated.box.Contains(Vec2(mouseX, mouseY))) {
                Damage(50);
                hitSound.Play(1);
            }
        }

        if (isTakingDamage) {
            damageTimer += dt;
            if (damageTimer >= 10) {
                auto animationSetter = associated.GetComponent<AnimationSetter>();
                if (animationSetter) {
                    animationSetter->SetAnimation("walking");
                }
                isTakingDamage = false;
            }
        }
    }

    if (isDying) {
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