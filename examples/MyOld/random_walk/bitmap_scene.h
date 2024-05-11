//
// Created by ivan on 8.5.2020..
//

#ifndef INCLUDED_BITMAP_SCENE_H
#define INCLUDED_BITMAP_SCENE_H

#include <string>

#include <glm/glm.hpp>

#include "core/window/gl_window.h"
#include "core/buffer/gpu_buffer.h"


class bitmap_scene : public mn::scene {
public:
    bitmap_scene(int window_width, int window_height) :
    scene(window_width, window_height), _pixel_buffer(),
    shader_program_id(0), vertex_array_id(0),
    vertex_pos_location(0), u_projection(0), _window_title("Title") {}

    int run();

    void pixel(float x, float y) const;
private:
    int _bitmap_width, _bitmap_height; // can be different for retina displays?
    std::string _window_title;

    GLint shader_program_id;
    GLuint vertex_array_id;
    GLint vertex_pos_location;
    GLint u_projection;

    glm::mat4 projection;
    mn::gpu_buffer _pixel_buffer;

    void _init();

};


#endif //INCLUDED_BITMAP_SCENE_H
