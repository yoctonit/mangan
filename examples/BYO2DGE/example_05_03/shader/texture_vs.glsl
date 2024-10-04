#version 430 core

in vec3 aPosition;
in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 uModelXformMatrix;
uniform mat4 uCameraXformMatrix;

void main(void) {
    gl_Position = uCameraXformMatrix * uModelXformMatrix * vec4(aPosition, 1.0);
    vTexCoord = aTexCoord;
}
