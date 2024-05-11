#version 430 core

// Input vertex data in model space, different for all executions of this shader.
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

uniform mat4 u_model_matrix;
uniform mat4 u_camera_matrix;

out vec3 v_color;

void main() {
    // Output position of the vertex, in clip space: MVP * position
    gl_Position = u_camera_matrix * u_model_matrix * vec4(a_position, 1.0);
    v_color = a_color;
}
