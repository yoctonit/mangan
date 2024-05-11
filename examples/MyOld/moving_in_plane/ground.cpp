//
// Created by ivan on 17.5.2020..
//

#include <cmath>
#include <vector>

#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ground.h"
#include "core/shader/program_library.h"

void ground::initialize() {
    // first 3 element specify coordinates, and next 3 color of one vertex
    std::vector<float> vertices;

    num_of_points = 0;
    const int dimension = 50;
    const int step = 2;

    for(int i = -dimension; i <= dimension; i += step) {
        // parallel with x axis

        // 'left' side of line
        vertices.push_back(-dimension);
        vertices.push_back(0.0f);
        vertices.push_back(i);
        // red color
        vertices.push_back(1.0f);vertices.push_back(0.0f);vertices.push_back(0.0f);

        // 'right' side of line
        vertices.push_back(dimension);
        vertices.push_back(0.0f);
        vertices.push_back(i);
        // green color
        vertices.push_back(0.0f);vertices.push_back(1.0f);vertices.push_back(0.0f);

        // parallel with z axis

        // 'left' side of line
        vertices.push_back(i);
        vertices.push_back(0.0f);
        vertices.push_back(-dimension);
        // white color
        vertices.push_back(1.0f);vertices.push_back(1.0f);vertices.push_back(1.0f);

        // 'right' side of line
        vertices.push_back(i);
        vertices.push_back(0.0f);
        vertices.push_back(dimension);
        // black color
        vertices.push_back(0.0f);vertices.push_back(0.0f);vertices.push_back(0.0f);

        num_of_points += 4;
    }

    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "basic.vert", "basic.frag");

    shader_program_id = program.handle();
    vertex_pos_location = program.location("a_position");
    vertex_col_location = program.location("a_color");
    u_MVP = program.location("u_MVP");

    // Vertex array initialization
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    buffer.create(vertices, GL_ARRAY_BUFFER);
    buffer.activate();

    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(vertex_col_location);
    glVertexAttribPointer(vertex_col_location, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(GLfloat), (void*) (sizeof(float) * 3));
}


void ground::draw(const mn::perspective_camera& camera) const {
    glm::mat4 mvp = camera.vp_matrix();

    glUseProgram(shader_program_id);

    glUniformMatrix4fv(u_MVP, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_LINES, 0, num_of_points);
}
