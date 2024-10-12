#include "SpriteAnimateRenderable.h"

SpriteAnimateRenderable::SpriteAnimateRenderable() = default;

SpriteAnimateRenderable::SpriteAnimateRenderable(
        const Mn::Vao &vao,
        const Mn::ShaderInfo &shader,
        const Mn::Texture &texture,
        const Mn::Vbo &vbo) {
    mVao = vao;
    mVbo = vbo;
    mShader = shader;
    mTexture = texture;

    mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    initAnimation();
}

void SpriteAnimateRenderable::draw(const Camera &camera) {
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

void SpriteAnimateRenderable::setColor(glm::vec4 color) {
    mColor = color;
}

glm::vec4 SpriteAnimateRenderable::getColor() const {
    return mColor;
}

Transform &SpriteAnimateRenderable::getXform() {
    return mXform;
}

void SpriteAnimateRenderable::setTexture(const Mn::Texture &texture) {
    mTexture = texture;
}

[[nodiscard]] Mn::Texture SpriteAnimateRenderable::getTexture() const {
    return mTexture;
}

void SpriteAnimateRenderable::setElementUVCoordinate(float left, float right, float bottom, float top) {
    mElmLeft = left;
    mElmRight = right;
    mElmBottom = bottom;
    mElmTop = top;
}

void SpriteAnimateRenderable::setElementPixelPositions(float left, float right, float bottom, float top) {
    // entire image width, height
    auto imageW = static_cast<float>(mTexture.Width());
    auto imageH = static_cast<float>(mTexture.Height());

    mElmLeft = left / imageW;
    mElmRight = right / imageW;
    mElmBottom = bottom / imageH;
    mElmTop = top / imageH;
}

std::vector<float> SpriteAnimateRenderable::getElementUVCoordinateArray() const {
    return {
            mElmRight, mElmTop,          // x,y of top-right
            mElmLeft, mElmTop,
            mElmRight, mElmBottom,
            mElmLeft, mElmBottom
    };
}

void SpriteAnimateRenderable::setSpriteSequence(
        int topPixel,         // offset from top-left
        int leftPixel,        // offset from top-left
        int elmWidthInPixel,
        int elmHeightInPixel,
        int numElements,      // number of elements in sequence
        int wPaddingInPixel   // left/right padding
) {
    // entire image width, height
    auto imageW = static_cast<float>(mTexture.Width());
    auto imageH = static_cast<float>(mTexture.Height());

    mNumElems = numElements; // number of elements in animation
    mFirstElmLeft = static_cast<float>(leftPixel) / imageW;
    mElmTop = static_cast<float>(topPixel) / imageH;
    mElmWidth = static_cast<float>(elmWidthInPixel) / imageW;
    mElmHeight = static_cast<float>(elmHeightInPixel) / imageH;
    mWidthPadding = static_cast<float>(wPaddingInPixel) / imageW;
    initAnimation();
}

void SpriteAnimateRenderable::setAnimationSpeed(int tickInterval) {
    mUpdateInterval = tickInterval; // how often to advance
}

void SpriteAnimateRenderable::incAnimationSpeed(int deltaInterval) {
    mUpdateInterval += deltaInterval; // how often to advance
}

void SpriteAnimateRenderable::setAnimationType(eAnimationType animationType) {
    mAnimationType = animationType;
    mCurrentAnimAdvance = -1;
    mCurrentElm = 0;
    initAnimation();
}

void SpriteAnimateRenderable::updateAnimation() {
    mCurrentTick++;
    if (mCurrentTick >= mUpdateInterval) {
        mCurrentTick = 0;
        mCurrentElm += mCurrentAnimAdvance;
        if (mCurrentElm >= 0 && mCurrentElm < mNumElems) {
            setSpriteElement();
        } else {
            initAnimation();
        }
    }
}

void SpriteAnimateRenderable::initAnimation() {
    // Currently running animation
    mCurrentTick = 0;
    switch (mAnimationType) {
        case eAnimationType::eRight:
            mCurrentElm = 0;
            mCurrentAnimAdvance = 1;
            break;
        case eAnimationType::eSwing:
            mCurrentAnimAdvance = -1 * mCurrentAnimAdvance; // swings...
            mCurrentElm += 2 * mCurrentAnimAdvance;
            break;
        case eAnimationType::eLeft:
            mCurrentElm = mNumElems - 1;
            mCurrentAnimAdvance = -1; // either 1 (to the right) or -1 (to the left)
            break;
    }
    setSpriteElement();
}

void SpriteAnimateRenderable::setSpriteElement() {
    auto currentElm = static_cast<float>(mCurrentElm);
    float left = mFirstElmLeft + (currentElm * (mElmWidth + mWidthPadding));
    setElementUVCoordinate(left, left + mElmWidth, mElmTop - mElmHeight, mElmTop);
}
