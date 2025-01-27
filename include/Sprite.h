//
// Created by victor_moraes on 22/10/24.
//

#pragma once

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "SDL_image.h"
#include "SDL.h"
#include <string>
#include "Resources.h"
#include "Vec2.h"

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, double angle = 0.0) const;
    void Render(int x, int y, int w, int h, double angle = 0.0) const;

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    bool IsOpen();

    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale() const;
    void SetFlip(SDL_RendererFlip flip);

private:
    SDL_Texture* texture;
    int width{}, height{};
    int frameCountW, frameCountH;
    int frameWidth{}, frameHeight{};
    SDL_Rect clipRect{};
    SDL_RendererFlip flip;
    Vec2 scale;
};

#endif // GAME_SPRITE_H
