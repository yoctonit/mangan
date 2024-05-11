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

    [[nodiscard]] glm::vec4 Color() const;

    void Color(glm::vec4 c);

    static Mn::Buffer CreateBuffer();

private:
    Mn::Buffer mBuffer{};
    glm::vec4 mColor{};
};

#endif //BYO2DGE_SQUARE_H
