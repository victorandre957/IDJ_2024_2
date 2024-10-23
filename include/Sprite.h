//
// Created by victor_moraes on 22/10/24.
//

#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include "SDL_image.h"
#include "SDL.h"
#include <string>

class Sprite {
public:
    Sprite();
    Sprite(std::string file);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);

    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};


#endif //GAME_SPRITE_H
