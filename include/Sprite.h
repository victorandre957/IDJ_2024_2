//
// Created by victor_moraes on 22/10/24.
//

#pragma once

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "SDL_image.h"
#include "SDL.h"
#include <string>

class Sprite {
public:
    Sprite();
    explicit Sprite(const std::string& file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    void Render(int x, int y, int w, int h);

    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen();

    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

private:
    SDL_Texture* texture;
    int width{}, height{};
    int frameCountW, frameCountH;
    int frameWidth{}, frameHeight{};
    SDL_Rect clipRect{};
};

#endif // GAME_SPRITE_H
