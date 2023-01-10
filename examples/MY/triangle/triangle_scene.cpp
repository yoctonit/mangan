//
// Created by ivan on 21.4.2020..
//

#include "triangle_scene.h"
#include "core/shader/program_library.h"


void triangle_scene::initialize() {
    // first 3 element specify coordinates, and next 3 color of one vertex
    const std::vector<float> vertices{
            -0.5f,-0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.57735f,  0.0f, 0.0f, 0.0f, 1.0f
    };

    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "basic.vert", "basic.frag");
    shader_program_id = program.handle();
    vertex_pos_location = program.location("a_position");
    vertex_col_location = program.location("a_color");

    // Vertex array initialization
    GLuint vertex_array_id;
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

    glViewport(0, 0, _width, _height);
}


void triangle_scene::draw() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_id);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
