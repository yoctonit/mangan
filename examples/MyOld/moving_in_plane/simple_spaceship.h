//
// Created by ivan on 16.5.2020..
//

#ifndef INCLUDED_SIMPLE_SPACESHIP_H
#define INCLUDED_SIMPLE_SPACESHIP_H

#include <glm/vec3.hpp>
#include "glad/glad.h"

#include "core/buffer/gpu_buffer.h"
#include "camera/perspective_camera.h"

class simple_spaceship {
public:
    simple_spaceship() = default;

    void initialize();
    void draw(const mn::perspective_camera& camera) const;

    [[nodiscard]] glm::vec3 position() const;
    void position(glm::vec3 new_position);

    [[nodiscard]] glm::vec3 direction() const;
    // void direction(glm::vec3 new_direction);

    [[nodiscard]] float angle() const;
    void angle(float new_angle);

    [[nodiscard]] float speed() const;
    void speed(float new_speed);

    void move_forward(double seconds);
    void move_backward(double seconds);

private:
    glm::vec3 _position;
    glm::vec3 _direction;
    float _angle; // in degrees
    float _speed; // units per second

    // for rendering
    GLuint shader_program_id;
    GLuint vertex_array_id;
    GLuint vertex_pos_location;
    GLuint vertex_col_location;
    GLint u_MVP;

    mn::gpu_buffer buffer;
};


#endif //INCLUDED_SIMPLE_SPACESHIP_H
