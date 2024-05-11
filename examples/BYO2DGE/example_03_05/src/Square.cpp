#include "Square.h"

Square::Square() = default;

Square::Square(Mn::Buffer buffer) : mBuffer{buffer} {}

Mn::Buffer Square::Buffer() const {
    return mBuffer;
}

void Square::Buffer(Mn::Buffer buffer) {
    mBuffer = buffer;
}

Mn::Buffer Square::CreateBuffer() {
    std::vector<float> vertices = {
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };
    return Mn::Buffer(vertices);
}

std::vector<float> Square::SquareVertices() {
    return {
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
    };
}
