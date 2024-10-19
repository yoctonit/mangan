#ifndef OPENGL_EXAMPLES_SPRITE_RENDERABLE_H
#define OPENGL_EXAMPLES_SPRITE_RENDERABLE_H

#include "TextureRenderable.h"
#include "Texture.h"

/*
 * Supports the drawing and of one sprite element mapped onto entire Renderable
 */
class SpriteRenderable : public TextureRenderable {
public:
    SpriteRenderable(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &tex)
            : TextureRenderable(ss, sq, tex) {
        mElmLeft = 0.0f;
        mElmRight = 1.0f;
        mElmTop = 1.0f;
        mElmBottom = 0.0f;
    }

    // specify element region by texture coordinate (between 0 and 1)
    void setElementUVCoordinate(float left, float right, float bottom, float top) override {
        mElmLeft = left;
        mElmRight = right;
        mElmBottom = bottom;
        mElmTop = top;
    }

// specify element region by pixel positions (between 0 to image resolutions)
    void setElementPixelPositions(float left, float right, float bottom, float top) override {
        // entire image width, height
        auto imageW = (float) mTexture->width();
        auto imageH = (float) mTexture->height();

        mElmLeft = left / imageW;
        mElmRight = right / imageW;
        mElmBottom = bottom / imageH;
        mElmTop = top / imageH;
    }

    [[nodiscard]] std::vector<float> getElementUVCoordinateArray() const override {
        return {
                mElmRight, mElmTop,          // x,y of top-right
                mElmLeft, mElmTop,
                mElmRight, mElmBottom,
                mElmLeft, mElmBottom
        };
    }

    void draw(const Camera &camera) override {
        mShader->setTextureCoordinate(getElementUVCoordinateArray());
        mTexture->activate();
        mShader->activate(
                mSquareGeometryBuffer,
                mColor,
                mXform->getTRSMatrix(),
                camera.getCameraMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

protected:
    float mElmLeft;   // bounds of texture coordinate (0 is left, 1 is right)
    float mElmRight;
    float mElmTop;    // 1 is top and 0 is bottom of image
    float mElmBottom;
};

#endif //OPENGL_EXAMPLES_SPRITE_RENDERABLE_H

// the expected texture coordinate array is an array of 8 floats where elements:
//  [0] [1]: is u/v coordinate of Top-Right
//  [2] [3]: is u/v coordinate of Top-Left
//  [4] [5]: is u/v coordinate of Bottom-Right
//  [6] [7]: is u/v coordinate of Bottom-Left
// Convention: eName is an enumerated data type
//const eTexCoordArrayIndex = Object.freeze({ eLeft: 2, eRight: 0, eTop: 1, eBottom: 5 });
