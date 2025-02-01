#ifndef INCLUDED_CAMERA_H
#define INCLUDED_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "window/Input.h"


class Camera {
public:
    Camera(float distance, float width, float height);

    [[nodiscard]] glm::mat4x4 ViewMatrix() const;

    [[nodiscard]] glm::mat4x4 ProjectionMatrix() const;

    [[nodiscard]] glm::mat4x4 ViewProjectionMatrix() const;

    [[nodiscard]] bool IsTurnedOff() const;

    void Perspective(float fov, float aspect, float near, float far);

    void Update(const Mn::Input &input, float deltaTime);

    glm::vec3 mPosition{};
private:
    float mWidth{};
    float mHeight{};
    float mFov{};
    float mAspect{};
    float mNear{};
    float mFar{};
    bool mTurnedOff{false};

    // transformation matrices
    glm::mat4x4 mViewMatrix{};
    glm::mat4x4 mProjectionMatrix{};
    glm::mat4x4 mViewProjectionMatrix{};

    float mDistance;
    float mAlpha{45.0f}; // in xz plane
    float mBeta{45.0f}; // in 'xy' plane

};

#endif //INCLUDED_CAMERA_H
