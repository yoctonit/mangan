//
// Created by ivan on 16.5.2020..
//

#ifndef OPENGL_EXAMPLES_PLANE_SCENE_H
#define OPENGL_EXAMPLES_PLANE_SCENE_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "core/window/scene.h"
#include "camera/perspective_camera.h"
#include "simple_spaceship.h"
#include "ground.h"


class plane_scene : public mn::scene {
public:
    plane_scene(int width, int height) : scene(width, height), ship(), floor(),
    camera(
            glm::vec3(0.0f, 10.0f, -15.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            1.0f,
            glm::vec4(0.0f, 0.0f, width, height)
            ) {
        ship_angle = 0.0f;
        camera_distance = 0.0f;
        camera_elevation = 0.0f;
    }

    void initialize() override;
    void update(double seconds, const mn::input& input) override;
    void draw() override;

private:
    mn::perspective_camera camera;
    float camera_distance;
    float camera_elevation; // angle in degrees

    // objects in scene
    ground floor;
    simple_spaceship ship;
    float ship_angle;

    void _position_camera();
};


#endif //OPENGL_EXAMPLES_PLANE_SCENE_H
