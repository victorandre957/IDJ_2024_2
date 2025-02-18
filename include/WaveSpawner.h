//
// Created by victor_moraes on 17/02/25.
//

#ifndef GAME_WAVESPAWNER_H
#define GAME_WAVESPAWNER_H

#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Wave.h>
#include <Timer.h>
#include <memory>
#include <Zombie.h>
#include <Camera.h>
#include <Rect.h>

class WaveSpawner: public Component {
public:
    explicit WaveSpawner(GameObject& associated);
    WaveSpawner(GameObject& associated, std::vector<Wave> waves);
    ~WaveSpawner() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(const std::string& type) const override;

private:
    int zombieCounter;
    std::vector<Wave> waves;
    Timer zombieCooldownTimer;
    int currentWave;
};


#endif //GAME_WAVESPAWNER_H
