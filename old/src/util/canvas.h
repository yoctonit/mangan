//
// Created by ivan on 9.5.2020..
//

#ifndef INCLUDED_CANVAS_H
#define INCLUDED_CANVAS_H

#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/buffer/gpu_buffer.h"


namespace mn {

    class canvas {
    public:
        canvas(int width, int height);

        void clear(glm::vec4 color) {
            _background_color = color;
            glClearColor(_background_color.r, _background_color.g, _background_color.b, _background_color.a);
        };

        void pixel(float x, float y);

    private:
        // can be different for retina displays?
        int _bitmap_width, _bitmap_height;

        GLint shader_program_id;
        GLuint vertex_array_id;
        GLint vertex_pos_location;
        GLint u_projection;

        glm::mat4 projection;

        mn::gpu_buffer _pixel_buffer;
        int _pixel_count;
        const int MAX_PIXELS = 36000;

        glm::vec4 _background_color;

        std::function<void(const canvas&)> _draw;

        void _init();
    };

}

#endif //OPENGL_EXAMPLES_CANVAS_H
