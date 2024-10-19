#ifndef BYO2DGE_SPRITE_ANIMATE_RENDERABLE_H
#define BYO2DGE_SPRITE_ANIMATE_RENDERABLE_H

#include "core/Vao.h"
#include "core/Vbo.h"
#include "graphics/ShaderInfo.h"
#include "core/Texture.h"
#include "Camera.h"
#include "Transform.h"
#include <glm/vec4.hpp>

enum class eAnimationType {
    eRight,     // Animate from first (left) towards right, when hit the end, start from the left again
    eLeft,      // Compute find the last element (in the right), start from the right animate left-wards,
    eSwing      // Animate from first (left) towards the right, when hit the end, animates backwards
};

class SpriteAnimateRenderable {
public:
    SpriteAnimateRenderable();

    SpriteAnimateRenderable(
            const Mn::Vao &vao,
            const Mn::ShaderInfo &shader,
            const Mn::Texture &texture,
            const Mn::Vbo &vbo);

    void draw(const Camera &camera);

    void setColor(glm::vec4 color);

    [[nodiscard]] glm::vec4 getColor() const;

    [[nodiscard]] Transform &getXform();

    void setTexture(const Mn::Texture &texture);

    [[nodiscard]] Mn::Texture getTexture() const;

    void setElementUVCoordinate(float left, float right, float bottom, float top);

    void setElementPixelPositions(float left, float right, float bottom, float top);

    std::vector<float> getElementUVCoordinateArray() const;

    void setSpriteSequence(
            int topPixel,         // offset from top-left
            int leftPixel,        // offset from top-left
            int elmWidthInPixel,
            int elmHeightInPixel,
            int numElements,      // number of elements in sequence
            int wPaddingInPixel   // left/right padding
    );

    void setAnimationSpeed(int tickInterval);  // number of update calls before advancing the animation

    void incAnimationSpeed(int deltaInterval); // number of update calls before advancing the animation

    void setAnimationType(eAnimationType animationType);

    void updateAnimation();

private:
    Mn::Vao mVao{};
    Mn::Vbo mVbo{};
    Mn::ShaderInfo mShader{};
    Mn::Texture mTexture{};
    glm::vec4 mColor{};
    Transform mXform{};

    // All coordinates are in texture coordinate (UV between 0 and 1)
    // Information on the sprite element
    float mFirstElmLeft{0.0f}; // 0.0 is left corner of image
    float mElmLeft{0.0f};   // bounds of texture coordinate (0 is left, 1 is right)
    float mElmRight{1.0f};
    float mElmTop{1.0f};    // 1.0 is top corner of image
    float mElmBottom{0.0f};

    float mElmWidth{1.0f};
    float mElmHeight{1.0f};
    float mWidthPadding{0.0f};
    int mNumElems{1};       // number of elements in an animation

    // per animation settings
    int mUpdateInterval{1};   // how often to advance
    eAnimationType mAnimationType{eAnimationType::eRight};

    int mCurrentAnimAdvance{-1};
    int mCurrentElm{0};
    int mCurrentTick{0};

    void initAnimation();

    void setSpriteElement();
};

#endif //BYO2DGE_SPRITE_ANIMATE_RENDERABLE_H
