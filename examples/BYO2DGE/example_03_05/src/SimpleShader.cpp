#include "SimpleShader.h"

SimpleShader::SimpleShader() = default;

void SimpleShader::Create() {
    mCompiledShader = Mn::ShaderProgram::CreateFromFiles("shader/simple.vs", "shader/simple.fs");

    mVertexPositionRef = mCompiledShader.AttributeLocation("aVertexPosition");
    mPixelColorRef = mCompiledShader.UniformLocation("uPixelColor");
    mModelMatrixRef = mCompiledShader.UniformLocation("uModelXformMatrix");
    mCameraMatrixRef = mCompiledShader.UniformLocation("uCameraXformMatrix");
}

void SimpleShader::Release() {
    mCompiledShader.Release();
}


Mn::ShaderProgram SimpleShader::Shader() const {
    return mCompiledShader;
}

GLuint SimpleShader::VertexPositionRef() const {
    return mVertexPositionRef;
}

GLint SimpleShader::PixelColorRef() const {
    return mPixelColorRef;
}

GLint SimpleShader::ModelMatrixRef() const {
    return mModelMatrixRef;
}

GLint SimpleShader::CameraMatrixRef() const {
    return mCameraMatrixRef;
}

void SimpleShader::Activate(glm::vec4 pixelColor, glm::mat4 trsMatrix, glm::mat4 cameraMatrix) const {
    mCompiledShader.Use();
    Mn::ShaderProgram::Uniform(mPixelColorRef, pixelColor);
    Mn::ShaderProgram::Uniform(mModelMatrixRef, trsMatrix);
    Mn::ShaderProgram::Uniform(mCameraMatrixRef, cameraMatrix);
}
//    glUseProgram(mCompiledShader);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, vb->get());
//    glVertexAttribPointer(mVertexPositionRef, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
//    glEnableVertexAttribArray(mVertexPositionRef);
//
//    // load uniforms
//    glUniform4fv(mPixelColorRef, 1, glm::value_ptr(pixelColor));
//    glUniformMatrix4fv(mModelMatrixRef, 1, GL_FALSE, glm::value_ptr(trsMatrix));
//    glUniformMatrix4fv(mCameraMatrixRef, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
//}
