#pragma once

struct Color {
    float r, g, b, a;

    static Color lerp(Color a, Color b, float t) {
        return Color{a.r * (1.0f - t) + b.r * t,
                     a.g * (1.0f - t) + b.g * t,
                     a.b * (1.0f - t) + b.b * t,
                     a.a * (1.0f - t) + b.a * t};
    }
};
