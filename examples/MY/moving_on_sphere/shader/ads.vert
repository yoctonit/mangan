#version 460

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

out vec3 v_light_intensity;

struct light_info {
    vec4 position; // Light position in eye coords.
    vec3 La; // Ambient light intensity
    vec3 Ld; // Diffuse light intensity
    vec3 Ls; // Specular light intensity
};
uniform light_info u_light;

struct material_info {
    vec3 Ka; // Ambient reflectivity
    vec3 Kd; // Diffuse reflectivity
    vec3 Ks; // Specular reflectivity
    float shininess; // specular shininess factor
};
uniform material_info u_material;

uniform mat4 u_model_view_matrix;
uniform mat3 u_normal_matrix;
uniform mat4 u_MVP;

void main() {
    vec3 tnorm = normalize( u_normal_matrix * a_normal);
    vec4 eye_coords = u_model_view_matrix * vec4(a_position,1.0);

    vec3 s = normalize(vec3(u_light.position - eye_coords));
    vec3 v = normalize(-eye_coords.xyz);
    vec3 r = reflect(-s, tnorm);

    vec3 ambient = u_light.La * u_material.Ka;

    float s_dot_n = max(dot(s, tnorm), 0.0);
    vec3 diffuse = u_light.Ld * u_material.Kd * s_dot_n;

    vec3 spec = vec3(0.0);
    if (s_dot_n > 0.0) {
        spec = u_light.Ls * u_material.Ks * pow(max(dot(r,v), 0.0), u_material.shininess);
    }

    v_light_intensity = ambient + diffuse + spec;

    gl_Position = u_MVP * vec4(a_position,1.0);
}
