#ifndef BYO2DGE_SQUARE_H
#define BYO2DGE_SQUARE_H

#include "core/Buffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


class Square {
public:
    Square();

    explicit Square(Mn::Buffer buffer);

    [[nodiscard]] Mn::Buffer Buffer() const;

    void Buffer(Mn::Buffer buffer);

    static Mn::Buffer CreateBuffer();

    static std::vector<float> SquareVertices();

private:
    Mn::Buffer mBuffer{};
};

#endif //BYO2DGE_SQUARE_H
//
////
//// Created by Ivan on 27-Jan-23.
////
//
//#ifndef OPENGL_EXAMPLES_SQUARE_H
//#define OPENGL_EXAMPLES_SQUARE_H
//
//#include <memory>
//#include "../VBO.h"
//
//class Square {
//public:
//    Square() {
//        std::vector<float> vertices = {
//                0.5f, 0.5f, 0.0f,
//                -0.5f, 0.5f, 0.0f,
//                0.5f, -0.5f, 0.0f,
//                -0.5f, -0.5f, 0.0f
//        };
//        mGLVertexBuffer = std::make_shared<Mn::VBO>(vertices);
//    }
//
//    [[nodiscard]] std::shared_ptr<Mn::VBO> get() const { return mGLVertexBuffer; }
//
//private:
//    std::shared_ptr<Mn::VBO> mGLVertexBuffer{};
//};
//
//#endif //OPENGL_EXAMPLES_SQUARE_H
