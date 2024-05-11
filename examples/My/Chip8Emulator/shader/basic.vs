#version 430 core

// Input vertex data in model space.
layout(location = 0) in vec2 a_position;

uniform mat4 u_camera_matrix;

void main() {
    // Output position of the vertex, in clip space: MVP * position
    gl_Position = u_camera_matrix * vec4(a_position, 0.0, 1.0);
}
