//
// Created by ivan on 16.5.2020..
//
#include <cmath>
#include <vector>
#include <iostream>

#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "simple_spaceship.h"
#include "core/shader/program_library.h"

void simple_spaceship::initialize() {
    // first 3 element specify coordinates, and next 3 color of one vertex
    const std::vector<float> vertices{
        -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f,
         0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,

         0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
         0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f,
         0.0f, 0.3f, -0.35f,0.0f, 0.0f, 0.5f,

         0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.3f, -0.35f,0.0f, 0.0f, 0.5f,
         0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
         0.0f, 0.3f, -0.35f,0.0f, 0.0f, 0.5f,

         0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.3f, -0.35f,0.0f, 0.0f, 0.5f,
         0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
    };

    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "basic.vert", "basic.frag");

    shader_program_id = program.handle();
    std::cout << "=========== SPACESHIP =================\n";
    std::cout << "shader_program_id: " << shader_program_id << "\n";
    vertex_pos_location = program.location("a_position");
    vertex_col_location = program.location("a_color");
    u_MVP = program.location("u_MVP");

    // Vertex array initialization
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);
    std::cout << "vertex_array_id: " << vertex_array_id << "\n";
    program.print();

    buffer.create(vertices, GL_ARRAY_BUFFER);
    buffer.activate();

    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(vertex_col_location);
    glVertexAttribPointer(vertex_col_location, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), (void*) (sizeof(float) * 3));
}


void simple_spaceship::draw(const mn::perspective_camera& camera) const {
    glm::mat4 vp = camera.vp_matrix();
    glm::mat4 m =
            glm::translate(_position) *
            glm::rotate(_angle * 3.14159f / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mvp = vp * m;

    glUseProgram(shader_program_id);

    glUniformMatrix4fv(u_MVP, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_TRIANGLES, 0, 18);
}


glm::vec3 simple_spaceship::position() const {
    return _position;
}

void simple_spaceship::position(glm::vec3 new_position) {
    _position = new_position;
}

glm::vec3 simple_spaceship::direction() const {
    return _direction;
}

//void simple_spaceship::direction(glm::vec3 new_direction) {
//    _direction = new_direction;
//}

float simple_spaceship::angle() const {
    return _angle;
}

void simple_spaceship::angle(float new_angle) {
    _angle = new_angle;

    // recalculate direction
    float angle_rad = _angle * 3.14159f / 180.0f;
    float z = std::cos(angle_rad);
    float x = std::sin(angle_rad);
    _direction = glm::vec3(x, 0.0f, z);
}

float simple_spaceship::speed() const {
    return _speed;
}

void simple_spaceship::speed(float new_speed) {
    _speed = new_speed;
}

void simple_spaceship::move_forward(double seconds) {
    auto move_units = static_cast<float>(_speed * seconds);
    _position += move_units * _direction;
}

void simple_spaceship::move_backward(double seconds) {
    auto move_units = static_cast<float>(_speed * seconds);
    _position -= move_units * _direction;
}
