#ifndef OPENGL_EXAMPLES_SQUARE_GEOMETRY_BUFFER_H
#define OPENGL_EXAMPLES_SQUARE_GEOMETRY_BUFFER_H

#include <memory>
#include "../VBO.h"

class SquareGeometryBuffer {
public:
    SquareGeometryBuffer() {
        // First: define the vertices for a square
        std::vector<float> vertices = {
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f
        };
        mGLVertexBuffer = std::make_shared<Mn::VBO>(vertices);

        // Second: define the corresponding texture coordinates
        std::vector<float> mTextureCoordinates = {
                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
        };
        mGLTextureCoordBuffer = std::make_shared<Mn::VBO>(mTextureCoordinates);
    }

    [[nodiscard]] std::shared_ptr<Mn::VBO> getVertexBuffer() const { return mGLVertexBuffer; }

    [[nodiscard]] std::shared_ptr<Mn::VBO> getTexCoordBuffer() { return mGLTextureCoordBuffer; }

private:
    std::shared_ptr<Mn::VBO> mGLVertexBuffer{};
    std::shared_ptr<Mn::VBO> mGLTextureCoordBuffer{};
};

#endif //OPENGL_EXAMPLES_SQUARE_GEOMETRY_BUFFER_H
