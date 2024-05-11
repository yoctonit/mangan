//
// Created by ivan on 23.4.2020..
//

#include "mandelbrot_scene.h"
#include "core/shader/program_library.h"
// #include "core/buffer/buffer_library.h"
#include "core/buffer/vao_library.h"
#include <iostream>


void mandelbrot_scene::initialize() {
    static const struct {
        float x, y;
    } vertices[6] = {
            {-1.0f, -1.0f },
            { 1.0f, -1.0f },
            { 1.0f,  1.0f },
            {-1.0f, -1.0f },
            { 1.0f,  1.0f },
            {-1.0f,  1.0f }
    };

    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program("mandelbrot.vert", "mandelbrot.frag");
    shader_program_id = program.handle();

    vertex_pos_location = program.location("a_position");
    u_julia_c_location = program.location("u_julia_c");
    // GLint fractal_location =
    // glGetSubroutineUniformLocation(shader_program_id, GL_FRAGMENT_SHADER, "fractal");

    u_canvas_size_location = program.location("u_canvas_size");
    u_offset_location = program.location("u_offset");
    u_scale_location = program.location("u_scale");

    mandelbrot_index = glGetSubroutineIndex(shader_program_id, GL_FRAGMENT_SHADER, "mandelbrot");
    julia_index = glGetSubroutineIndex(shader_program_id, GL_FRAGMENT_SHADER, "julia");

    // Vertex array initialization
//    glGenVertexArrays(1, &vertex_array_id);
//    glBindVertexArray(vertex_array_id);

    // NOTE: OpenGL error checks have been omitted for brevity
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    mn::vao_library& vao_lib = mn::vao_library::instance();
    vertex_array_id = vao_lib.create("mandelbrot", [this] () { _init_vao_to_buffer(); });

//    glEnableVertexAttribArray(vertex_pos_location);
//    glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE,
//            sizeof(vertices[0]), nullptr);

    glViewport(0, 0, _width, _height);
}

void mandelbrot_scene::_init_vao_to_buffer() const {
    std::cout << "called init vao to buffer\n";
    glEnableVertexAttribArray(vertex_pos_location);
    glVertexAttribPointer(vertex_pos_location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
}


void mandelbrot_scene::update(double seconds, const mn::input& input) {
    const float rate_of_change = 0.975f; // obtained experimentally with fps set to 60
    const float pan_divider = 25.0f; // obtained experimentally with fps set to 60

    if (input.is_pressed(mn::key::left)) {
        offset_x -= scale / pan_divider;
    }
    if (input.is_pressed(mn::key::right)) {
        offset_x += scale / pan_divider;
    }
    if (input.is_pressed(mn::key::up)) {
        offset_y += scale / pan_divider;
    }
    if (input.is_pressed(mn::key::down)) {
        offset_y -= scale / pan_divider;
    }

    if (input.is_pressed(mn::key::w)) {
        scale *= rate_of_change; // zoom in
    }
    if (input.is_pressed(mn::key::s)) {
        scale /= rate_of_change; // zoom out
    }

    const int NUM_OF_SCENES = 10;
    if (input.is_clicked(mn::key::d)) {
        ++scene_selection; // next fractal
        if (scene_selection > NUM_OF_SCENES - 1) scene_selection = 0;
    }
    if (input.is_clicked(mn::key::a)) {
        --scene_selection; // previous fractal
        if (scene_selection < 0) scene_selection = NUM_OF_SCENES - 1;
    }
}


void mandelbrot_scene::draw() {
    glUseProgram(shader_program_id);

    glUniform2f(u_canvas_size_location, (GLfloat)_width, (GLfloat)_height);
    glUniform2f(u_offset_location, offset_x, offset_y);
    glUniform1f(u_scale_location, scale);

    if (scene_selection == 0) {
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &mandelbrot_index);
    } else {
        float cr, ci; // fixed point for julia fractal; see fragment shader docs
        // some examples of julia fractal
        switch (scene_selection) {
            case 1: cr =  -0.4f;    ci =  0.6f;     break;
            case 2: cr =  0.285f;   ci =  0.0f;     break;
            case 3: cr =  0.285f;   ci =  0.01f;    break;
            case 4: cr =  0.45f;    ci =  0.1428f;  break;
            case 5: cr = -0.70176f; ci = -0.3842f;  break;
            case 6: cr = -0.835f;   ci = -0.2321f;  break;
            case 7: cr = -0.8f;     ci =  0.156f;   break;
            case 8: cr = -0.7269f;  ci =  0.1889f;  break;
            case 9: cr =  0.0f;     ci = -0.8f;     break;
        }
        glUniform2f(u_julia_c_location, cr, ci);
        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &julia_index);
    }
    glBindVertexArray(vertex_array_id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
