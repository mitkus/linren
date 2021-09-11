#pragma once

#include <cmath>

struct Vec2 {
    float x, y;

    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}
    Vec2(const Vec2& v) = default;

    Vec2 operator-() { return Vec2(-x, -y); }

    Vec2 operator+(Vec2 rhs) { return Vec2(x + rhs.x, y + rhs.y); }
    Vec2 operator-(Vec2 rhs) { return Vec2(x - rhs.x, y - rhs.y); }
    Vec2 operator*(float s) { return Vec2(x * s, y * s); }
    Vec2 operator/(float s) { return Vec2(x / s, y / s); }

    Vec2& operator+=(Vec2 rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vec2& operator-=(Vec2 rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Vec2& operator*=(float s) {
        x *= s;
        y *= s;
        return *this;
    }
    Vec2& operator/=(float s) {
        x /= s;
        y /= s;
        return *this;
    }

    float length_sq() { return x * x + y * y; }
    float length() { return sqrtf(length_sq()); }

    Vec2 normalized() {
        float inv_l = 1.0f / length();
        return Vec2(x * inv_l, y * inv_l);
    }
    void normalize() {
        float inv_l = 1.0f / length();
        x *= inv_l;
        y *= inv_l;
    }
};
