//
// Created by ivan on 21.5.2020..
//

#ifndef INCLUDED_SPHERE_SCENE_H
#define INCLUDED_SPHERE_SCENE_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "core/window/scene.h"
#include "camera/perspective_camera.h"
#include "light/point_light.h"
#include "model/icosahedron.h"
#include "simple_spaceship.h"

class sphere_scene : public mn::scene {
public:
    sphere_scene(int width, int height)
    :
    scene(width, height), ship(), planet(),
    camera(glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3(0.0f, 0.0f, 0.0f),
           1.0f,
           glm::vec4(0.0f, 0.0f, width, height)),
    alpha(0.0f), beta(90.0f), distance(3.0f) {
        // ship_angle = 0.0f;
    }

    void initialize() override;
    void update(double seconds, const mn::input& input) override;
    void draw() override;

private:
    mn::perspective_camera camera;
    float alpha; // camera orbiting from z
    float beta; // camera orbiting from y
    float distance; // camera distance

    mn::point_light light;

    // objects in scene
    simple_spaceship ship;
    // float ship_angle;

    mn::icosahedron planet;
};

#endif //INCLUDED_SPHERE_SCENE_H
