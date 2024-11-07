//
// Created by victor_moraes on 22/10/24.
//

#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite() : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1), frameWidth(0), frameHeight(0) {}

Sprite::Sprite(const std::string& file, int frameCountW, int frameCountH) : texture(nullptr), frameCountW(frameCountW), frameCountH(frameCountH) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(const std::string& file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
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

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect = { x, y, clipRect.w, clipRect.h };
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect dstrect = { x, y, w, h };
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
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
    return frameWidth;
}

int Sprite::GetHeight() const {
    return frameHeight;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}