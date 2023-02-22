#ifndef OPENGL_EXAMPLES_RENDERABLE_H
#define OPENGL_EXAMPLES_RENDERABLE_H

#include <memory>
#include <glm/glm.hpp>
#include "../SquareGeometryBuffer.h"
#include "../shader/ShaderInterface.h"
#include "../Transform.h"
#include "../Camera.h"

enum class eAnimationType {
    eRight = 0,     // Animate from first (left) towards right, when hit the end, start from the left again
    eLeft = 1,      // Compute find the last element (in the right), start from the right animate left-wards,
    eSwing = 2      // Animate from first (left) towards the right, when hit the end, animates backwards
};

/*
 * Encapsulate the Shader and vertexBuffer into the same object (and will include
 * other attributes later) to represent a Renderable object on the game screen.
 */
class Renderable {
public:
    Renderable(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq) {
        mShader = ss;
        mSquareGeometryBuffer = sq;
        mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        mXform = std::make_shared<Transform>();
    }

    virtual void draw(const Camera &camera) {
        mShader->activate(
                mSquareGeometryBuffer,
                mColor,
                mXform->getTRSMatrix(),
                camera.getCameraMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    virtual void setElementPixelPositions(float left, float right, float bottom, float top) {}

    virtual void setElementUVCoordinate(float left, float right, float bottom, float top) {}

    [[nodiscard]] virtual std::vector<float> getElementUVCoordinateArray() const { return {}; }

    virtual void setSpriteSequence(
            float topPixel,   // offset from top-left
            float leftPixel, // offset from top-left
            float elmWidthInPixel,
            float elmHeightInPixel,
            int numElements,      // number of elements in sequence
            float wPaddingInPixel  // left/right padding
    ) {}

    virtual void setAnimationType(eAnimationType animationType) {}

    virtual void setAnimationSpeed(int tickInterval) {}

    virtual void updateAnimation() {}
    virtual void incAnimationSpeed(int deltaInterval) {}
    void setColor(glm::vec4 color) { mColor = color; }

    glm::vec4 getColor() { return mColor; }

    std::shared_ptr<Transform> getXform() { return mXform; }

protected:
    std::shared_ptr<ShaderInterface> mShader{};   // the shader for shading this object
    std::shared_ptr<SquareGeometryBuffer> mSquareGeometryBuffer{};
    glm::vec4 mColor{};
    std::shared_ptr<Transform> mXform;
};

#endif //OPENGL_EXAMPLES_RENDERABLE_H
