#version 430 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform float mixValue;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures
	FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), mixValue);
}
