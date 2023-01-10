//
// Created by ivan on 04.5.2020..
//

#include "ads_scene.h"
#include "ads_renderer.h"
#include <cmath>
#include <random>

void ads_scene::initialize() {
    ads_renderer& renderer = ads_renderer::instance();
    renderer.initialize();

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(0, 10); // define the range

    // compute num_of_points
    for(int i = 0; i < 5; ++i) {
        auto ico = new mn::icosahedron();

        // pick a color at random
        float r = float(distribution(eng)) / 10.0f;
        float g = float(distribution(eng)) / 10.0f;
        float b = float(distribution(eng)) / 10.0f;

        // pick a vertex at random: all coords between -5 and 5
        int x_pos = distribution(eng); x_pos -= 5;
        int y_pos = distribution(eng); y_pos -= 5;
        int z_pos = distribution(eng); z_pos -= 5;

        ico->create(1.0f, 3, glm::vec4(r, g, b, 1.0f));
        ico->position(glm::vec3(x_pos, y_pos, z_pos));
        // ico->position(glm::vec3(0.0f, 0.0f, 0.0f));
        ico->scale(1.0f + float(distribution(eng)) / 10.0f);

        renderer.add(ico);
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void ads_scene::update(double seconds, const mn::input& input) {
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


void ads_scene::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ads_renderer& renderer = ads_renderer::instance();

    camera.calculate_view_projection();
    renderer.render(camera);
}
