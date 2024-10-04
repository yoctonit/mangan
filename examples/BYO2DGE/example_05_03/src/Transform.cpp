#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() {
    mPosition = glm::vec2(0.0f, 0.0f);
    mScale = glm::vec2(1.0f, 1.0f);
    mRotationInRad = 0.0f;
}

[[nodiscard]] glm::vec2 Transform::getPosition() const {
    return mPosition;
}

void Transform::setPosition(float xPos, float yPos) {
    setXPos(xPos);
    setYPos(yPos);
}

[[nodiscard]] float Transform::getXPos() const {
    return mPosition.x;
}

void Transform::setXPos(float xPos) {
    mPosition.x = xPos;
}

void Transform::incXPosBy(float delta) {
    mPosition.x += delta;
}

[[nodiscard]] float Transform::getYPos() const {
    return mPosition.y;
}

void Transform::setYPos(float yPos) {
    mPosition.y = yPos;
}

void Transform::incYPosBy(float delta) {
    mPosition.y += delta;
}

[[nodiscard]] glm::vec2 Transform::getSize() const {
    return mScale;
}

void Transform::setSize(float width, float height) {
    setWidth(width);
    setHeight(height);
}

void Transform::incSizeBy(float delta) {
    incWidthBy(delta);
    incHeightBy(delta);
}

[[nodiscard]] float Transform::getWidth() const {
    return mScale.x;
}

void Transform::setWidth(float width) {
    mScale.x = width;
}

void Transform::incWidthBy(float delta) {
    mScale.x += delta;
}

[[nodiscard]] float Transform::getHeight() const {
    return mScale.y;
}

void Transform::setHeight(float height) {
    mScale.y = height;
}

void Transform::incHeightBy(float delta) {
    mScale.y += delta;
}

[[nodiscard]] float Transform::getRotationInRad() const {
    return mRotationInRad;
}

void Transform::setRotationInRad(float rotationInRadians) {
    mRotationInRad = rotationInRadians;
    while (mRotationInRad > (2.0f * M_PI)) {
        mRotationInRad -= (2.0f * M_PI);
    }
}

void Transform::incRotationByRad(float deltaRad) {
    setRotationInRad(mRotationInRad + deltaRad);
}

[[nodiscard]] float Transform::getRotationInDegree() const {
    return mRotationInRad * 180.0f / (float) M_PI;
}

void Transform::setRotationInDegree(float rotationInDegree) {
    setRotationInRad(rotationInDegree * (float) M_PI / 180.0f);
}

void Transform::incRotationByDegree(float deltaDegree) {
    incRotationByRad(deltaDegree * (float) M_PI / 180.0f);
}

// returns the matrix the concatenates the transformations defined
[[nodiscard]] glm::mat4 Transform::getTRSMatrix() const {
    // Creates a blank identity matrix
    glm::mat4 matrix{1.0f};

    // Step A: compute translation, for now z is always at 0.0
    matrix = glm::translate(matrix, glm::vec3(getXPos(), getYPos(), 0.0f));

    // Step B: concatenate with rotation.
    matrix = glm::rotate(matrix, getRotationInRad(), glm::vec3(0.0f, 0.0f, 1.0f));

    // Step C: concatenate with scaling
    matrix = glm::scale(matrix, glm::vec3(getWidth(), getHeight(), 1.0f));

    return matrix;
}
