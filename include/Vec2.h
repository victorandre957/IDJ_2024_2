//
// Created by victor_moraes on 03/11/24.
//

#ifndef GAME_VEC2_H
#define GAME_VEC2_H

#pragma once
#include <cmath>

class Vec2 {
public:
    float x, y;

    Vec2();
    Vec2(float x, float y);

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scalar) const;
    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);

    float Magnitude() const;
    Vec2 Normalize() const;
    float Distance(const Vec2& other) const;
    float Angle() const;
    Vec2 Rotate(float angle) const;

};


#endif //GAME_VEC2_H
