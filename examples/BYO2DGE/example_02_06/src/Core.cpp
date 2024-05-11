#include "Core.h"

void Core::Initialize() {
    BackgroundColor(glm::vec4(0.0f, 0.8f, 0.0f, 1.0f));

    mSquare.Buffer(Square::CreateBuffer());
    mSquare.Color(glm::vec4(0.8f, 0.2f, 0.0f, 1.0f));

    vao.Create();
    vao.Connect(mSquare.Buffer(), mSimpleShader.Shader(), "aPos", 3, 3, nullptr);
}

void Core::Release() {
    mSimpleShader.Shader().Release();
    mSquare.Buffer().Release();
    vao.Release();
}

void Core::Clear() const {
    glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Core::Draw() {
    Clear();

    // Step A: Activate the shader
    // mSimpleShader.Shader().Use();
    // Mn::ShaderProgram::Uniform(mSimpleShader.PixelColorRef(), mSquare.Color());
    mSimpleShader.Activate(mSquare.Color());

    // Step B: Draw with the currently activated geometry and the activated shader
    vao.Draw(GL_TRIANGLE_STRIP, 0, 4);
}

void Core::BackgroundColor(glm::vec4 color) {
    mBackgroundColor = color;
}
