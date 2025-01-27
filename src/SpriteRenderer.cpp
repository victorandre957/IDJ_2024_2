//
// Created by victor_moraes on 03/11/24.
//
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(GameObject& associated)
        : Component(associated), sprite(), frameStart(0), frameEnd(0), frameTime(0.0f), currentFrame(0), timeElapsed(0.0f) {
}


SpriteRenderer::SpriteRenderer(GameObject& associated, const std::string& file, int frameCountW, int frameCountH)
        : Component(associated), sprite(file, frameCountW, frameCountH), frameStart(0), frameEnd(0), frameTime(0.0f), currentFrame(0), timeElapsed(0.0f) {
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}


void SpriteRenderer::Open(const std::string& file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}


void SpriteRenderer::Update(float dt) {
    if (frameTime > 0) {
        timeElapsed += dt;

        if (timeElapsed > frameTime) {
            timeElapsed -= frameTime;
            currentFrame++;


            if (currentFrame > frameEnd) {
                currentFrame = frameStart;
            }

            sprite.SetFrame(currentFrame);
        }
    }
}


void SpriteRenderer::Render() {
    sprite.Render(associated.box.x, associated.box.y, associated.angleDeg);
}

bool SpriteRenderer::Is(const std::string& type) const {
    return type == "SpriteRenderer";
}

void SpriteRenderer::SetAnimation(Animation anim) {
    frameStart = anim.frameStart;
    frameEnd = anim.frameEnd;
    frameTime = anim.frameTime;
    currentFrame = frameStart;
    timeElapsed = 0;

    sprite.SetFrame(currentFrame);
    sprite.SetFlip(anim.flip);
}

bool SpriteRenderer::IsAnimationFinished() const {
    return currentFrame == frameEnd;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    Vec2 oldCenter = associated.box.Center();
    sprite.SetScale(scaleX, scaleY);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    associated.box.Center(oldCenter);
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}

void SpriteRenderer::SetFlip(SDL_RendererFlip flip) {
    sprite.SetFlip(flip);
}
