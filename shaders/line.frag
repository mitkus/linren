#version 120

varying vec4 v_color;
varying float v_width;
varying float v_dist;

void main() {
    float coverage = 1.0f - clamp(abs(v_dist) - v_width/2.0f + 0.5f, 0.0f, 1.0f);
    gl_FragColor = vec4(v_color.xyz, v_color.w * coverage);
}
