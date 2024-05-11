//
// Created by ivan on 27.4.2020..
//

#ifndef INCLUDED_COLORED_SQUARE_H
#define INCLUDED_COLORED_SQUARE_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

class colored_square {
public:
    colored_square(glm::vec2 pos, float w, float h, glm::vec4 c) :
    _position(pos), _width(w), _height(h), _color(c) {}

    void position(glm::vec2 pos) { _position = pos; }
    [[nodiscard]] glm::vec2 position() const { return _position; }

    void width(float w) { _width = w; }
    [[nodiscard]] float width() const { return _width; }

    void height(float h) { _height = h; }
    [[nodiscard]] float height() const { return _height; }

    void color(glm::vec4 c) { _color = c; }
    [[nodiscard]] glm::vec4 color() const { return _color; }

private:
    glm::vec2 _position;
    float _width;
    float _height;
    glm::vec4 _color;
};

#endif //INCLUDED_COLORED_SQUARE_H
