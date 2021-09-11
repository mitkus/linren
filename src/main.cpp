#include <stdio.h>

#include "vec2.h"

int main() {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(-10.0f, 3.0f);

    auto c = a + b;
    auto d = a - b;

    printf("Hello world!\n");
    printf("|c| = %f, |d| = %f\n", c.length(), d.length());
    return 0;
}
