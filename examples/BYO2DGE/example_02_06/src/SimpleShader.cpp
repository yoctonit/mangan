#include "SimpleShader.h"

SimpleShader::SimpleShader() {
    mCompiledShader = Mn::ShaderProgram::CreateFromFiles("shader/simple.vs", "shader/simple.fs");

    mVertexPositionRef = mCompiledShader.AttributeLocation("aPos");
    mPixelColorRef = mCompiledShader.UniformLocation("uPixelColor");
}

Mn::ShaderProgram SimpleShader::Shader() const {
    return mCompiledShader;
}

void SimpleShader::Activate(glm::vec4 pixelColor) const {
    glUseProgram(mCompiledShader.Id());
    Mn::ShaderProgram::Uniform(mPixelColorRef, pixelColor);
    // glUniform4f(mPixelColorRef, pixelColor.r, pixelColor.g, pixelColor.b, pixelColor.a);
}

GLuint SimpleShader::VertexPositionRef() const {
    return mVertexPositionRef;
}

GLint SimpleShader::PixelColorRef() const {
    return mPixelColorRef;
}
