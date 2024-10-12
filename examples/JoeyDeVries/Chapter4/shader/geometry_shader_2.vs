#version 430 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec2 aTexCoord;

out VS_OUT {
    vec2 texCoord;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vs_out.texCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
}