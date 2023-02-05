//
// Created by Ivan on 30-Jan-23.
//

#ifndef OPENGL_EXAMPLES_RENDERABLE_H
#define OPENGL_EXAMPLES_RENDERABLE_H

/*
 * Encapsulate the Shader and vertexBuffer into the same object (and will include
 * other attributes later) to represent a Renderable object on the game screen.
 */

//import * as glSys from "./core/gl.js";
#include <memory>
#include <glm/glm.hpp>
#include "ShaderResources.h"
#include "Transform.h"
#include "Camera.h"

class Renderable {
public:
    Renderable(const std::shared_ptr<SimpleShader>& ss, const std::shared_ptr<Mn::VBO>& vbo) {
        mShader = ss;
        mGLVertexBuffer = vbo;
        mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);    // color of pixel
        mXform = std::make_shared<Transform>();
    }

    void draw(const Camera& camera) {
        mShader->activate(
                mGLVertexBuffer,
                mColor,
                mXform->getTRSMatrix(),
                camera.getCameraMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void setColor(glm::vec4 color) { mColor = color; }

//    glm::vec4 getColor() { return mColor; }

    std::shared_ptr<Transform> getXform() { return mXform; }

private:
    std::shared_ptr<SimpleShader> mShader{};   // the shader for shading this object
    std::shared_ptr<Mn::VBO> mGLVertexBuffer{};
    glm::vec4 mColor{};
    std::shared_ptr<Transform> mXform;
};

#endif //OPENGL_EXAMPLES_RENDERABLE_H
