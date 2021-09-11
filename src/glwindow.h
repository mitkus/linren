#pragma once

#include <cstddef>

#include <SDL.h>

// Window with OpenGL context attached to it.
//
// Handles minimal window events to know when it is closed or ESC key pressed
// which closes the window too. GL profile is hardcoded to Core 2.0, ES 2.0
// would be preferrable but it's not supported by many desktop OS GL drivers.
// Doublebuffering and 24 bit depth buffer is also hardcoded.
class GLWindow {
public:
    // Initializes GL context and opens a window. In case of errors it crashes
    // with an assertion.
    GLWindow(const char* title, size_t width, size_t height);
    ~GLWindow();

    // Use this to override default black clear color.
    void set_clear_color(float r, float g, float b);

    // Returns true if window is open and rendering can proceed. Internally
    // this handles events and looks for ESC key or window being closed in any
    // other way.
    bool is_open();

    // Does the GL backbuffer swap.
    void present();

private:
    SDL_Window* sdl_window;
    SDL_GLContext gl_context;
};
