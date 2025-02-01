#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(float distance, float width, float height) :
        mDistance{distance}, mWidth{width}, mHeight{height},
        mFov{1.0f}, mAspect{mWidth / mHeight},
        mNear{1.0f}, mFar{100.0} {

    glm::mat4 RotY = glm::rotate(glm::mat4{1.0f}, glm::radians(mAlpha), glm::vec3{0.0f, 1.0f, 0.0f});
    glm::vec3 temp = glm::vec3{RotY * glm::vec4{0.0f, 0.0f, mDistance, 1.0f}};
    glm::vec3 newAxis = glm::cross(temp, glm::vec3{0.0f, 1.0f, 0.0f});

    glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(mBeta), newAxis);
    M = glm::rotate(M, glm::radians(mAlpha), glm::vec3{0.0f, 1.0f, 0.0f});
    mPosition = glm::vec3{M * glm::vec4{0.0f, 0.0f, mDistance, 1.0f}};

    mViewMatrix = glm::lookAt(
            mPosition,
            glm::vec3(0.0f, 1.0f, 0.0f), // orbit camera around 0
            glm::vec3(0.0f, 1.0f, 0.0f) // up direction (orientation), for now fixed
    );

    mViewMatrix = glm::lookAt(
            mPosition,
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f) // up direction (orientation), for now fixed
    );

    mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;

    mProjectionMatrix = glm::perspective(
            mFov, // Vertical field of view in radians
            mAspect, // Aspect ratio. typically viewport width/height
            mNear, // z-distance to near plane
            mFar // z-distance to far plane
    );
}

[[nodiscard]] glm::mat4x4 Camera::ViewMatrix() const { return mViewMatrix; }

[[nodiscard]] glm::mat4x4 Camera::ProjectionMatrix() const { return mProjectionMatrix; };

[[nodiscard]] glm::mat4x4 Camera::ViewProjectionMatrix() const { return mViewProjectionMatrix; }

[[nodiscard]] bool Camera::IsTurnedOff() const { return mTurnedOff; }

void Camera::Perspective(float fov, float aspect, float near, float far) {
    mFov = fov;
    mAspect = aspect;
    mNear = near;
    mFar = far;

    mProjectionMatrix = glm::perspective(
            mFov, // Vertical field of view in radians
            mAspect, // Aspect ratio. typically viewport width/height
            mNear, // z-distance to near plane
            mFar // z-distance to far plane
    );
}

void Camera::Update(const Mn::Input &input, float deltaTime) {
    bool somethingChanged = false;
    const float movementSpeed = 10.0f;

    if (input.IsClickedKey(MN_KEY_ESCAPE)) {
        mTurnedOff = true;
        return;
    }

    float velocity = movementSpeed * deltaTime;
    if (input.IsPressedKey(MN_KEY_W)) {
        mBeta += velocity;
        somethingChanged = true;
    }
    if (input.IsPressedKey(MN_KEY_S)) {
        mBeta -= velocity;
        somethingChanged = true;
    }
    if (input.IsPressedKey(MN_KEY_A)) {
        mAlpha -= velocity;
        somethingChanged = true;
    }
    if (input.IsPressedKey(MN_KEY_D)) {
        mAlpha += velocity;
        somethingChanged = true;
    }

    // Recalculate matrices
//    if (somethingChanged) {
        glm::mat4 RotY = glm::rotate(glm::mat4{1.0f}, glm::radians(mAlpha), glm::vec3{0.0f, 1.0f, 0.0f});
        glm::vec3 temp = glm::vec3{RotY * glm::vec4{0.0f, 0.0f, mDistance, 1.0f}};
        glm::vec3 newAxis = glm::cross(temp, glm::vec3{0.0f, 1.0f, 0.0f});


//    glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(mBeta), glm::vec3{0.0f, 0.0f, 1.0f});
        glm::mat4 M = glm::rotate(glm::mat4{1.0f}, glm::radians(mBeta), newAxis);
        M = glm::rotate(M, glm::radians(mAlpha), glm::vec3{0.0f, 1.0f, 0.0f});
        mPosition = glm::vec3{M * glm::vec4{0.0f, 0.0f, mDistance, 1.0f}};

//        std::cout << "Camera position: ("
//                  << mPosition.x << ", "
//                  << mPosition.y << ", "
//                  << mPosition.z << "), angles ("
//                  << mAlpha << ", "
//                  << mBeta << ")\n";

        mViewMatrix = glm::lookAt(
                mPosition,
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f) // up direction (orientation), for now fixed
        );

        mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
//    }
}
