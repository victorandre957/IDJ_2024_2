    //
// Created by victor_moraes on 07/11/24.
//

#ifndef ANIMATION_SETTER_H
#define ANIMATION_SETTER_H

#pragma once

#include <string>
#include <unordered_map>
#include "Component.h"
#include "Animation.h"
#include "SpriteRenderer.h"

    class AnimationSetter : public Component {
    public:

        explicit AnimationSetter(GameObject& associated);


        void Update(float dt) override;

        void Render() override;

        bool Is(const std::string& type) const override;

        void SetAnimation(const std::string& name);

        void AddAnimation(const std::string& name, const Animation& anim);

        std::string GetCurrentAnimation() const;

    private:
        std::unordered_map<std::string, Animation> animations;

        std::string currentAnimation;
    };

#endif // ANIMATION_SETTER_H
