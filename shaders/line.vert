#version 120

uniform vec2 inv_screen_size;

attribute vec2 position;
attribute float width;
attribute float dist;
attribute vec4 color;

varying vec4 v_color;
varying float v_width;
varying float v_dist;

void main() {
    // Transform vertices from screen space to clip space
    vec2 transformed_pos = (position * inv_screen_size) * 2.0 - vec2(1.0, 1.0);
    gl_Position = vec4(transformed_pos, 1.0, 1.0);

    // Pass over interpolated values
    v_color = color;
    v_width = width;
    v_dist = dist;
}
