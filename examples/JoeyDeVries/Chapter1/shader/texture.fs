#version 430 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, texCoord);
	// FragColor = texture(texture1, texCoord) * vec4(ourColor, 1.0);
}
