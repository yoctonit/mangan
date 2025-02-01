#include <cmath>
#include <vector>
#include <iostream>


#include <glm/gtc/matrix_transform.hpp>

#include "Axes.h"


Axes::Axes()
        : mShaderLoader{"shader/basic.vs.glsl", "shader/basic.fs.glsl"},
          mVao{}, mBuffer{} {
    // first 3 element specify coordinates, and next 3 color of one vertex
    const std::vector<float> vertices{
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 3.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 1.0f,
    };
    mBuffer = Mn::Vbo(vertices);
    mVao.Connect(mBuffer, 0, 3, 6, 0);
    mVao.Connect(mBuffer, 1, 3, 6, 3);
}


void Axes::Draw(const Camera &camera) const {
    glm::mat4 M = glm::mat4{1.0f};
    glm::mat4 V = camera.ViewMatrix();
    glm::mat4 P = camera.ProjectionMatrix();

    glm::mat4 MVP = P * V * M;

    mShaderLoader.Use();
    mShaderLoader.Set("u_MVP", MVP);
    mVao.Draw(GL_LINES, 0, 6);
}
