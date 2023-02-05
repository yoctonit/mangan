//
// Created by Ivan on 27-Jan-23.
//

#ifndef OPENGL_EXAMPLES_ENGINE_H
#define OPENGL_EXAMPLES_ENGINE_H

#include <memory>
#include "SimpleShader.h"
#include "Square.h"

class Core {
public:
    void initialize(int, int) {
        mGLVertexBuffer = std::make_shared<Square>();
        mShader = std::make_shared<SimpleShader>("shader/basic.vs", "shader/basic.fs");
        glClearColor(0.0f, 0.8f, 0.0f, 1.0f);
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT);

        // Step A: Activate the shader
        mShader->activate(mGLVertexBuffer->get(), mColor);

        // Step B: Draw with the currently activated geometry and the activated shader
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void cleanup() {}

    void Color(glm::vec4 c) { mColor = c; }

private:
    std::shared_ptr<SimpleShader> mShader{};
    std::shared_ptr<Square> mGLVertexBuffer{};
    glm::vec4 mColor{};
};

#endif //OPENGL_EXAMPLES_ENGINE_H
