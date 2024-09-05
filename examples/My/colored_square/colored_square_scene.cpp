//
// Created by ivan on 27.4.2020..
//

#include "glad/glad.h"
#include "colored_square_scene.h"
#include "colored_square_renderer.h"


void colored_square_scene::initialize() {
    // Vertex array initialization
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    colored_square_renderer& renderer = colored_square_renderer::instance();
    renderer.initialize();

    _setup_colored_squares();
}

void colored_square_scene::update(double seconds, const mn::input& input) {
    _player.update(seconds, input);
}

void colored_square_scene::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    colored_square_renderer& renderer = colored_square_renderer::instance();

    camera.calculate_view_projection();
    glm::mat4 vp = camera.vp_matrix();

    for (const colored_square& square : _squares) {
        renderer.draw(vp, square);
    }

    renderer.draw(vp, _player.square());
}

void colored_square_scene::_setup_colored_squares() {
    _squares.emplace_back(colored_square(
            glm::vec2(-3.0f, -3.5f),
            0.5f, 1.0f,
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
    );
    _squares.emplace_back(colored_square(
            glm::vec2(-3.0f, 2.0f),
            1.0f, 0.5f,
            glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))
    );
    _squares.emplace_back(colored_square(
            glm::vec2(2.0f, 4.0f),
            1.5f, 1.5f,
            glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
    );
}
