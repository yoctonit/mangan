#version 430 core

uniform sampler2D image;
uniform sampler2D noise;
uniform float time;

in vec2 UV;
out vec4 fragColor;

void main()
{
    vec2 uvShift = UV + vec2( -0.033, 0.07 ) * time;
    vec4 noiseValues = texture( noise, uvShift );
    vec2 uvNoise = UV + 0.4 * noiseValues.rg;
    fragColor = texture( image, uvNoise );
}
