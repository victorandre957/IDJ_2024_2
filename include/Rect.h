//
// Created by victor_moraes on 03/11/24.
//

#ifndef GAME_RECT_H
#define GAME_RECT_H

#pragma once

#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    Rect operator+(const Vec2& vec) const;
    Rect operator-(const Vec2& vec) const;
    Rect& operator+=(const Vec2& vec);
    Rect& operator-=(const Vec2& vec);

    Vec2 Center() const;
    float CenterDistance(const Rect& other) const;
    bool Contains(const Vec2& point) const;

};


#endif //GAME_RECT_H
