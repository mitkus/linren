#include <stdio.h>

#include "glwindow.h"
#include "linerenderer.h"
#include "vec2.h"

const float pi = 3.1415f;
const size_t window_width = 800;
const size_t window_height = 600;

// Returns random float in given range
float rand_float(float min, float max) {
    float t = (float)rand() / (float)RAND_MAX;
    return min + t * (max - min);
}

// Draws a test pattern that includes various line arrangements.
void draw_line_pattern(LineRenderer* lren) {
    LineDef defs[100];

    float time = (float)SDL_GetTicks() / 1000.0f;

    // Circle
    Vec2 cursor(80.0f, 520.0f);
    for(int i = 0; i < 16; ++i) {
        float t = (float)i / 16.0f;
        Color c = Color::lerp(
            Color{0.0f, 0.1f, 0.9f, 1.0f}, Color{0.1f, 0.9f, 0.3f, 1.0f}, t);
        Vec2 o(sinf(time / 8.0f + t * 2.0f * pi),
               -cosf(time / 8.0f + t * 2.0f * pi));
        defs[i] = LineDef{cursor + o * 72.0f, cursor - o * 72.0f, 2.0f, c};
    }
    lren->add_lines(defs, 16);

    // Rect with varying angles
    cursor = Vec2(210.0f, 460.0f);
    for(int i = 0; i < 20; ++i) {
        float t = (float)i / 20.0f;
        Color c = Color::lerp(
            Color{0.7f, 0.7f, 0.0f, 1.0f}, Color{0.2f, 0.2f, 0.7f, 1.0f}, t);
        defs[i] = LineDef{cursor + Vec2(600.0f, 0.0f) * t,
                          cursor + Vec2(0.0f, 120.0f) + Vec2(180.0f, 0.0f) * t,
                          1.0f,
                          c};
    }
    lren->add_lines(defs, 20);

    // Horizontal lines of different thickness
    cursor = Vec2(20.0f, 300.0f);
    for(int i = 0; i < 10; ++i) {
        defs[i] = LineDef{cursor + Vec2(0.0f, i * 14.0f),
                          cursor + Vec2(window_width - 40.0f, i * 14.0f),
                          (float)i,
                          {0.2f, 0.2f, 0.2f, 1.0f}};
    }
    lren->add_lines(defs, 10);

    // Vertical lines of differrent thickness
    cursor = Vec2(20.0f, 220.0f);
    for(int i = 0; i < 64; ++i) {
        float t = (float)i / 64.0f;
        defs[i] = LineDef{cursor + Vec2(i * 12.0f, 0.0f),
                          cursor + Vec2(i * 12.0f, 60.0f),
                          4.0f + sinf(time * 3.0f + t * 8.0f * pi) * 3.0f,
                          {0.2f, 0.2f, 0.2f, 1.0f}};
    }
    lren->add_lines(defs, 64);

    // Frame for random portion of the test
    cursor = Vec2(20.0f, 200.0f);
    Vec2 x_offset(window_width - 40.0f, 0.0f);
    Vec2 y_offset(0.0f, -180.0f);
    Vec2 xy_offset = x_offset + y_offset;
    Color black = {0.0f, 0.0f, 0.0f, 1.0f};
    defs[0] = {cursor, cursor + x_offset, 1.0f, black};
    defs[1] = {cursor + x_offset, cursor + xy_offset, 1.0f, black};
    defs[2] = {cursor + xy_offset, cursor + y_offset, 1.0f, black};
    defs[3] = {cursor + y_offset, cursor, 1.0f, black};
    lren->add_lines(defs, 4);

    // Random lines, change pattern every 2 seconds
    srand((int)time / 2.0f);
    for(int i = 0; i < 100; ++i) {
        Color c = {rand_float(0.2f, 0.8f),
                   rand_float(0.2f, 0.8f),
                   rand_float(0.2f, 0.8f),
                   1.0f};
        defs[i] = {Vec2(rand_float(20.0f, window_width - 40.0f),
                        rand_float(20.0f, 200.0f)),
                   Vec2(rand_float(20.0f, window_height - 40.0f),
                        rand_float(20.0f, 200.0f)),
                   1.0f,
                   c};
    }
    lren->add_lines(defs, 100);
}

int main() {
    GLWindow window("LineRen", window_width, window_height);
    LineRenderer lren(window_width, window_height);

    window.set_clear_color(0.9f, 0.9f, 0.9f);

    while(window.is_open()) {
        lren.clear();

        draw_line_pattern(&lren);

        lren.render();
        window.present();
    }
    return 0;
}
