//
// Created by ivan on 30.4.2020..
//

#ifndef INCLUDED_MODEL_SCENE_H
#define INCLUDED_MODEL_SCENE_H

// #include "glad/glad.h"
#include "core/window/scene.h"
#include "core/window/input.h"
#include "camera/perspective_camera.h"
#include "model/icosahedron.h"


class model_scene : public mn::scene {

public:
    model_scene(int width, int height) : scene(width, height),
    camera(glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            1.0f,
            glm::vec4(0.0f, 0.0f, width, height)),
            alpha(0.0f), beta(90.0f), distance(3.0f) {}

    void initialize() override;
    void update(double seconds, const mn::input& input) override;
    void draw() override;

private:
    mn::perspective_camera camera;
    float alpha; // camera orbiting from z
    float beta; // camera orbiting from y
    float distance; // camera distance

    mn::icosahedron icosahedron;
    mn::icosahedron icosahedron2;

    // mn::icosahedron_renderer renderer;
};

#endif //INCLUDED_MODEL_SCENE_H
