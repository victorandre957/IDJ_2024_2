//
// Created by victor_moraes on 03/11/24.
//

#ifndef GAME_SPRITERENDERER_H
#define GAME_SPRITERENDERER_H

#pragma once

#include "Component.h"
#include "Sprite.h"
#include "Animation.h"
#include "GameObject.h"

class SpriteRenderer : public Component {
public:
    explicit SpriteRenderer(GameObject& associated);
    SpriteRenderer(GameObject& associated, const std::string& file, int frameCountW = 1, int frameCountH = 1);

    void Open(const std::string& file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void Update(float dt) override;
    void Render() override;
    [[nodiscard]] bool Is(const std::string& type) const override;
    bool IsAnimationFinished() const;
    void SetAnimation(Animation anim);

private:
    Sprite sprite;
    int frameStart;
    int frameEnd;
    float frameTime;
    int currentFrame;
    float timeElapsed;
};


#endif //GAME_SPRITERENDERER_H
