#version 430

in vec2 tex_coords;

out vec4 color;

uniform sampler2D u_text;
uniform vec3 u_text_color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_text, tex_coords).r);
    color = vec4(u_text_color, 1.0) * sampled;
}
