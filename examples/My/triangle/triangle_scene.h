//
// Created by ivan on 21.4.2020..
//

#ifndef INCLUDED_TRIANGLE_SCENE_H
#define INCLUDED_TRIANGLE_SCENE_H

#include "glad/glad.h"
#include "core/window/scene.h"
#include "core/buffer/gpu_buffer.h"

class triangle_scene : public mn::scene {

public:
    triangle_scene(int width, int height) : scene(width, height), buffer() {
        shader_program_id = 0;
        vertex_pos_location = 0;
        vertex_col_location = 0;
    }

    void initialize() override;
    void draw() override;

private:
    GLuint shader_program_id;
    GLuint vertex_pos_location;
    GLuint vertex_col_location;
    mn::gpu_buffer buffer;
};

#endif //INCLUDED_TRIANGLE_SCENE_H
