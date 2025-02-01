//
// Created by ivan on 29.4.2020..
//

#include "glad/glad.h"
#include "perspective_camera.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>


/*
 * @param position_ {vec3} camera position
 * @param look_at_ {vec3} where the camera is looking at
 * @param fovy_ {float} fovy angle
 * @param viewport_array_: an array of 4 elements:
 * [0] and [1]: (x,y) position of lower left corner on the canvas (in pixel)
 * [2] and [3]: width and height of viewport
 */
perspective_camera::perspective_camera(glm::vec3 position_, glm::vec3 look_at_,
                                       float fovy_, glm::vec4 viewport_array_) :
        _position(position_),
        _look_at(look_at_),
        _fovy(fovy_),
        _viewport(viewport_array_), // [x, y, width, height]
        _near_plane(1.0),
        _far_plane(1000.0),
        _view_matrix(glm::mat4(1.0f)),
        _proj_matrix(glm::mat4(1.0f)),
        _vp_matrix(glm::mat4(1.0f)) {}


void perspective_camera::calculate_view_projection() {
    // Set up and clear the Viewport
    glViewport(
            _viewport[0],  // x position of bottom-left corner of the area to be drawn
            _viewport[1],  // y position of bottom-left corner of the area to be drawn
            _viewport[2],  // width of the area to be drawn
            _viewport[3]   // height of the area to be drawn
    );

    // Set up the Projection-View transform operator

    // Define the view matrix
    _view_matrix = glm::lookAt(
            _position,
            _look_at,
            glm::vec3(0.0, 1.0, 0.0) // up direction (orientation), for now fixed
    );

    // Define the projection matrix
    _proj_matrix = glm::perspective(
            _fovy,          // Vertical field of view in radians
            aspect_ratio(), // Aspect ratio. typically viewport width/height
            _near_plane,    // z-distance to near plane
            _far_plane      // z-distance to far plane
    );

    // Concatenate project and view matrices
    _vp_matrix = _proj_matrix * _view_matrix;
}

