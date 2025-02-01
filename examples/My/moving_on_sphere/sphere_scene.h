//
// Created by ivan on 21.5.2020..
//

#ifndef INCLUDED_SPHERE_SCENE_H
#define INCLUDED_SPHERE_SCENE_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Camera.h"
#include "point_light.h"
#include "simple_spaceship.h"
#include "Planet.h"
#include "Axes.h"

#include "window/Input.h"

class sphere_scene {
public:
    sphere_scene(int width, int height)
            :
            mWidth{width}, mHeight{height},
            mAxes(), mShip(), mPlanet(1.0f),
            mCamera(3.0f, static_cast<float>(width), static_cast<float>(height)) {}

    void initialize();

    void update(const Mn::Input &input, float seconds);

    void draw();

private:
    int mWidth;
    int mHeight;

    Camera mCamera;
    point_light mLight;

    // objects in scene
    Axes mAxes;
    simple_spaceship mShip;
    Planet mPlanet;
};

#endif //INCLUDED_SPHERE_SCENE_H
