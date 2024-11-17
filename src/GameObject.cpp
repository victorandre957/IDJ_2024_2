//
// Created by victor_moraes on 03/11/24.
//

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto& component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::unique_ptr<Component> cpt) {
    components.emplace_back(std::move(cpt));
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::find_if(components.begin(), components.end(),
                           [cpt](const std::unique_ptr<Component>& ptr) { return ptr.get() == cpt; });

    if (it != components.end()) {
        components.erase(it);
    }
}

Component* GameObject::GetComponent(std::string& type) {
    for (auto& component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}

