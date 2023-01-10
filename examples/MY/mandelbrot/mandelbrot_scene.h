//
// Created by ivan on 23.4.2020..
//

#ifndef INCLUDED_MANDELBROT_SCENE_H
#define INCLUDED_MANDELBROT_SCENE_H

#include "glad/glad.h"
#include "core/window/scene.h"
#include "core/window/input.h"

class mandelbrot_scene : public mn::scene {

public:
    mandelbrot_scene(int width, int height) : scene(width, height) {
        vertex_array_id = 0;
        vertex_buffer = 0;
        shader_program_id = 0;
        vertex_pos_location = 0;
        u_canvas_size_location = 0;
        u_offset_location = 0;
        u_scale_location = 0;
        u_julia_c_location = 0;
        mandelbrot_index = 0;
        julia_index = 0;
        offset_x = -0.5f;
        offset_y = 0.0f;
        scale = 1.0f;
        scene_selection = 0;
    }

    void initialize() override;
    void draw() override;
    void update(double seconds, const mn::input& input) override;

private:
    GLuint vertex_array_id;
    GLuint vertex_buffer;
    GLint shader_program_id;
    GLint vertex_pos_location;
    GLint u_canvas_size_location;
    GLint u_offset_location;
    GLint u_scale_location;
    GLint u_julia_c_location;
    GLuint mandelbrot_index;
    GLuint julia_index;

    GLfloat offset_x;
    GLfloat offset_y;
    GLfloat scale;

    int scene_selection;

    void _init_vao_to_buffer() const;
};

#endif //INCLUDED_MANDELBROT_SCENE_H
