//
// Created by ivan on 16.5.2020.
//

#ifndef INCLUDED_SIMPLE_SPACESHIP_H
#define INCLUDED_SIMPLE_SPACESHIP_H

#include <glm/vec3.hpp>
#include "glad/glad.h"

#include "core/Vbo.h"
#include "core/Vao.h"
#include "graphics/ShaderLoader.h"
#include "Camera.h"
#include <cmath>
#include <algorithm>


bool epsilon_equal(float x, float y, float epsilon = 0.0001f);

std::ostream &operator<<(std::ostream &os, glm::vec3 v);

glm::vec3 sphericalCoordinates(glm::vec3 pos);
glm::vec3 coordinates(glm::vec3 spherical);

class simple_spaceship {
public:
    simple_spaceship();

    void Draw(const Camera &camera) const;

//    [[nodiscard]] glm::vec3 position() const;
//
//    void position(glm::vec3 new_position);
//
//    [[nodiscard]] glm::vec3 direction() const;
    // void direction(glm::vec3 new_direction);

    void Update(const Mn::Input &input, float deltaTime);

//    void move_forward(double seconds);
//
//    void move_backward(double seconds);

private:
    // for rendering
    Mn::ShaderLoader mShaderLoader;
    Mn::Vao mVao;
    Mn::Vbo mBuffer;

    glm::vec3 mPosition{};
    glm::vec3 mForward{};
    glm::vec3 mNormal{};
    glm::vec3 mRotAxis{};
};

#endif //INCLUDED_SIMPLE_SPACESHIP_H
