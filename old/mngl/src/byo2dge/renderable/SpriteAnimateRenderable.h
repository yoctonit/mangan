#ifndef OPENGL_EXAMPLES_SPRITE_ANIMATE_RENDERABLE_H
#define OPENGL_EXAMPLES_SPRITE_ANIMATE_RENDERABLE_H

#include "SpriteRenderable.h"
#include "Texture.h"

/*
 * Supports the drawing and of one sprite element mapped onto entire Renderable
 */

//enum class eAnimationType {
//    eRight = 0,     // Animate from first (left) towards right, when hit the end, start from the left again
//    eLeft = 1,      // Compute find the last element (in the right), start from the right animate left-wards,
//    eSwing = 2      // Animate from first (left) towards the right, when hit the end, animates backwards
//};

class SpriteAnimateRenderable : public SpriteRenderable {
public:
    SpriteAnimateRenderable(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &tex)
            : SpriteRenderable(ss, sq, tex) {
// All coordinates are in texture coordinate (UV between 0 and 1)
        // Information on the sprite element 
        mFirstElmLeft = 0.0f;
        mElmTop = 1.0f;
        mElmWidth = 1.0f;
        mElmHeight = 1.0f;
        mWidthPadding = 0.0f;
        mNumElems = 1;

        // per animation settings
        mUpdateInterval = 1;   // how often to advance
        mAnimationType = eAnimationType::eRight;

        mCurrentAnimAdvance = -1;
        mCurrentElm = 0;
        _initAnimation();
    }

    // Always set the left-most element to be the first
    void setSpriteSequence(
            float topPixel,   // offset from top-left
            float leftPixel, // offset from top-left
            float elmWidthInPixel,
            float elmHeightInPixel,
            int numElements,      // number of elements in sequence
            float wPaddingInPixel  // left/right padding
    ) override {
        // entire image width, height
        auto imageW = (float) mTexture->width();
        auto imageH = (float) mTexture->height();

        mNumElems = numElements;   // number of elements in animation
        mFirstElmLeft = leftPixel / imageW;
        mElmTop = topPixel / imageH;
        mElmWidth = elmWidthInPixel / imageW;
        mElmHeight = elmHeightInPixel / imageH;
        mWidthPadding = wPaddingInPixel / imageW;
        _initAnimation();
    }

    // number of update calls before advancing the animation)
    void setAnimationSpeed(int tickInterval) override {
        mUpdateInterval = tickInterval;   // how often to advance
    }

    // number of update calls before advancing the animation
    void incAnimationSpeed(int deltaInterval) override {
        mUpdateInterval += deltaInterval;   // how often to advance
    }

    void setAnimationType(eAnimationType animationType) override {
        mAnimationType = animationType;
        mCurrentAnimAdvance = -1;
        mCurrentElm = 0;
        _initAnimation();
    }

    void updateAnimation() override {
        mCurrentTick++;
        if (mCurrentTick >= mUpdateInterval) {
            mCurrentTick = 0;
            mCurrentElm += mCurrentAnimAdvance;
            if ((mCurrentElm >= 0) && (mCurrentElm < mNumElems)) {
                _setSpriteElement();
            } else {
                _initAnimation();
            }
        }
    }

private:
    // All coordinates are in texture coordinate (UV between 0 and 1)
    // Information on the sprite element 
    float mFirstElmLeft{}; // 0.0 is left corner of image
    float mElmTop{};       // 1.0 is top corner of image (from SpriteRenderable)
    float mElmWidth{};
    float mElmHeight{};
    float mWidthPadding{};
    int mNumElems{};       // number of elements in an animation

    // per animation settings
    int mUpdateInterval{};  // how often to advance
    eAnimationType mAnimationType;

    int mCurrentAnimAdvance{};
    int mCurrentElm{};
    int mCurrentTick{};

    void _initAnimation() {
        // Currently running animation
        mCurrentTick = 0;
        switch (mAnimationType) {
            case eAnimationType::eRight:
                mCurrentElm = 0;
                mCurrentAnimAdvance = 1; // either 1 or -1
                break;
            case eAnimationType::eSwing:
                mCurrentAnimAdvance = -1 * mCurrentAnimAdvance; // swings ...
                mCurrentElm += 2 * mCurrentAnimAdvance;
                break;
            case eAnimationType::eLeft:
                mCurrentElm = mNumElems - 1;
                mCurrentAnimAdvance = -1; // either 1 or -1
                break;
        }
        _setSpriteElement();
    }

    void _setSpriteElement() {
        float left = mFirstElmLeft + ((float) mCurrentElm * (mElmWidth + mWidthPadding));
        setElementUVCoordinate(left, left + mElmWidth, mElmTop - mElmHeight, mElmTop);
    }

};

#endif //OPENGL_EXAMPLES_SPRITE_ANIMATE_RENDERABLE_H

// Assumption is that the first sprite in an animation is always the left-most element.
//const eAnimationType = Object.freeze({
//     eRight: 0,     // Animate from first (left) towards right, when hit the end, start from the left again
//     eLeft: 1,      // Compute find the last element (in the right), start from the right animate left-wards,
//     eSwing: 2      // Animate from first (left) towards the right, when hit the end, animates backwards
//});
