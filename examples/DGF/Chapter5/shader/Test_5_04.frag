#version 430 core

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float time;

in vec2 UV;

out vec4 fragColor;

void main()
{
    vec4 color1 = texture(texture1, UV);
    vec4 color2 = texture(texture2, UV);
    float s = abs(sin(time));
    fragColor = s * color1 + (1.0 - s) * color2;
}
