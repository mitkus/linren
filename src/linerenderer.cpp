#include "linerenderer.h"

#include <string>

LineRenderer::LineRenderer(size_t buffer_width,
                           size_t buffer_height,
                           size_t max_lines) {
    vert_shader = load_shader("shaders/line.vert", GL_VERTEX_SHADER);
    assert(vert_shader);

    frag_shader = load_shader("shaders/line.frag", GL_FRAGMENT_SHADER);
    assert(frag_shader);

    // Link shaders into a program
    program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    // TODO: bind attrib location
    glLinkProgram(program);
    glUseProgram(program);
    assert(glGetError() == GL_NO_ERROR);
}

LineRenderer::~LineRenderer() {}

void LineRenderer::clear() {}

void LineRenderer::add_lines(const LineDef* defs, size_t count) {}

void LineRenderer::render() {}

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
