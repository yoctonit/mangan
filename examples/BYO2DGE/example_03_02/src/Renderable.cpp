#include "Renderable.h"

Renderable::Renderable() = default;

Renderable::Renderable(const Mn::Vao &vao, const Mn::ShaderInfo &shader) {
    mVao = vao;
    mShader = shader;
    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Renderable::draw(glm::mat4 trsMatrix) {
    // Step A: Activate the shader
    mShader["uPixelColor"] = mColor;
    mShader["uModelXformMatrix"] = trsMatrix;
    mShader.Upload();

    // Step B: Draw with the currently activated geometry and the activated shader
    mVao.Draw(GL_TRIANGLE_STRIP, 0, 4);
}

void Renderable::setColor(glm::vec4 color) {
    mColor = color;
}

glm::vec4 Renderable::getColor() const {
    return mColor;
}

