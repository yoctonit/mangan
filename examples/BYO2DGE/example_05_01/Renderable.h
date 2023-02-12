#ifndef OPENGL_EXAMPLES_RENDERABLE_H
#define OPENGL_EXAMPLES_RENDERABLE_H

/*
 * Encapsulate the Shader and vertexBuffer into the same object (and will include
 * other attributes later) to represent a Renderable object on the game screen.
 */
#include <memory>
#include <glm/glm.hpp>
#include "SquareGeometryBuffer.h"
#include "ShaderInterface.h"
#include "Transform.h"
#include "Camera.h"

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

    void setColor(glm::vec4 color) { mColor = color; }

    glm::vec4 getColor() { return mColor; }

    std::shared_ptr<Transform> getXform() { return mXform; }

protected:
    std::shared_ptr<ShaderInterface> mShader{};   // the shader for shading this object
    std::shared_ptr<SquareGeometryBuffer> mSquareGeometryBuffer{};
    glm::vec4 mColor{};
    std::shared_ptr<Transform> mXform;

    // void _setShader(const std::shared_ptr<SimpleShader>& s) { mShader = s; }
};

#endif //OPENGL_EXAMPLES_RENDERABLE_H
