//
// Created by Ivan on 27-Jan-23.
//

#ifndef OPENGL_EXAMPLES_SQUARE_H
#define OPENGL_EXAMPLES_SQUARE_H

#include <memory>
#include "../VBO.h"

class Square {
public:
    Square() {
        std::vector<float> vertices = {
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f
        };
        mGLVertexBuffer = std::make_shared<Mn::VBO>(vertices);
    }

    [[nodiscard]] const Mn::VBO &get() const { return *mGLVertexBuffer; }

private:
    std::shared_ptr<Mn::VBO> mGLVertexBuffer{};
};

#endif //OPENGL_EXAMPLES_SQUARE_H
