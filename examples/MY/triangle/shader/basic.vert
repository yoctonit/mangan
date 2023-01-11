#version 430

// Input vertex data in model space, different for all executions of this shader.
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

out vec3 v_color;

void main() {
    // Output position of the vertex, in clip space : MVP * position
    // gl_Position = MVP * vec4(position, 1.0);
    gl_Position = vec4(a_position, 1.0);
    v_color = a_color;
}
