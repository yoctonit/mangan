//
// Created by ivan on 2.5.2020..
//

#ifndef INCLUDED_ICOSAHEDRON_RENDERER_H
#define INCLUDED_ICOSAHEDRON_RENDERER_H

#include "glad/glad.h"
#include "core/buffer/gpu_buffer.h"
#include "model/icosahedron.h"
#include "camera/perspective_camera.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace mn {

    class icosahedron_renderer {

    public:
        static icosahedron_renderer& instance();
//        icosahedron_renderer() :
//        a_position(0), a_normal(0), vertex_array_id(0),
//        vertex_buffer(), normal_buffer() {
//            shader_program_id = 0;
//            u_light_position = 0;
//            u_Kd = 0;
//            u_Ld = 0;
//            u_model_view_matrix = 0;
//            u_normal_matrix = 0;
//            u_MVP = 0;
//        }

        void add(icosahedron* icosahedron_);

        void initialize();
        void render(const perspective_camera& camera) const;

    private:
        icosahedron_renderer() = default;
        ~icosahedron_renderer() = default;
        icosahedron_renderer(const icosahedron_renderer&) = default;
        const icosahedron_renderer& operator=(const icosahedron_renderer& lib) const {
            if (this == &lib) return *this; // self-assignment check
            return *this; // return *this anyway, because it's a singleton
        }

        GLint shader_program_id;

        //GLuint vertex_array_id;
        GLint a_position;
        GLint a_normal;

        // uniform locations in shader program
        GLint u_light_position;
        GLint u_Kd;
        GLint u_Ld;
        GLint u_model_view_matrix;
        GLint u_normal_matrix;
        GLint u_MVP;

        // mn::gpu_buffer vertex_buffer;
        // mn::gpu_buffer normal_buffer;

        std::vector<std::pair<icosahedron*, GLuint>> _objects;
        std::unordered_map<std::string, GLuint> _vao_ids;
    };

}

#endif //INCLUDED_ICOSAHEDRON_RENDERER_H
