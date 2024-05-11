#version 430 core

uniform vec4 uPixelColor;
uniform vec4 uGlobalAmbientColor;
uniform float uGlobalAmbientIntensity;

out vec4 FragColor;

void main()
{
    FragColor = uPixelColor * uGlobalAmbientIntensity * uGlobalAmbientColor;
}
