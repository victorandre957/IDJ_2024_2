//
// Created by victor_moraes on 17/02/25.
//

#ifndef GAME_AICONTROLLER_H
#define GAME_AICONTROLLER_H


#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Timer.h>
#include <Vec2.h>
#include <iostream>

#include <Camera.h>
#include <Rect.h>
#include <Character.h>


class AIController: public Component {
public:
    AIController(GameObject& associated);

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type);
private:
    int npcCounter;
    enum AIState {
        MOVING,
        RESTING
    };
    AIState state;
    Timer restTimer;
    Vec2 destination;
    int cooldownRest;
};


#endif //GAME_AICONTROLLER_H
