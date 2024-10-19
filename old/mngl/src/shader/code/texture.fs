#version 430 core

in vec2 v_texture_coordinate;

uniform vec4 u_color;
uniform sampler2D u_sampler;

out vec4 frag_color;

void main()
{
    // texel color look up based on interpolated UV value in v_texture_coordinate
    // vec4 c = texture2D(u_sampler, vec2(v_texture_coordinate.s, v_texture_coordinate.t));
    vec4 c = texture2D(u_sampler, v_texture_coordinate);

    // different options:
    // e.g. tint the transparent area also
    // vec4 result = c * (1.0-u_color.a) + u_color * u_color.a;

    // or: tint the textured area, and leave transparent area as defined by the texture
    vec3 r = vec3(c) * (1.0-u_color.a) + vec3(u_color) * u_color.a;
    vec4 result = vec4(r, c.a);

    // or: ignore pixel tinting ...
    // vec4 result = c;

    // or: simply multiply pixel color with texture color
    // vec4 result = c * u_color;

    frag_color = result;
}
