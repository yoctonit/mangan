#version 430 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset;

out vec3 fColor;

void main()
{
    fColor = aColor;
    gl_Position = vec4(aPosition + aOffset, 0.0, 1.0);
}
