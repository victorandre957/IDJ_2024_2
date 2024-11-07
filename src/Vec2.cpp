//
// Created by victor_moraes on 03/11/24.
//

#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2& other) const {
    return {x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return {x - other.x, y - other.y};
}

Vec2 Vec2::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

float Vec2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

Vec2 Vec2::Normalize() const {
    float mag = Magnitude();
    return (mag != 0) ? Vec2(x / mag, y / mag) : Vec2(0, 0);
}

float Vec2::Distance(const Vec2& other) const {
    return (*this - other).Magnitude();
}

float Vec2::Angle() const {
    return std::atan2(y, x);
}

Vec2 Vec2::Rotate(float angle) const {
    float cosTheta = std::cos(angle);
    float sinTheta = std::sin(angle);
    return {x * cosTheta - y * sinTheta, y * cosTheta + x * sinTheta};
}