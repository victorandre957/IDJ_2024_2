//
// Created by victor_moraes on 25/01/25.
//

#include "Gun.h"

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character)
        : Component(associated),
        shotSound("./public/audio/Range.wav"),
        reloadSound("./public/audio/PumpAction.mp3"),
        cooldown(1),
        cdTimer(),
        character(std::move(character)),
        angle(0) {

    auto spriteRenderer = std::make_unique<SpriteRenderer>(associated, "./public/img/Gun.png", 3, 2);
    associated.AddComponent(std::move(spriteRenderer));

    auto animationSetter = std::make_unique<AnimationSetter>(associated);
    animationSetter->AddAnimation("idle", Animation(0, 0, 0));
    animationSetter->AddAnimation("shooting", Animation(1, 2, 10));
    animationSetter->AddAnimation("reloading", Animation(3, 5, 10));
    animationSetter->SetAnimation("idle");

    associated.AddComponent(std::move(animationSetter));
}

void Gun::SetTarget(Vec2 target) {
    this->target = target;
}

void Gun::Update(float dt) {
    if (auto characterPtr = character.lock()) {
        // Calculate the new position of the gun based on the character's position and the angle
        Vec2 characterCenter = characterPtr->box.Center();

        // Calculate the angle to the target
        angle = atan2(target.y - characterCenter.y, target.x - characterCenter.x);

        // Update the gun's position to point towards the target
        if (cos(angle) < 0) {
            associated.box.x = characterCenter.x + cos(angle) * (characterCenter.x / 4);
        } else {
            associated.box.x = characterCenter.x + cos(angle) * (characterCenter.x / 4 - 50);
        }

        if (sin(angle) < 0) {
            associated.box.y = characterCenter.y + sin(angle) * (characterCenter.y / 4  +10);
        } else {
            associated.box.y = characterCenter.y + sin(angle) * (characterCenter.y  / 4);
        }

        auto spriteRenderer = associated.GetComponent<SpriteRenderer>();

        auto animationSetter = associated.GetComponent<AnimationSetter>();
        if (animationSetter && animationSetter->GetCurrentAnimation() == "shooting" && spriteRenderer->IsAnimationFinished()) {
            reloadSound.Play();
            animationSetter->SetAnimation("reloading");
        }

        if(cdTimer.Get()>20) {
            animationSetter->SetAnimation("idle");
        }

        cdTimer.Update(dt);

        if (angle > M_PI / 2 || angle < -M_PI / 2) {
            spriteRenderer->SetFlip(SDL_FLIP_HORIZONTAL);
            associated.angleDeg = sin(angle) * 90 * -1;
        } else {
            associated.angleDeg = sin(angle) * 90;
        }

    } else {
        associated.RequestDelete();
    }
}


void Gun::Render() {
    if (auto sprite = associated.GetComponent<SpriteRenderer>()) {
        sprite->Render();
    }
}

bool Gun::Is(const std::string& type) const {
    return type == "Gun";
}

void Gun::Shoot(Vec2 target) {
    if (cdTimer.Get() > 10) {
        shotSound.Play();
        cdTimer.Restart();

        auto bulletGO = std::make_shared<GameObject>();

        angle = atan2(target.y - associated.box.y, target.x - associated.box.x);

        bulletGO->AddComponent(std::make_shared<Bullet>(*bulletGO, angle, 15, 10, 1000));

        bulletGO->box.Center(associated.box.Center() + Vec2(cos(angle), sin(angle)) * 50);

        bulletGO->angleDeg = (angle - M_PI_2) * 180 / M_PI; // Set the bullet's angle to match the firing direction

        auto spriteRenderer = bulletGO->GetComponent<SpriteRenderer>();

        if (spriteRenderer) {
            spriteRenderer->SetFlip(SDL_FLIP_VERTICAL);
        }

        // Add the Bullet GameObject to the game
        State::GetInstance().AddObject(bulletGO);

        auto animationSetter = associated.GetComponent<AnimationSetter>();
        if (animationSetter) {
            animationSetter->SetAnimation("shooting");
        }
    }
}
