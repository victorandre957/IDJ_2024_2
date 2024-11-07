//
// Created by victor_moraes on 03/11/24.
//
#pragma once

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H

#include <vector>
#include <string>
#include <memory>
#include "Component.h"
#include "Rect.h"


class GameObject {
public:
    GameObject();

    ~GameObject();

    void Update(float dt);

    void Render();

    bool IsDead() const;

    void RequestDelete();

    void AddComponent(std::unique_ptr<Component> cpt);

    void RemoveComponent(Component* cpt);

    template <typename T>
    T* GetComponent() {
        for (const auto& component : components) {
            if (auto* casted = dynamic_cast<T*>(component.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    Rect box;

private:
    std::vector<std::unique_ptr<Component>> components;

    bool isDead;

    Component *GetComponent(const std::string &type);
};


#endif //GAME_GAMEOBJECT_H
