#include "glwindow.h"

#include <cassert>

#define GL_GLEXT_PROTOTYPES
#include "SDL_opengl.h"

GLWindow::GLWindow(const char* title, size_t width, size_t height) {
    SDL_Init(SDL_INIT_VIDEO);

    // Use OpenGL 2.1 profile (ES 2.0 doesn't work on macOS 11)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Set doublebuffer & depth buffer size
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    sdl_window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_OPENGL);
    assert(sdl_window);

    gl_context = SDL_GL_CreateContext(sdl_window);
    assert(gl_context);

    glViewport(0, 0, width, height);
}

GLWindow::~GLWindow() {
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void GLWindow::set_clear_color(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}

bool GLWindow::is_open() {
    bool open = true;

    // Handle OS events and quit when window is closed
    // or ESC key pressed
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            open = false;
            break;
        }
        if(e.type == SDL_WINDOWEVENT &&
           e.window.event == SDL_WINDOWEVENT_CLOSE) {
            open = false;
            break;
        }
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            open = false;
            break;
        }
    }

    return open;
}

void GLWindow::present() {
    SDL_GL_SwapWindow(sdl_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
