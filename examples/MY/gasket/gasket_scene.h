//
// Created by ivan on 26.4.2020..
//

#ifndef INCLUDED_GASKET_SCENE_H
#define INCLUDED_GASKET_SCENE_H

#include "glad/glad.h"
#include "core/window/scene.h"
#include "core/window/input.h"
#include "core/buffer/gpu_buffer.h"
#include <vector>


class gasket_scene : public mn::scene {

public:
    gasket_scene(int width, int height) : scene(width, height), buffer() {
        shader_program_id = 0;
        vertex_pos_location = 0;
        num = 0;
        vertices_per_second = 300.0f;
    }

    void initialize() override;
    void draw() override;
    void update(double seconds, const mn::input& input) override;

private:
    GLint shader_program_id;
    GLint vertex_pos_location;
    mn::gpu_buffer buffer;

    GLsizei num; // num of vertices to show
    float vertices_per_second;

    const int num_of_points = 10000;
    [[nodiscard]] std::vector<GLfloat> _rand_algorithm() const;
};

#endif //INCLUDED_GASKET_SCENE_H
