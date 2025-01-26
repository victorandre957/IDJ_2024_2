//
// Created by victor_moraes on 25/01/25.
//

#ifndef GAME_PLAYERCONTROLLER_H
#define GAME_PLAYERCONTROLLER_H

#include "SDL.h"

#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d

#pragma  once

#include "Component.h"
#include "InputManager.h"
#include "Gun.h"
#include "GameObject.h"
#include "Character.h"
#include <iostream>

class PlayerController : public Component {
public:
    explicit PlayerController(GameObject& associated);
    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;
};


#endif //GAME_PLAYERCONTROLLER_H
