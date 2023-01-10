//
// Created by ivan on 27.4.2020..
//

#ifndef INCLUDED_ORTHOGRAPHIC_CAMERA_H
#define INCLUDED_ORTHOGRAPHIC_CAMERA_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace mn {

    class orthographic_camera {

    public:
        orthographic_camera(float world_center_x, float world_center_y,
                float world_width, glm::vec4 viewport_array);

        void world_center(float world_center_x, float world_center_y) {
            _world_center_x = world_center_x;
            _world_center_y = world_center_y;
        }
        [[nodiscard]] glm::vec2 world_center() const {
            return glm::vec2(_world_center_x, _world_center_y);
        }
        void elevation(float e) { _elevation = e; }
        [[nodiscard]] float elevation() const { return _elevation; }

        void world_width(float world_width) { _world_width = world_width; }
        [[nodiscard]] float world_width() const { return _world_width; }
        [[nodiscard]] float world_height() const {
            return _world_width * _viewport[3] / _viewport[2];
        }
        [[nodiscard]] float aspect_ratio() const { return _viewport[3] / _viewport[2]; } // ?

        void viewport(glm::vec4 viewport_array) { _viewport = viewport_array; }
        [[nodiscard]] glm::vec4 viewport() const { return _viewport; }

        void near_plane(float plane) { _near_plane = plane; }
        [[nodiscard]] float near_plane() const { return _near_plane; }
        void far_plane(float plane) { _far_plane = plane; }
        [[nodiscard]] float far_plane() const { return _far_plane; }

        [[nodiscard]] glm::mat4x4 vp_matrix() const { return _vp_matrix; };
        void calculate_view_projection();

    private:
        glm::vec4 _viewport; // [x, y, width, height]
        float _world_center_x;
        float _world_center_y;
        float _elevation; // elevation of camera above world center
        float _world_width;
        float _near_plane;
        float _far_plane;

        // transformation matrices
        glm::mat4x4 _view_matrix;
        glm::mat4x4 _proj_matrix;
        glm::mat4x4 _vp_matrix;
    };

}

#endif //INCLUDED_ORTHOGRAPHIC_CAMERA_H
