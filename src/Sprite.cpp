//
// Created by victor_moraes on 22/10/24.
//

#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite() : texture(nullptr), width(1), height(1), frameCountW(1), frameCountH(1), frameWidth(0), frameHeight(0), flip(SDL_FLIP_NONE), scale(1, 1) {}

Sprite::Sprite(const std::string& file, int frameCountW, int frameCountH) : texture(nullptr), frameCountW(frameCountW), frameCountH(frameCountH), flip(SDL_FLIP_NONE), scale(1, 1) {
    Open(file);
}

Sprite::~Sprite() = default;

void Sprite::Open(const std::string& file) {
    texture = Resources::GetImage(file);
    if (texture) {
        int width, height;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
        this->width = width;
        this->height = height;
    }
    if (texture == nullptr) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    frameWidth = width / frameCountW;
    frameHeight = height / frameCountH;

    SetClip(0, 0, frameWidth, frameHeight);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, double angle) const {
    SDL_Rect dstrect = { x, y, static_cast<int>(clipRect.w * scale.x), static_cast<int>(clipRect.h * scale.y) };
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, angle, nullptr, flip);
}

void Sprite::Render(int x, int y, int w, int h, double angle) const {
    SDL_Rect dstrect;
    dstrect.x = x + Camera::pos.x;
    dstrect.y = y + Camera::pos.y;
    dstrect.w = static_cast<int>(w * scale.x);
    dstrect.h = static_cast<int>(h * scale.y);

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, angle, nullptr, flip);
}

void Sprite::SetFrame(int frame) {
    int row = frame / frameCountW;
    int col = frame % frameCountW;
    int clipX = col * frameWidth;
    int clipY = row * frameHeight;

    SetClip(clipX, clipY, frameWidth, frameHeight);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    frameWidth = width / frameCountW;
    frameHeight = height / frameCountH;
}

int Sprite::GetWidth() const {
    return static_cast<int>(frameWidth * scale.x);
}

int Sprite::GetHeight() const {
    return static_cast<int>(frameHeight * scale.y);
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) scale.x = scaleX;
    if (scaleY != 0) scale.y = scaleY;
}

Vec2 Sprite::GetScale() const {
    return scale;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
    this->flip = flip;
}