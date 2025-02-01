#version 430

in vec3 v_light_intensity;

// layout( location = 0 ) out vec4 frag_color;
out vec4 frag_color;

void main() {
    frag_color = vec4(v_light_intensity, 1.0);
}
