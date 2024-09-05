//
// Created by ivan on 21.4.2020..
//

#ifndef INCLUDED_COLORED_SQUARE_SCENE_H
#define INCLUDED_COLORED_SQUARE_SCENE_H

#include "core/window/scene.h"
#include "core/window/input.h"
#include "camera/orthographic_camera.h"
#include "colored_square.h"
#include "player.h"
#include <vector>

class colored_square_scene : public mn::scene {

public:
    colored_square_scene(int width, int height) :
        scene(width, height),
        camera(0.0f, 0.0f, 10.0f,
                glm::vec4(0.0f, 0.0f, width, height)),
        _player() {}

    void initialize() override;
    void update(double seconds, const mn::input& input) override;
    void draw() override;

private:
    mn::orthographic_camera camera;

    std::vector<colored_square> _squares;
    player _player;

    void _setup_colored_squares();
};

#endif //INCLUDED_COLORED_SQUARE_SCENE_H
