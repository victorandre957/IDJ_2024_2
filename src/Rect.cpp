//
// Created by victor_moraes on 03/11/24.
//

#include "Rect.h"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Rect Rect::operator+(const Vec2& vec) const {
    return {x + vec.x, y + vec.y, w, h};
}

Rect Rect::operator-(const Vec2& vec) const {
    return {x - vec.x, y - vec.y, w, h};
}

Rect& Rect::operator+=(const Vec2& vec) {
    x += vec.x;
    y += vec.y;
    return *this;
}

Rect& Rect::operator-=(const Vec2& vec) {
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vec2 Rect::Center() const {
    return {x + w / 2, y + h / 2};
}

void Rect::Center(const Vec2& center) {
    x = center.x - w / 2;
    y = center.y - h / 2;
}

float Rect::CenterDistance(const Rect& other) const {
    return Center().Distance(other.Center());
}

bool Rect::Contains(const Vec2& point) const {
    return (point.x >= x && point.x <= x + w &&
            point.y >= y && point.y <= y + h);
}

float Rect::GetDiagonal() const {
    return sqrt(w * w + h * h);
}