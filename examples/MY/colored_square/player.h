//
// Created by ivan on 28.4.2020..
//

#ifndef INCLUDED_PLAYER_H
#define INCLUDED_PLAYER_H

#include "colored_square.h"
#include "core/window/input.h"

class player {
public:
    player()
    : _square(glm::vec2(0.0f, 0.0f), 1.0f, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {}

    [[nodiscard]] const colored_square& square() const { return _square; }

    void update(double seconds, const mn::input& input);
private:
    colored_square _square;
};


#endif //INCLUDED_PLAYER_H
