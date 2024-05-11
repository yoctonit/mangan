#include "Renderable.h"

Renderable::Renderable() = default;

Renderable::Renderable(Mn::Vao vao, SimpleShader shader) {
    mVao = vao;
    mSimpleShader = shader;
    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    mXform = Transform();
}

void Renderable::Create(Mn::Vao vao, SimpleShader shader) {
    mVao = vao;
    mSimpleShader = shader;
    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    mXform = Transform();
}

void Renderable::Draw(const Camera &camera) const {
    mSimpleShader.Activate(mColor, mXform.TRSMatrix(), camera.CameraMatrix());
    mVao.Draw(GL_TRIANGLE_STRIP, 0, 4);
}

void Renderable::Color(glm::vec4 color) {
    mColor = color;
}

glm::vec4 Renderable::Color() const {
    return mColor;
}

Transform &Renderable::Xform() {
    return mXform;
}
