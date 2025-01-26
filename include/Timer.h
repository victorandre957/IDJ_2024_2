//
// Created by victor_moraes on 25/01/25.
//

#ifndef GAME_TIMER_H
#define GAME_TIMER_H


class Timer {
public:
    Timer();

    void Update(float dt);

    void Restart();

    float Get() const;

private:
    float time;
};


#endif //GAME_TIMER_H
