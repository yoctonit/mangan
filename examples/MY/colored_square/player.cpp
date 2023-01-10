//
// Created by ivan on 28.4.2020..
//

#include "player.h"

void player::update(double seconds, const mn::input& input) {
    const double speed = 3.0f; // world units per second
    double displacement = seconds * speed;

    glm::vec2 pos = _square.position();

    if (input.is_pressed(mn::key::left)) {
        pos.x -= displacement;
    }
    if (input.is_pressed(mn::key::right)) {
        pos.x += displacement;
    }
    if (input.is_pressed(mn::key::up)) {
        pos.y += displacement;
    }
    if (input.is_pressed(mn::key::down)) {
        pos.y -= displacement;
    }

    _square.position(pos);
}
