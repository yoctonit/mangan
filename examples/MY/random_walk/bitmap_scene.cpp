//
// Created by ivan on 8.5.2020..
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "bitmap_scene.h"
#include "core/shader/program_library.h"


int bitmap_scene::run() {
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(_width, _height, _window_title,4, 6)) {
        window.clean_up();
        return 1;
    }

    _width = window.width();
    _height = window.height();

    _bitmap_width = window.width();
    _bitmap_height = window.height();

    projection = glm::ortho(0.0f, static_cast<float>(_bitmap_width),
            0.0f, static_cast<float>(_bitmap_height));

    _init();

    window.set_scene(this);

    window.action();

    return 0;
}

void bitmap_scene::_init() {
    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "basic.vert", "basic.frag");

    shader_program_id = program.handle();
    vertex_pos_location = program.location("a_position");
    u_projection = program.location("u_projection");

    // Vertex array initialization
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    _pixel_buffer.create(2 * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    _pixel_buffer.activate();

    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}


void bitmap_scene::pixel(float x, float y) const {
    float data[2]{x, y};
    _pixel_buffer.load_data_at_offset(0, 2 * sizeof(GLfloat), data);

    glUseProgram(shader_program_id);
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_POINTS, 0, 1);
}
