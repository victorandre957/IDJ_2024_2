//
// Created by victor_moraes on 03/11/24.
//

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : box(), angleDeg(0), isDead(false), started(false) {}

void GameObject::Start() {
    for (auto& component : components) {
        component->Start();
    }
    started = true;
}

GameObject::~GameObject() = default;

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

void GameObject::AddComponent(std::shared_ptr<Component> cpt) {
    components.emplace_back(std::move(cpt));
    if (started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt) {
    components.erase(std::remove(components.begin(), components.end(), cpt), components.end());
}

std::shared_ptr<Component> GameObject::GetComponent(const std::string& type) {
    for (auto& component : components) {
        if (component->Is(type)) {
            return component;
        }
    }
    return nullptr;
}

std::weak_ptr<GameObject> GameObject::AsWeakPtr() {
    return shared_from_this();
}

void GameObject::NotifyCollision(GameObject& other) {
    const int size = components.size();
    for (int i = 0; i < size; i++) {
        components[i]->NotifyCollision(other);
    }
}