#version 430 core

in vec3 aVertexPosition;
in vec2 aTextureCoordinate;

out vec2 vTexCoord;

// to transform the vertex position
uniform mat4 uModelXformMatrix;
uniform mat4 uCameraXformMatrix;

void main(void) {
    gl_Position = uCameraXformMatrix * uModelXformMatrix * vec4(aVertexPosition, 1.0);
    vTexCoord = aTextureCoordinate;
}
