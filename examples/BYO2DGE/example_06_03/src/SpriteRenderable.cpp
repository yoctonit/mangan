#include "SpriteRenderable.h"

SpriteRenderable::SpriteRenderable() = default;

SpriteRenderable::SpriteRenderable(
        const Mn::Vao &vao,
        const Mn::ShaderInfo &shader,
        const Mn::Texture &texture,
        const Mn::Vbo &vbo) {
    mVao = vao;
    mVbo = vbo;
    mShader = shader;
    mTexture = texture;

    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void SpriteRenderable::draw(const Camera &camera) {
    // Step A: Activate the shader
    mShader["uModelXformMatrix"] = mXform.getTRSMatrix();
    mShader["uCameraXformMatrix"] = camera.getCameraMatrix();
    mShader["uPixelColor"] = mColor;
    mShader["uSampler"] = 0;
    mShader.Upload();

    mVbo.Load(getElementUVCoordinateArray());

    // Step B: Draw with the currently activated geometry and the activated shader
    mTexture.Activate();
    mVao.Draw(GL_TRIANGLE_STRIP, 0, 4);
}

void SpriteRenderable::setColor(glm::vec4 color) {
    mColor = color;
}

glm::vec4 SpriteRenderable::getColor() const {
    return mColor;
}

Transform &SpriteRenderable::getXform() {
    return mXform;
}

void SpriteRenderable::setTexture(const Mn::Texture &texture) {
    mTexture = texture;
}

[[nodiscard]] Mn::Texture SpriteRenderable::getTexture() const {
    return mTexture;
}

void SpriteRenderable::setElementUVCoordinate(float left, float right, float bottom, float top) {
    mElmLeft = left;
    mElmRight = right;
    mElmBottom = bottom;
    mElmTop = top;
}

void SpriteRenderable::setElementPixelPositions(float left, float right, float bottom, float top) {
    // entire image width, height
    auto imageW = static_cast<float>(mTexture.Width());
    auto imageH = static_cast<float>(mTexture.Height());

    mElmLeft = left / imageW;
    mElmRight = right / imageW;
    mElmBottom = bottom / imageH;
    mElmTop = top / imageH;
}

std::vector<float> SpriteRenderable::getElementUVCoordinateArray() const {
    return {
            mElmRight, mElmTop,          // x,y of top-right
            mElmLeft, mElmTop,
            mElmRight, mElmBottom,
            mElmLeft, mElmBottom
    };
}
