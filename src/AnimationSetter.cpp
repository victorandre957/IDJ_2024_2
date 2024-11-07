//
// Created by victor_moraes on 07/11/24.
//

#include "AnimationSetter.h"
#include "GameObject.h"

AnimationSetter::AnimationSetter(GameObject& associated): Component(associated) {}

void AnimationSetter::Update(float dt) {}

void AnimationSetter::Render() {}

bool AnimationSetter::Is(const std::string& type) const {
    return type == "AnimationSetter";
}

void AnimationSetter::SetAnimation(const std::string& name) {
    auto it = animations.find(name);
    if (it != animations.end()) {
        auto* spriteRenderer = associated.GetComponent<SpriteRenderer>();
        if (spriteRenderer) {
            spriteRenderer->SetAnimation(it->second);
            currentAnimation = name;
        }
    }
}

void AnimationSetter::AddAnimation(const std::string& name, const Animation& anim) {
    if (animations.find(name) == animations.end()) {
        animations.emplace(name, anim);
    }
}

std::string AnimationSetter::GetCurrentAnimation() const {
    return currentAnimation;
}