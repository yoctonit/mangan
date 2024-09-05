#version 430

// Input vertex data in model space
in vec2 a_position;

uniform mat4 u_MVP;

out vec3 v_color;

void main() {
    gl_Position = u_MVP * vec4(a_position, 0.0, 1.0);
}
