#version 430

// Input vertex data in model space, different for all executions of this shader.
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_color;

uniform mat4 u_MVP;

out vec3 v_color;

void main() {
    gl_Position = u_MVP * vec4(a_position, 1.0);
    v_color = a_color;
}
