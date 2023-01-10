//
// Created by ivan on 26.4.2020..
//

#include "gasket_scene.h"
#include "core/shader/program_library.h"
#include <random>


void gasket_scene::initialize() {
    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program("basic.vert", "basic.frag");
    shader_program_id = program.handle();
    vertex_pos_location = program.location("a_position");

    // Vertex array initialization
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    buffer.create(_rand_algorithm(), GL_ARRAY_BUFFER);
    buffer.activate();

    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), nullptr);

    glViewport(0, 0, _width, _height);
}


void gasket_scene::update(double seconds, const mn::input& input) {
    const float rate_of_change = 0.975f; // obtained experimentally with fps set to 60

    if (input.is_pressed(mn::key::a)) {
        num = 0; // reset animation
    }
    if (input.is_pressed(mn::key::w)) {
        vertices_per_second /= rate_of_change; // speed up
    }
    if (input.is_pressed(mn::key::s)) {
        vertices_per_second *= rate_of_change; // slow down
    }

    num += static_cast<int>(seconds * vertices_per_second);
    if (num > num_of_points) num = num_of_points;
}


void gasket_scene::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_id);
    glDrawArrays(GL_POINTS, 0, num);
}


std::vector<GLfloat> gasket_scene::_rand_algorithm() const {
    GLfloat vertices[3][2];
    // a equilateral triangle
    vertices[0][0] = -0.5f; vertices[0][1] = -0.22867f;
    vertices[1][0] =  0.5f; vertices[1][1] = -0.22867;
    vertices[2][0] =  0.0f; vertices[2][1] =  0.57735;

    std::vector<float> result{
        -0.5f,-0.22867f,
        0.5f, -0.22867f,
        0.0f, 0.57735f,
    };

    // an arbitrary initial point inside equilateral triangle defined above
    GLfloat p[2] = {0.0f, 0.22867f};

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distribution(0, 2); // define the range

    // compute num_of_points
    for(int i = 0; i < num_of_points; ++i)
    {
        int v = distribution(eng); // pick a vertex at random

        // compute point halfway between selected vertex and old point
        p[0] = (p[0] + vertices[v][0]) / 2.0;
        p[1] = (p[1] + vertices[v][1]) / 2.0;

        // add new point
        result.push_back(p[0]);
        result.push_back(p[1]);
    }

    return result;
}
