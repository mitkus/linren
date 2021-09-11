#include <stdio.h>

#include "glwindow.h"
#include "vec2.h"

int main() {
    GLWindow window("LineRen", 800, 600);

    while(window.is_open()) {
        // TODO: Rendering here

        window.present();
    }
    return 0;
}
