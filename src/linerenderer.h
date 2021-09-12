#pragma once

#include "vec2.h"

#include <vector>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

struct Color {
    float r, g, b, a;

    static Color lerp(Color a, Color b, float t) {
        return Color{a.r * (1.0f - t) + b.r * t,
                     a.g * (1.0f - t) + b.g * t,
                     a.b * (1.0f - t) + b.b * t,
                     a.a * (1.0f - t) + b.a * t};
    }
};

struct LineDef {
    Vec2 start, end;
    float width;
    Color col;
};

struct LineVertex {
    Vec2 pos;
    float width, dist;
    Color col;
};

// Anti-aliased line renderer.
class LineRenderer {
public:
    LineRenderer(size_t buffer_width,
                 size_t buffer_height,
                 size_t max_lines = 4096);
    ~LineRenderer();

    void clear();
    void add_lines(const LineDef *defs, size_t count);
    void render();

private:
    GLuint vert_shader, frag_shader, program;

    std::vector<LineVertex> vertices;

    GLuint load_shader(const char *src, GLenum type);
};
