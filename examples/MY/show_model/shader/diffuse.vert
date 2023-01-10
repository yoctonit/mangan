#version 460

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

out vec3 v_light_intensity;

uniform vec4 u_light_position; // Light position in eye coords.
uniform vec3 u_Kd;             // Diffuse reflectivity
uniform vec3 u_Ld;             // Diffuse light intensity

uniform mat4 u_model_view_matrix;
uniform mat3 u_normal_matrix;
uniform mat4 u_MVP;

void main() {
    vec3 tnorm = normalize( u_normal_matrix * a_normal);
    vec4 eye_coords = u_model_view_matrix * vec4(a_position,1.0);
    vec3 s = normalize(vec3(u_light_position - eye_coords));

    v_light_intensity = u_Ld * u_Kd * max( dot( s, tnorm ), 0.0 );

    gl_Position = u_MVP * vec4(a_position,1.0);
}
