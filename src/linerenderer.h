#pragma once

#include "color.h"
#include "vec2.h"

#include <vector>

#define GL_GLEXT_PROTOTYPES
#include <SDL_opengl.h>

// Data format for defining a line to draw
// on the application side.
struct LineDef {
    Vec2 start, end;
    float width;
    Color col;
};

// Internal data structure for line vertices.
struct LineVertex {
    Vec2 pos;
    float width, dist;
    Color col;
};

// Anti-aliased line renderer.
//
// Lines are drawn with analytically calculated
// pixel coverage for anti-aliasing.
// TODO: review OpenGL state changes for an app
// that does more than render lines.
class LineRenderer {
public:
    // Initializes OpenGL state for line rendering and
    // loads two shader from the filesystem:
    // shaders/line.vert and shaders/line.frag
    LineRenderer(size_t buffer_width,
                 size_t buffer_height,
                 size_t max_lines = 4096);
    ~LineRenderer();

    // Adds lines to a draw list.
    void add_lines(const LineDef *defs, size_t count);

    // Clears draw list.
    void clear();

    // Renders all the lines currently present in the draw list.
    void render();

private:
    const size_t max_lines;
    GLuint vert_shader, frag_shader, program;
    std::vector<LineVertex> vertices;

    GLuint load_shader(const char *src, GLenum type);
};
