#version 430

// Input vertex data in model space, different for all executions of this shader.
layout(location = 0) in vec2 a_position;

uniform mat4 u_projection;

void main() {
    // gl_Position = vec4(a_position, 0.0, 1.0);
    gl_Position = u_projection * vec4(a_position, 0.0, 1.0);
}
