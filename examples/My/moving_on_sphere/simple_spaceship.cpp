#include <vector>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "simple_spaceship.h"


bool epsilon_equal(float x, float y, float epsilon) {
    if (std::abs(x - y) <= epsilon * std::max({1.0f, std::abs(x), std::abs(y)})) {
        return true;
    }
    return false;
}

std::ostream &operator<<(std::ostream &os, const glm::vec3 v) {
    os << "("
       << (epsilon_equal(v.x, 0.0f) ? 0.0f : v.x) << ", "
       << (epsilon_equal(v.y, 0.0f) ? 0.0f : v.y) << ", "
       << (epsilon_equal(v.z, 0.0f) ? 0.0f : v.z) << ")\n";
    return os;
}

glm::vec3 sphericalCoordinates(glm::vec3 pos) {
    std::cout << "sphericalCoordinates called\n";
    float dist1 = glm::length(pos);
    float dist2 = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    std::cout << "dist1: " << dist1 << "\n";
    std::cout << "dist2: " << dist2 << "\n";

    float d = std::sqrt(pos.x * pos.x + pos.z * pos.z);
    float alpha1 = std::acos(pos.z / d);
    float alpha2 = std::asin(pos.x / d);
    float alpha3 = std::atan2(pos.x, pos.z);
    std::cout << "alpha1: " << alpha1 << "\n";
    std::cout << "alpha2: " << alpha2 << "\n";
    std::cout << "alpha3: " << alpha3 << "\n";

    float beta1 = std::acos(d / dist1);
    float beta2 = std::asin(pos.y / dist1);
    float beta3 = std::atan2(pos.y, d);
    std::cout << "beta1: " << beta1 << "\n";
    std::cout << "beta2: " << beta2 << "\n";
    std::cout << "beta3: " << beta3 << "\n";
    std::cout << "sphericalCoordinates ended\n";

    return {dist1, alpha3, beta3};
}

glm::vec3 coordinates(glm::vec3 spherical) {
    float ca = std::cos(spherical.y);
    float sa = std::sin(spherical.y);
    float cb = std::cos(spherical.z);
    float sb = std::sin(spherical.z);
    float r = spherical.x;
    return {r * sa * cb, r * sb, r * ca * cb};
}

simple_spaceship::simple_spaceship()
        : mShaderLoader{"shader/basic.vs.glsl", "shader/basic.fs.glsl"},
          mVao{}, mBuffer{} {
    // first 3 element specify coordinates, and next 3 color of one vertex
//    const std::vector<float> vertices{
//            -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//            0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
//
//            0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
//            0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//
//            -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//            0.0f, 0.3f, -0.35f, 0.0f, 0.0f, 0.5f,
//
//            0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.3f, -0.35f, 0.0f, 0.0f, 0.5f,
//            0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
//
//            -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
//            0.0f, 0.3f, -0.35f, 0.0f, 0.0f, 0.5f,
//
//            0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,
//            0.0f, 0.3f, -0.35f, 0.0f, 0.0f, 0.5f,
//            0.0f, 0.0f, -0.2f, 0.0f, 0.5f, 0.5f,
//    };
    const std::vector<float> vertices{
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.1f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.1f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    mBuffer = Mn::Vbo(vertices);
    mVao.Connect(mBuffer, 0, 3, 6, 0);
    mVao.Connect(mBuffer, 1, 3, 6, 3);

    mForward = glm::vec3{0.0f, 0.0f, 1.0f};
    mNormal = glm::vec3{0.0f, 1.0f, 0.0f};
    mRotAxis = glm::cross(mNormal, mForward);
    mPosition = mNormal;
}


void simple_spaceship::Draw(const Camera &camera) const {

    glm::mat4 vp = camera.ViewProjectionMatrix();
    // https://math.stackexchange.com/questions/878785/how-to-find-an-angle-in-range0-360-between-2-vectors

    glm::mat4 M = glm::mat4{1.0f};

//    M[0][0] = mRotAxis.x;
//    M[0][1] = mRotAxis.y;
//    M[0][2] = mRotAxis.z;
    M[0] = glm::vec4(mRotAxis, 0.0f);

//    M[1][0] = mNormal.x;
//    M[1][1] = mNormal.y;
//    M[1][2] = mNormal.z;
    M[1] = glm::vec4(mNormal, 0.0f);

//    M[2][0] = mForward.x;
//    M[2][1] = mForward.y;
//    M[2][2] = mForward.z;
    M[2] = glm::vec4(mForward, 0.0f);
//std::cout << mPosition.x << ", " << mPosition.y << ", " << mPosition.z << "\n";

    M[3] = glm::vec4(mPosition, 1.0f);
//    M[3][0] = mPosition.x;
//    M[3][1] = mPosition.y;
//    M[3][2] = mPosition.z;

    glm::mat4 mvp = vp * M;

    mShaderLoader.Use();
    mShaderLoader.Set("u_MVP", mvp);
    mVao.Draw(GL_LINES, 0, 6);
//    mVao.Draw(GL_LINES, 0, 18);
}

void simple_spaceship::Update(const Mn::Input &input, float deltaTime) {
    const float angleSpeed = 30.0f;
    const float forwardSpeed = 30.0f;

    float deltaAngle = angleSpeed * deltaTime;
    float deltaForward = forwardSpeed * deltaTime;

    if (input.IsPressedKey(MN_KEY_UP)) {
        glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(deltaForward), mRotAxis);
        glm::vec3 Nn = glm::vec3(M * glm::vec4(mNormal, 0.0f));
        glm::vec3 Fn = glm::vec3(M * glm::vec4(mForward, 0.0f));
        // glm::vec3 An = glm::cross(mNormal, Fn); // stays the same

        mForward = Fn;
        mNormal = Nn;
        mPosition = mNormal;
    }
    if (input.IsPressedKey(MN_KEY_DOWN)) {
        glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(-deltaForward), mRotAxis);
        glm::vec3 Nn = glm::vec3(M * glm::vec4(mNormal, 0.0f));
        glm::vec3 Fn = glm::vec3(M * glm::vec4(mForward, 0.0f));
        // glm::vec3 An = glm::cross(mNormal, Fn); // stays the same

        mForward = Fn;
        mNormal = Nn;
        mPosition = mNormal;
    }

    if (input.IsPressedKey(MN_KEY_RIGHT)) {
        glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(-deltaAngle), mNormal);
        glm::vec3 Fn = glm::vec3(M * glm::vec4(mForward, 0.0f));
        glm::vec3 An = glm::cross(mNormal, Fn);

        mForward = Fn;
        mRotAxis = An;
        mPosition = mNormal;
    }
    if (input.IsPressedKey(MN_KEY_LEFT)) {
        glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(deltaAngle), mNormal);
        glm::vec3 Fn = glm::vec3(M * glm::vec4(mForward, 0.0f));
        glm::vec3 An = glm::cross(mNormal, Fn);

        mForward = Fn;
        mRotAxis = An;
        mPosition = mNormal;
    }
}
