#include "Transform.h"

Transform::Transform() {
    mPosition = glm::vec2(0.0f, 0.0f);
    mScale = glm::vec2(1.0f, 1.0f);
    mRotationInRad = 0.0f;
}

void Transform::Position(float xPos, float yPos) {
    XPos(xPos);
    YPos(yPos);
}

[[nodiscard]] glm::vec2 Transform::Position() const {
    return mPosition;
}

[[nodiscard]] float Transform::XPos() const {
    return mPosition.x;
}

void Transform::XPos(float xPos) {
    mPosition.x = xPos;
}

void Transform::IncXPosBy(float delta) {
    mPosition.x += delta;
}

[[nodiscard]] float Transform::YPos() const {
    return mPosition.y;
}

void Transform::YPos(float yPos) {
    mPosition.y = yPos;
}

void Transform::IncYPosBy(float delta) {
    mPosition.y += delta;
}

void Transform::Size(float width, float height) {
    Width(width);
    Height(height);
}

[[nodiscard]] glm::vec2 Transform::Size() const {
    return mScale;
}

void Transform::IncSizeBy(float delta) {
    IncWidthBy(delta);
    IncHeightBy(delta);
}

[[nodiscard]] float Transform::Width() const {
    return mScale.x;
}

void Transform::Width(float width) {
    mScale.x = width;
}

void Transform::IncWidthBy(float delta) {
    mScale.x += delta;
}

[[nodiscard]] float Transform::Height() const {
    return mScale.y;
}

void Transform::Height(float height) {
    mScale.y = height;
}

void Transform::IncHeightBy(float delta) {
    mScale.y += delta;
}

[[nodiscard]] float Transform::RotationInRad() const {
    return mRotationInRad;
}

void Transform::RotationInRad(float rotationInRadians) {
    mRotationInRad = rotationInRadians;
    while (mRotationInRad > (2.0f * M_PI)) {
        mRotationInRad -= (2.0f * M_2_PI);
    }
}

void Transform::IncRotationByRad(float deltaRad) {
    RotationInRad(mRotationInRad + deltaRad);
}

[[nodiscard]] float Transform::RotationInDegree() const {
    return mRotationInRad * 180.0f / (float) M_PI;
}

void Transform::RotationInDegree(float rotationInDegree) {
    RotationInRad(rotationInDegree * (float) M_PI / 180.0f);
}

void Transform::IncRotationByDegree(float deltaDegree) {
    IncRotationByRad(deltaDegree * (float) M_PI / 180.0f);
}

// returns the matrix the concatenates the transformations defined
[[nodiscard]] glm::mat4 Transform::TRSMatrix() const {
    // Creates a blank identity matrix
    glm::mat4 matrix{1.0f};

    // The matrices that WebGL uses are transposed, thus the typical matrix
    // operations must be in reverse.

    // Step A: compute translation, for now z is always at 0.0
    matrix = glm::translate(matrix, glm::vec3(XPos(), YPos(), 0.0f));
    // mat4.translate(matrix, matrix, vec3.fromValues(this.getXPos(), this.getYPos(), 0.0));

    // Step B: concatenate with rotation.
    matrix = glm::rotate(matrix, RotationInRad(), glm::vec3(0.0f, 0.0f, 1.0f));
    // mat4.rotateZ(matrix, matrix, this.getRotationInRad());

    // Step C: concatenate with scaling
    matrix = glm::scale(matrix, glm::vec3(Width(), Height(), 1.0f));
    // mat4.scale(matrix, matrix, vec3.fromValues(this.getWidth(), this.getHeight(), 1.0));

    return matrix;
}
