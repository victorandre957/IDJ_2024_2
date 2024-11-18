//
// Created by victor_moraes on 18/11/24.
//

#ifndef GAME_INPUTMANAGER_H
#define GAME_INPUTMANAGER_H

#pragma once

#include <unordered_map>
#include "SDL.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

class InputManager {
public:
    void Update();
    bool KeyPress(int key) const;
    bool KeyRelease(int key) const;
    bool IsKeyDown(int key) const;
    bool MousePress(int button) const;
    bool MouseRelease(int button) const;
    bool IsMouseDown(int button) const;
    int GetMouseX() const;
    int GetMouseY() const;
    bool QuitRequested() const;

    static InputManager& GetInstance();

private:
    InputManager();
    ~InputManager();

    bool quitRequested;
    int updateCounter;
    int mouseX, mouseY;

    bool mouseState[6];
    int mouseUpdate[6];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
};

#endif //GAME_INPUTMANAGER_H
