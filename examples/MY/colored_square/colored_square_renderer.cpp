//
// Created by ivan on 28.4.2020..
//

#include "colored_square_renderer.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/shader/program_library.h"
#include <vector>

colored_square_renderer& colored_square_renderer::instance() {
    static colored_square_renderer _instance;
    return _instance;
}

void colored_square_renderer::initialize() {
    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program("basic.vert", "basic.frag");
    shader_program_id = program.handle();

    vertex_pos_location = program.location("a_position");
    u_MVP = program.location("u_MVP");
    u_pixel_color = program.location("u_pixel_color");

    // first 3 element specify coordinates, and next 3 color of one vertex
    const std::vector<float> vertices{
        -0.5f, 0.5f,
        -0.5f,-0.5f,
         0.5f, 0.5f,
         0.5f,-0.5f
    };

    buffer.create(vertices, GL_ARRAY_BUFFER);
    buffer.activate();

    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat), nullptr);
}

void colored_square_renderer::draw(const glm::mat4& vp, const colored_square& square) const {
    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(glm::vec3(square.position(), 0.0f)) *
            glm::scale(glm::vec3(square.width(), square.height(), 1.0f));
    glm::mat4 mvp = vp * model_matrix;

    glUseProgram(shader_program_id);
    glUniformMatrix4fv(u_MVP, 1, GL_FALSE, glm::value_ptr(mvp));
    glUniform3fv(u_pixel_color, 1, glm::value_ptr(square.color()));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
