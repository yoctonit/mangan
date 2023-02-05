#version 430 core

uniform vec4 uPixelColor;
out vec4 FragColor;

void main()
{
    FragColor = uPixelColor;
}
