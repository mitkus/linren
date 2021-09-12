#include "linerenderer.h"

#include <string>

LineRenderer::LineRenderer(size_t buffer_width,
                           size_t buffer_height,
                           size_t max_lines) {
    vert_shader = load_shader("shaders/line.vert", GL_VERTEX_SHADER);
    assert(vert_shader);

    frag_shader = load_shader("shaders/line.frag", GL_FRAGMENT_SHADER);
    assert(frag_shader);

    // Link shaders into a program, set vertex attributes and uniforms
    program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "width");
    glBindAttribLocation(program, 2, "dist");
    glBindAttribLocation(program, 3, "color");
    glLinkProgram(program);

    // Allocate client-side vertices buffer
    assert(sizeof(LineVertex) == 4 * 8);
    vertices.resize(max_lines * 6);
    // Dummy vertex to enable us to get pointers to the attributes
    vertices.push_back(LineVertex{});
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Set up vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, sizeof(LineVertex), &vertices[0].pos);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 1, GL_FLOAT, GL_FALSE, sizeof(LineVertex), &vertices[0].width);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 1, GL_FLOAT, GL_FALSE, sizeof(LineVertex), &vertices[0].dist);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(
        3, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), &vertices[0].col);
    vertices.clear();

    assert(glGetError() == GL_NO_ERROR);

    // Validate & bind the shader programs
    glValidateProgram(program);
    GLint valid;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);
    if(valid != GL_TRUE) {
        char buf[4096];
        GLsizei length;
        glGetProgramInfoLog(program, sizeof(buf), &length, buf);
        printf("Unable to validate program: %s\n", buf);
        assert(0);
    }
    glUseProgram(program);
    glUniform2f(glGetUniformLocation(program, "inv_screen_size"),
                1.0f / (float)buffer_width,
                1.0f / (float)buffer_height);
    assert(glGetError() == GL_NO_ERROR);

    // Initialize the needed GL state
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    assert(glGetError() == GL_NO_ERROR);
}

LineRenderer::~LineRenderer() {}

void LineRenderer::clear() { vertices.clear(); }

void LineRenderer::add_lines(const LineDef* defs, size_t count) {
    for(size_t i = 0; i < count; ++i) {
        LineDef def = defs[i];

        Vec2 dir = def.end - def.start;

        // Skip vanishingly short lines that would be invisible anyway
        if(dir.length_sq() < 0.001f) continue;

        // Get line normal - perpendicular vector to the line
        Vec2 normal = Vec2(dir.y, -dir.x).normalized();

        // Line half width expanded by one pixel to both sides to make
        // space for anti-aliasing
        float exp_width = def.width / 2.0f + 1.0f;

        // Four vertices of the line represented as quad
        LineVertex v0 = {
            def.start + normal * exp_width, def.width, exp_width, def.col};
        LineVertex v1 = {
            def.end + normal * exp_width, def.width, exp_width, def.col};
        LineVertex v2 = {
            def.end - normal * exp_width, def.width, -exp_width, def.col};
        LineVertex v3 = {
            def.start - normal * exp_width, def.width, -exp_width, def.col};

        // Push six new vertices to the buffer, for two quad triangles
        // (this could be avoided with use of index buffer)
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v2);
        vertices.push_back(v3);
        vertices.push_back(v0);
    }
}

void LineRenderer::render() {
    if(vertices.size() > 0) {
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        assert(glGetError() == GL_NO_ERROR);
    }
}

// Private methods

GLuint LineRenderer::load_shader(const char* path, GLenum type) {
    GLenum err = GL_NO_ERROR;

    // Read shader source file in chunks and put it in std::string
    // to avoid manually dealling with memory.
    std::string shader_src;
    size_t bytes_read = 0;
    FILE* f = fopen(path, "r");
    char read_buf[1024];
    while((bytes_read = fread(read_buf, 1, sizeof(read_buf), f)) > 0)
        shader_src += std::string(read_buf, read_buf + bytes_read);
    fclose(f);

    // Allocate GL shader handle.
    GLuint shader = glCreateShader(type);

    // Load shader source into OpenGL.
    const char* src = shader_src.c_str();
    GLint src_length = shader_src.size();
    glShaderSource(shader, 1, &src, &src_length);
    err = glGetError();
    if(err != GL_NO_ERROR) {
        printf("Error loading shader source %s: %d\n", path, err);
        return 0;
    }

    // Compile shader, report any errors.
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char buf[4096];
        GLsizei length;
        glGetShaderInfoLog(shader, sizeof(buf), &length, buf);
        printf("Unable to compile shader %s: %s\n", path, buf);
        return 0;
    }

    return shader;
}
