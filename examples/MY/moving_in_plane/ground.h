//
// Created by ivan on 17.5.2020..
//

#ifndef INCLUDED_GROUND_H
#define INCLUDED_GROUND_H

#include <glm/vec3.hpp>
#include "glad/glad.h"

#include "core/buffer/gpu_buffer.h"
#include "camera/perspective_camera.h"


class ground {
public:
    ground() = default;

    void initialize();
    void draw(const mn::perspective_camera& camera) const;

private:
    // for rendering
    int num_of_points;
    GLuint shader_program_id;
    GLuint vertex_array_id;
    GLuint vertex_pos_location;
    GLuint vertex_col_location;
    GLint u_MVP;

    mn::gpu_buffer buffer;

};


#endif //INCLUDED_GROUND_H
