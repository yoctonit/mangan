#ifndef OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H
#define OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H

#include "Renderable.h"
#include "Texture.h"

class TextureRenderable : public Renderable {
public:
    TextureRenderable(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &tex)
            : Renderable(ss, sq) {
        mTexture = tex;
        mElmWidthPixels = mTexture->width();
        mElmHeightPixels = mTexture->height();
        mElmLeftIndex = 0;
        mElmBottomIndex = 0;
    }

    void draw(const Camera &camera) override {
        mTexture->activate();
        mShader->activate(
                mSquareGeometryBuffer,
                mColor,
                mXform->getTRSMatrix(),
                camera.getCameraMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    std::shared_ptr<Mn::Texture> getTexture() { return mTexture; }

    void setTexture(const std::shared_ptr<Mn::Texture> &newTexture) {
        mTexture = newTexture;
        // defined for one sprite element for subclass to override
        // For texture_renderable, one sprite element is the entire texture
        mElmWidthPixels = mTexture->width();
        mElmHeightPixels = mTexture->height();
        mElmLeftIndex = 0;
        mElmBottomIndex = 0;
    }

    bool pixelTouches(const std::shared_ptr<Renderable>& other, glm::vec2& wcTouchPos) override {
        bool pixelTouch = false;
        int xIndex = 0;
        int yIndex;
        glm::ivec2 otherIndex;

        while ((!pixelTouch) && (xIndex < mElmWidthPixels)) {
            yIndex = 0;
            while ((!pixelTouch) && (yIndex < mElmHeightPixels)) {
                if (_pixelAlphaValue(xIndex, yIndex) > 0) {
                    wcTouchPos = _indexToWCPosition(xIndex, yIndex);
                    otherIndex = other->_wcPositionToIndex(wcTouchPos);
                    if ((otherIndex.x >= 0) && (otherIndex.x < other->getElmWidthPixels()) &&
                        (otherIndex.y >= 0) && (otherIndex.y < other->getElmHeightPixels())) {
                        pixelTouch = other->_pixelAlphaValue(otherIndex.x, otherIndex.y) > 0;
                    }
                }
                yIndex++;
            }
            xIndex++;
        }
        return pixelTouch;
    }

    void setColorArray() override {
        if (mColorArray.empty()) {
            mColorArray = mTexture->getColorArray();
        }
    }

    [[nodiscard]] float _pixelAlphaValue(int x, int y) const override {
        x = x * 4;
        y = y * 4;
        return mColorArray[(y * mTexture->width()) + x + 3];
    }

    glm::ivec2 _wcPositionToIndex(glm::vec2 wcPos) override {
        glm::vec2 returnIndex;
        // use wcPos to compute the corresponding returnIndex[0 and 1]
        glm::vec2 delta;
//        delta = vec2.sub(delta, wcPos, mXform.getPosition());
        delta = wcPos - mXform->getPosition();
        returnIndex.x = (float) mElmWidthPixels * (delta.x / mXform->getWidth());
        returnIndex.y = (float) mElmHeightPixels * (delta.y / mXform->getHeight());

        // recall that xForm.getPosition() returns center, yet
        // Texture origin is at lower-left corner!
        returnIndex.x += (float) mElmWidthPixels / 2;
        returnIndex.x += (float) mElmHeightPixels / 2;

//        returnIndex[0] = Math.floor(returnIndex[0]);
//        returnIndex[1] = Math.floor(returnIndex[1]);
        return glm::ivec2{std::floor(returnIndex.x), std::floor(returnIndex.y)};
    }

    glm::vec2 _indexToWCPosition(int i, int j) {
        glm::vec2 returnWCPos;
        float x = (float) i * mXform->getWidth() / (float) mElmWidthPixels;
        float y = (float) j * mXform->getHeight() / (float) mElmHeightPixels;
        returnWCPos.x = mXform->getXPos() + (x - (mXform->getWidth() * 0.5f));
        returnWCPos.y = mXform->getYPos() + (y - (mXform->getHeight() * 0.5f));
        return returnWCPos;
    }

    [[nodiscard]] int getElmWidthPixels() const override {return mElmWidthPixels; }
    [[nodiscard]] int getElmHeightPixels() const override  {return mElmHeightPixels; }

protected:
    int mElmWidthPixels;
    int mElmHeightPixels;
    int mElmLeftIndex;
    int mElmBottomIndex;

    std::shared_ptr<Mn::Texture> mTexture{};
    std::vector<unsigned char> mColorArray;
};

#endif //OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H
