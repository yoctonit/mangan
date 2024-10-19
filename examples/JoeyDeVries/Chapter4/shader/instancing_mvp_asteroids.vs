#version 430 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoord = aTexCoord;
    gl_Position = projection * view * aInstanceMatrix * vec4(aPosition, 1.0f);
}
