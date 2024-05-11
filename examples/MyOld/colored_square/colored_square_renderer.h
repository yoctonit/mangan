//
// Created by ivan on 28.4.2020..
//

#ifndef INCLUDED_COLORED_SQUARE_RENDERER_H
#define INCLUDED_COLORED_SQUARE_RENDERER_H

#include "glad/glad.h"
#include <glm/mat4x4.hpp>
#include "core/buffer/gpu_buffer.h"
#include "colored_square.h"


class colored_square_renderer {

public:
    static colored_square_renderer& instance();

    void initialize();
    void draw(const glm::mat4& vp, const colored_square& square) const;

private:
    colored_square_renderer() = default;
    ~colored_square_renderer() = default;
    colored_square_renderer(const colored_square_renderer&) = default;
    const colored_square_renderer& operator=(const colored_square_renderer& renderer) const {
        if (this == &renderer) return *this; // self-assignment check
        return *this; // return *this anyway, because it's a singleton
    }

    GLint shader_program_id;
    GLint vertex_pos_location;
    GLint u_MVP;
    GLint u_pixel_color;
    mn::gpu_buffer buffer;
};

#endif //OPENGL_EXAMPLES_COLORED_SQUARE_RENDERER_H
