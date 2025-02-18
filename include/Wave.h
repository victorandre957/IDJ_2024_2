//
// Created by victor_moraes on 17/02/25.
//

#ifndef GAME_WAVE_H
#define GAME_WAVE_H

#pragma once

class Wave {
public:
    Wave(int zombies, float cooldown);

    int zombies;
    float cooldown;
};


#endif //GAME_WAVE_H
