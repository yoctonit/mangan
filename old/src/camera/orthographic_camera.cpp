//
// Created by ivan on 27.4.2020..
//

#include "glad/glad.h"
#include "orthographic_camera.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

namespace mn {

    orthographic_camera::orthographic_camera(
            float world_center_x, float world_center_y,
            float world_width, glm::vec4 viewport_array) :

            _world_center_x(world_center_x),
            _world_center_y(world_center_y),
            _world_width(world_width),
            _viewport(viewport_array), // [x, y, width, height]
            _elevation(10.0f),
            _near_plane(0.0f),
            _far_plane(1000.0f),
            _view_matrix(glm::mat4(1.0f)),
            _proj_matrix(glm::mat4(1.0f)),
            _vp_matrix(glm::mat4(1.0f)) {}

    void orthographic_camera::calculate_view_projection() {
        // Step A: Set up the viewport: area on canvas to be drawn
        glViewport(
                _viewport[0], // x position of bottom-left corner
                _viewport[1], // y position of bottom-left corner
                _viewport[2], // width of the area to be drawn
                _viewport[3]  // height of the area to be drawn
        );

        // Step B: Set up the View-Projection transform operator

        // Step B1: define the view matrix
        _view_matrix = glm::lookAt(
                glm::vec3(_world_center_x, _world_center_y, _elevation),
                glm::vec3(_world_center_x, _world_center_x, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
        );

        // Step B2: define the projection matrix
        float half_world_width = 0.5f * _world_width;
        float half_world_height = half_world_width * _viewport[3] / _viewport[2];

        _proj_matrix = glm::ortho(
                -half_world_width,  // distance to left of world center
                half_world_width,   // distance to right of world center
                -half_world_height, // distance to bottom of world center
                half_world_height,  // distance to top of world center
                _near_plane,        // z-distance to near plane
                _far_plane          // z-distance to far plane
        );

        // Step B3: concatenate view and projection matrices
        _vp_matrix = _proj_matrix * _view_matrix;
    }

}
