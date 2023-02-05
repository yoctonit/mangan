#version 430 core

in vec3 aVertexPosition;

void main(void) {
    gl_Position = vec4(aVertexPosition, 1.0);
}
