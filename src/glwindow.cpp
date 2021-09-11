#include "glwindow.h"

#include <cassert>

GLWindow::GLWindow(const char* title, size_t width, size_t height) {
    SDL_Init(SDL_INIT_VIDEO);

    // Use OpenGL 2.0 profile (ES 2.0 doesn't work on macOS 11)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Set doublebuffer & depth buffer size
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    sdl_window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    assert(sdl_window);
}

GLWindow::~GLWindow() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

bool GLWindow::is_open() {
    bool open = true;

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

void GLWindow::present() { SDL_GL_SwapWindow(sdl_window); }
