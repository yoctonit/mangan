#version 430 core

layout (location = 0) in vec3 aPosition;

out vec3 TexCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoord = aPosition;
    vec4 pos = projection * view * vec4(aPosition, 1.0);
    gl_Position = pos.xyww;
}
