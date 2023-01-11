#version 430

#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif

uniform vec3 u_pixel_color;

out vec3 frag_color;

void main() {
    frag_color = u_pixel_color;
}
