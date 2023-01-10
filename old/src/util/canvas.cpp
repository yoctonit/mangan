//
// Created by ivan on 9.5.2020..
//

#include "canvas.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/window/gl_window.h"
#include "core/shader/program_library.h"

namespace mn {

    canvas::canvas(int width, int height)
    : _bitmap_width(width), _bitmap_height(height),
    _pixel_buffer(), shader_program_id(0), vertex_array_id(0),
    vertex_pos_location(0), u_projection(0), _pixel_count(0),
    projection(), _draw(nullptr), _background_color()
    {
        projection = glm::ortho(0.0f, static_cast<float>(_bitmap_width),0.0f, static_cast<float>(_bitmap_height));
        _init();
    }


    void canvas::_init() {
        mn::program_library& lib = mn::program_library::instance();
        mn::shader_program& program = lib.get_program(
                "basic.vert", "basic.frag");

        shader_program_id = program.handle();
        vertex_pos_location = program.location("a_position");
        u_projection = program.location("u_projection");

        // Vertex array initialization
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        _pixel_buffer.create(2 * MAX_PIXELS * sizeof(GLfloat), GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
        _pixel_buffer.activate();

        glEnableVertexAttribArray(vertex_pos_location);
        glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }


    void canvas::pixel(float x, float y) {
        ++_pixel_count;

        if (_pixel_count > MAX_PIXELS) return;

        float data[2]{x, y};
        _pixel_buffer.load_data(2, data);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program_id);
        glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vertex_array_id);
        if (_pixel_count > 0)
            glDrawArrays(GL_POINTS, 0, _pixel_count);
    }

}
