//
// Created by victor_moraes on 22/10/24.
//

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite() : texture(nullptr), width(0), height(0) {}

Sprite::Sprite(std::string file) : texture(nullptr), width(0), height(0) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        printf("Failed to load texture: %s\n", SDL_GetError());
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    if (texture != nullptr) {
        SDL_Rect dstrect = {x, y, clipRect.w, clipRect.h};  // Define o retângulo de destino
        SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}