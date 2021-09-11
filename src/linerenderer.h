#pragma once

#include "vec2.h"

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

struct LineDef {
    Vec2 start, end;
    float width;
    float r, g, b, a;
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

    GLuint load_shader(const char *src, GLenum type);
};
