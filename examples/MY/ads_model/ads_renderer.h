//
// Created by ivan on 4.5.2020..
//

#ifndef INCLUDED_ADS_RENDERER_H
#define INCLUDED_ADS_RENDERER_H

#include "glad/glad.h"
#include "core/buffer/gpu_buffer.h"
#include "camera/perspective_camera.h"
#include "model/icosahedron.h"

#include <string>
#include <vector>
#include <unordered_map>


class ads_renderer {

public:
    static ads_renderer& instance();

    void add(mn::icosahedron* icosahedron_);

    void initialize();
    void render(const mn::perspective_camera& camera) const;

private:
    ads_renderer() = default;
    ~ads_renderer() = default;
    ads_renderer(const ads_renderer&) = default;
    const ads_renderer& operator=(const ads_renderer& renderer) const {
        if (this == &renderer) return *this; // self-assignment check
        return *this; // return *this anyway, because it's a singleton
    }

    GLint shader_program_id;

    GLint a_position;
    GLint a_normal;

    // uniform locations in shader program
    GLint u_light_position;
    GLint u_La;
    GLint u_Ld;
    GLint u_Ls;

    GLint u_Ka;
    GLint u_Kd;
    GLint u_Ks;
    float u_shininess;

    GLint u_model_view_matrix;
    GLint u_normal_matrix;
    GLint u_MVP;

    std::vector<std::pair<mn::icosahedron*, GLuint>> _objects;
    std::unordered_map<std::string, GLuint> _vao_ids;

};


#endif //INCLUDED_ADS_RENDERER_H
