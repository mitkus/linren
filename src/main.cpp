#include <stdio.h>

#include "glwindow.h"
#include "linerenderer.h"
#include "vec2.h"

const size_t window_width = 800;
const size_t window_height = 600;

int main() {
    GLWindow window("LineRen", window_width, window_height);
    LineRenderer lren(window_width, window_height);

    window.set_clear_color(0.5f, 0.5f, 0.5f);

    while(window.is_open()) {
        lren.clear();

        LineDef a = {
            {0.0f, 0.0f}, {100.0f, 100.0f}, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
        lren.add_lines(&a, 1);

        lren.render();
        window.present();
    }
    return 0;
}
