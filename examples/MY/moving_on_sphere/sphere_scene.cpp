//
// Created by ivan on 21.5.2020..
//

#include <cmath>

#include "glad/glad.h"
#include "core/window/input.h"
#include "renderer/ads_renderer.h"
#include "sphere_scene.h"


void sphere_scene::initialize() {
    ship.initialize();
    ship.position(glm::vec3(2.0f, 0.0f, 0.0f));
    ship.angle(0.0f);
    ship.speed(5.0f);

    planet.create(1.0f, 2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    planet.position(glm::vec3(0.0f, 0.0f, 0.0f));
    planet.scale(1.0f);

    // light.position(glm::vec4(10.0f, 10.0f, 10.0f, 1.0f));
    // light.ambient(glm::vec3(0.2f, 0.2f, 0.2f));
    // light.diffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    // light.specular(glm::vec3(1.0f, 1.0f, 1.0f));

    mn::ads_renderer& renderer = mn::ads_renderer::instance();
    renderer.initialize();
    renderer.add(&planet);

    // _position_camera();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, _width, _height);
}


void sphere_scene::update(double seconds, const mn::input& input) {
    bool key_pressed = false;

    if (input.is_pressed(mn::key::right)) {
        alpha += 1.0f;
        key_pressed = true;
    } else if (input.is_pressed(mn::key::left)) {
        alpha -= 1.0f;
        key_pressed = true;
    }

    if (input.is_pressed(mn::key::down)) {
        beta += 1.0f;
        if (beta > 179.0f) beta = 179.0f;
        key_pressed = true;
    } else if (input.is_pressed(mn::key::up)) {
        beta -= 1.0f;
        if (beta < 1.0f) beta = 1.0f;
        key_pressed = true;
    }

    if (input.is_pressed(mn::key::s)) {
        distance *= 1.05f;
        key_pressed = true;
    } else if (input.is_pressed(mn::key::w)) {
        distance /= 1.05f;
        key_pressed = true;
    }

    if (key_pressed) {
        float alpha_rad = alpha * 3.14159f / 180.0f;
        float beta_rad = beta * 3.14159f / 180.0f;
        float xz_dist = distance * std::sin(beta_rad);
        float height = distance * std::cos(beta_rad);
        float z = std::cos(alpha_rad);
        float x = std::sin(alpha_rad);
        camera.position(glm::vec3(xz_dist * x, height, xz_dist * z));
    }
}


void sphere_scene::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.calculate_view_projection();
    mn::ads_renderer& renderer = mn::ads_renderer::instance();
    renderer.render(camera, light);

    ship.draw(camera);
}
