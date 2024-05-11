#version 430 core

in vec3 a_position;
in vec2 a_texture_coordinate;

out vec2 v_texture_coordinate;

uniform mat4 u_model_matrix;
uniform mat4 u_camera_matrix;

void main(void) {
    gl_Position = u_camera_matrix * u_model_matrix * vec4(a_position, 1.0);
    v_texture_coordinate = a_texture_coordinate;
}
