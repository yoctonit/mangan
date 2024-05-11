//
// Created by ivan on 16.5.2020..
//

#include <cmath>

#include "glad/glad.h"
#include "core/window/input.h"
#include "plane_scene.h"

void plane_scene::initialize() {
    floor.initialize();

    ship.initialize();
    ship.position(glm::vec3(0.0f, 0.0f, 0.0f));
    ship.angle(0.0f);
    ship.speed(5.0f);

    camera_distance = 10.0f;
    camera_elevation = 30.0f;
    _position_camera();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glViewport(0, 0, _width, _height);
}


void plane_scene::update(double seconds, const mn::input& input) {
    if (input.is_pressed(mn::key::right)) {
        ship_angle -= 1.0f;
        if (ship_angle < -180.0f) ship_angle += 360.0f;
    } else if (input.is_pressed(mn::key::left)) {
        ship_angle += 1.0f;
        if (ship_angle > 180.0f) ship_angle -= 360.0f;
    }

    if (input.is_pressed(mn::key::up)) {
        ship.move_forward(seconds);
    } else if (input.is_pressed(mn::key::down)) {
        ship.move_backward(seconds);
    }

    ship.angle(ship_angle);

    if (input.is_pressed(mn::key::w)) {
        camera_distance -= 0.1f;
        if (camera_distance < 1.0f) camera_distance = 1.0f;
    } else if (input.is_pressed(mn::key::s)) {
        camera_distance += 0.1f;
        if (camera_distance > 100.0f) camera_distance = 100.0f;
    }

    if (input.is_pressed(mn::key::d)) {
        camera_elevation += 0.1f;
        if (camera_elevation > 90.0f) camera_elevation = 90.0f;
    } else if (input.is_pressed(mn::key::a)) {
        camera_elevation -= 0.1f;
        if (camera_elevation < 1.0f) camera_elevation = 1.0f;
    }

    _position_camera();
}


void plane_scene::draw() {
    camera.calculate_view_projection();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    floor.draw(camera);
    ship.draw(camera);
}


void plane_scene::_position_camera() {
    float elevation_rad = camera_elevation * 3.14159f / 180.0f;

    float d = camera_distance * std::cos(elevation_rad);
    float h = camera_distance * std::sin(elevation_rad);

    glm::vec3 up(0.0f, 1.0f, 0.0f);

    camera.position(ship.position() - ship.direction() * d + up * h);
    camera.look_at(ship.position());
}
