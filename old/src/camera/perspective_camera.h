//
// Created by ivan on 29.4.2020..
//

#ifndef INCLUDED_PERSPECTIVE_CAMERA_H
#define INCLUDED_PERSPECTIVE_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace mn {

    class perspective_camera {
    public:
        perspective_camera(glm::vec3 position_, glm::vec3 look_at_, float fovy_, glm::vec4 viewport_array_);

        void position(glm::vec3 position_) { _position = position_; }
        [[nodiscard]] glm::vec3 position() const { return _position; }

        void look_at(glm::vec3 look_at_) { _look_at = look_at_; }
        [[nodiscard]] glm::vec3 look_at() const { return _look_at; }

        void fovy(float fovy_) { _fovy = fovy_; }
        [[nodiscard]] float fovy() const { return _fovy; }

        void near_plane(float plane) { _near_plane = plane; }
        [[nodiscard]] float near_plane() const { return _near_plane; }

        void far_plane(float plane) { _far_plane = plane; }
        [[nodiscard]] float far_plane() const { return _far_plane; }

        void viewport(glm::vec4 viewport_array) { _viewport = viewport_array; }
        [[nodiscard]] glm::vec4 viewport() const { return _viewport; }

        [[nodiscard]] float aspect_ratio() const { return _viewport[2] / _viewport[3]; }

        [[nodiscard]] glm::mat4x4 vp_matrix() const { return _vp_matrix; };
        [[nodiscard]] glm::mat4x4 view_matrix() const { return _view_matrix; };
        [[nodiscard]] glm::mat4x4 projection_matrix() const { return _proj_matrix; };

        void calculate_view_projection();

    private:
        glm::vec4 _viewport; // [x, y, width, height]
        glm::vec3 _position;
        glm::vec3 _look_at;
        float _fovy;
        float _near_plane;
        float _far_plane;

        // transformation matrices
        glm::mat4x4 _view_matrix;
        glm::mat4x4 _proj_matrix;
        glm::mat4x4 _vp_matrix;
    };

}

#endif //INCLUDED_PERSPECTIVE_CAMERA_H
