//
// Created by victor_moraes on 03/11/24.
//

#ifndef GAME_ANIMATION_H
#define GAME_ANIMATION_H

class Animation {
public:
    Animation(int frameStart, int frameEnd, float frameTime);

    int frameStart;
    int frameEnd;
    float frameTime;
};


#endif //GAME_ANIMATION_H
