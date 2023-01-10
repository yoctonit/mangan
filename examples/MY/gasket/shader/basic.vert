#version 460

// Input vertex data in model space, different for all executions of this shader.
layout(location = 0) in vec2 a_position;

void main() {
    // Output position of the vertex, in clip space : MVP * position
    // gl_Position = MVP * vec4(position, 1.0);
    gl_Position = vec4(a_position, 0.0, 1.0);
}
