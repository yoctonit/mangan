#include "TextureRenderable.h"

TextureRenderable::TextureRenderable() = default;

TextureRenderable::TextureRenderable(const Mn::Vao &vao, const Mn::ShaderInfo &shader, const Mn::Texture &texture) {
    mVao = vao;
    mShader = shader;
    mTexture = texture;

    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void TextureRenderable::draw(const Camera &camera) {
    // Step A: Activate the shader
    mShader["uModelXformMatrix"] = mXform.getTRSMatrix();
    mShader["uCameraXformMatrix"] = camera.getCameraMatrix();
    mShader["uPixelColor"] = mColor;
    mShader["uSampler"] = 0;
    mShader.Upload();

    // Step B: Draw with the currently activated geometry and the activated shader
    mTexture.Activate();
    mVao.Draw(GL_TRIANGLE_STRIP, 0, 4);
}

void TextureRenderable::setColor(glm::vec4 color) {
    mColor = color;
}

glm::vec4 TextureRenderable::getColor() const {
    return mColor;
}

Transform &TextureRenderable::getXform() {
    return mXform;
}

void TextureRenderable::setTexture(const Mn::Texture &texture) {
    mTexture = texture;
}

[[nodiscard]] Mn::Texture TextureRenderable::getTexture() const {
    return mTexture;
}
