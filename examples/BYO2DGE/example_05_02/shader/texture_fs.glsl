#version 430 core

in vec2 vTexCoord;

uniform vec4 uPixelColor;
uniform sampler2D uSampler;

out vec4 FragColor;

void main() {
    // texel color look up based on interpolated UV value in vTexCoord
    vec4 c = texture2D(uSampler, vec2(vTexCoord.s, vTexCoord.t));

    // different options:
    // e.g. tint the transparent area also
    // vec4 result = c * (1.0-uPixelColor.a) + uPixelColor * uPixelColor.a;

    // or: tint the textured area, and leave transparent area as defined by the texture
    vec3 r = vec3(c) * (1.0 - uPixelColor.a) + vec3(uPixelColor) * uPixelColor.a;
    vec4 result = vec4(r, c.a);

    // or: ignore pixel tinting ...
    // vec4 result = c;

    // or: simply multiply pixel color with texture color
    // vec4 result = c * uPixelColor;

    FragColor = result;
}
