//
// Created by victor_moraes on 03/11/24.
//

#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#pragma once

#include <string>

class GameObject;

class Component {
public:
    explicit Component(GameObject& associated);

    virtual ~Component();

    virtual void Update(float dt) = 0;

    virtual void Render() = 0;

    virtual bool Is(const std::string& type) const = 0;

protected:
    GameObject& associated;
};


#endif //GAME_COMPONENT_H
