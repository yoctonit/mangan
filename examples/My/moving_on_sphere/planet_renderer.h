//
// Created by ivan on 21.5.2020..
//

#ifndef INCLUDED_PLANET_RENDERER_H
#define INCLUDED_PLANET_RENDERER_H

#include "glad/glad.h"
// #include "core/buffer/gpu_buffer.h"
#include "core/shader/shader_program.h"
#include "camera/perspective_camera.h"
#include "model/icosahedron.h"


class planet_renderer {

public:
    explicit planet_renderer(mn::icosahedron& icosahedron)
    : _icosahedron(icosahedron), program(nullptr), vertex_array_id(0) {}
    ~planet_renderer() = default;
    planet_renderer(const planet_renderer&) = default;

    void initialize();
    void render(const mn::perspective_camera& camera) const;

private:
    mn::shader_program*  program;
    GLuint vertex_array_id;

    mn::icosahedron& _icosahedron;
};

#endif //INCLUDED_PLANET_RENDERER_H
