//
// Created by victor_moraes on 25/01/25.
//

#include "Character.h"

Character* Character::player = nullptr;

Character::Character(GameObject& associated, const std::string& sprite)
        : Component(associated), speed(Vec2()), linearSpeed(10), hp(100), deathTimer() { // Adjusted linearSpeed to 10
    associated.AddComponent(std::make_shared<SpriteRenderer>(associated, sprite, 3, 4));

    auto animationSetter = std::make_unique<AnimationSetter>(associated);
    animationSetter->AddAnimation("idle", Animation(6, 9, 12.f));
    animationSetter->AddAnimation("walking", Animation(0, 5, 10.f));
    animationSetter->AddAnimation("dead", Animation(12, 13, 2.f));
    animationSetter->SetAnimation("idle");

    associated.AddComponent(std::move(animationSetter));

    if (!Character::player) {
        Character::player = this;
    }
}

Character::~Character() {
    if (Character::player == this) {
        Character::player = nullptr;
    }
}

void Character::Start() {
    auto gunObject = std::make_shared<GameObject>();
    gunObject->AddComponent(std::make_shared<Gun>(*gunObject, associated.AsWeakPtr()));
    State::GetInstance().AddObject(gunObject);
    gun = gunObject;
}

void Character::Update(float dt) {
    auto animationSetter = associated.GetComponent<AnimationSetter>();
    auto spriteRenderer = associated.GetComponent<SpriteRenderer>();

    if (!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::CommandType::MOVE) {
            Vec2 direction = task.pos - associated.box.Center();
            speed = direction.Normalize() * linearSpeed;
            if (animationSetter->GetCurrentAnimation() != "walking") {
                animationSetter->SetAnimation("walking");
            }

            if (direction.x < 0) {
                flip = true;
            } else if (direction.x > 0) {
                flip = false;
            }
        }
    } else {
        speed = Vec2();
        if (animationSetter->GetCurrentAnimation() != "idle") {
            animationSetter->SetAnimation("idle");
        }
    }

    if(flip) {
        spriteRenderer->SetFlip(SDL_FLIP_HORIZONTAL);
    } else {
        spriteRenderer->SetFlip(SDL_FLIP_NONE);
    }

    associated.box += speed * dt;

    if (hp <= 0) {
        if (animationSetter) {
            animationSetter->SetAnimation("dead");
        }
        if (spriteRenderer && spriteRenderer->IsAnimationFinished()) {
            associated.RequestDelete();
        }
    }
}

void Character::Render() {}

bool Character::Is(const std::string& type) const {
    return type == "Character";
}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

// Add the missing Command constructor implementation
Command::Command(CommandType type, float x, float y) : type(type), pos(x, y) {}

std::weak_ptr<GameObject> Character::GetGun() const {
    return gun;
}