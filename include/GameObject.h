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
#include "Resources.h"

class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    [[nodiscard]] bool IsDead() const;
    void RequestDelete();
    void Start();

    void AddComponent(std::shared_ptr<Component> cpt);
    void RemoveComponent(std::shared_ptr<Component> cpt);

    std::weak_ptr<GameObject> AsWeakPtr();

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
    double angleDeg;

private:
    std::vector<std::shared_ptr<Component>> components;

    bool isDead;
    bool started;

    std::shared_ptr<Component> GetComponent(const std::string& type);
};

#endif //GAME_GAMEOBJECT_H
