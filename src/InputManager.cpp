//
// Created by victor_moraes on 18/11/24.
//

#include "InputManager.h"

InputManager::InputManager()
        : quitRequested(false), updateCounter(0), mouseX(0), mouseY(0) {
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

InputManager::~InputManager() {}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::Update() {
    SDL_Event event;
    updateCounter++;
    quitRequested = false;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quitRequested = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.repeat == 0) {
                    keyState[event.key.keysym.sym] = true;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                }
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                keyUpdate[event.key.keysym.sym] = updateCounter;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;
        }
    }

    SDL_GetMouseState(&mouseX, &mouseY);
}

bool InputManager::KeyPress(int key) const {
    auto itState = keyState.find(key);
    auto itUpdate = keyUpdate.find(key);

    return itState != keyState.end() && itUpdate != keyUpdate.end() &&
           itState->second && itUpdate->second == updateCounter;
}

bool InputManager::KeyRelease(int key) const {
    auto itState = keyState.find(key);
    auto itUpdate = keyUpdate.find(key);

    return itState != keyState.end() && itUpdate != keyUpdate.end() &&
           !itState->second && itUpdate->second == updateCounter;
}

bool InputManager::IsKeyDown(int key) const {
    auto itState = keyState.find(key);
    return itState != keyState.end() && itState->second;
}

bool InputManager::MousePress(int button) const {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) const {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) const {
    return mouseState[button];
}

int InputManager::GetMouseX() const {
    return mouseX;
}

int InputManager::GetMouseY() const {
    return mouseY;
}

bool InputManager::QuitRequested() const {
    return quitRequested;
}

