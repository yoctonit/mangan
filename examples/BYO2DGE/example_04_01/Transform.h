//
// Created by Ivan on 31-Jan-23.
//

#ifndef OPENGL_EXAMPLES_TRANSFORM_H
#define OPENGL_EXAMPLES_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    Transform() {
        mPosition = glm::vec2(0.0f, 0.0f);
        mScale = glm::vec2(1.0f, 1.0f);
        mRotationInRad = 0.0f;
    }

    void setPosition(float xPos, float yPos) {
        setXPos(xPos);
        setYPos(yPos);
    }

    [[nodiscard]] glm::vec2 getPosition() const { return mPosition; }

    [[nodiscard]] float getXPos() const { return mPosition.x; }

    void setXPos(float xPos) { mPosition.x = xPos; }

    void incXPosBy(float delta) { mPosition.x += delta; }

    [[nodiscard]] float getYPos() const { return mPosition.y; }

    void setYPos(float yPos) { mPosition.y = yPos; }

    void incYPosBy(float delta) { mPosition.y += delta; }

    void setSize(float width, float height) {
        setWidth(width);
        setHeight(height);
    }

    [[nodiscard]] glm::vec2 getSize() const { return mScale; }

    void incSizeBy(float delta) {
        incWidthBy(delta);
        incHeightBy(delta);
    }

    [[nodiscard]] float getWidth() const { return mScale.x; }

    void setWidth(float width) { mScale.x = width; }

    void incWidthBy(float delta) { mScale.x += delta; }

    [[nodiscard]] float getHeight() const { return mScale.y; }

    void setHeight(float height) { mScale.y = height; }

    void incHeightBy(float delta) { mScale.y += delta; }

    void setRotationInRad(float rotationInRadians) {
        mRotationInRad = rotationInRadians;
        while (mRotationInRad > (2.0f * M_PI)) {
            mRotationInRad -= (2.0f * M_2_PI);
        }
    }

    void setRotationInDegree(float rotationInDegree) {
        setRotationInRad(rotationInDegree * (float) M_PI / 180.0f);
    }

    void incRotationByDegree(float deltaDegree) {
        incRotationByRad(deltaDegree * (float) M_PI / 180.0f);
    }

    void incRotationByRad(float deltaRad) {
        setRotationInRad(mRotationInRad + deltaRad);
    }

    [[nodiscard]] float getRotationInRad() const { return mRotationInRad; }

    [[nodiscard]] float getRotationInDegree() const { return mRotationInRad * 180.0f / (float) M_PI; }

    // returns the matrix the concatenates the transformations defined
    [[nodiscard]] glm::mat4 getTRSMatrix() const {
        // Creates a blank identity matrix
        glm::mat4 matrix{1.0f};

        // The matrices that WebGL uses are transposed, thus the typical matrix
        // operations must be in reverse.

        // Step A: compute translation, for now z is always at 0.0
        matrix = glm::translate(matrix, glm::vec3(getXPos(), getYPos(), 0.0f));
        // mat4.translate(matrix, matrix, vec3.fromValues(this.getXPos(), this.getYPos(), 0.0));

        // Step B: concatenate with rotation.
        matrix = glm::rotate(matrix, getRotationInRad(), glm::vec3(0.0f, 0.0f, 1.0f));
        // mat4.rotateZ(matrix, matrix, this.getRotationInRad());

        // Step C: concatenate with scaling
        matrix = glm::scale(matrix, glm::vec3(getWidth(), getHeight(), 1.0f));
        // mat4.scale(matrix, matrix, vec3.fromValues(this.getWidth(), this.getHeight(), 1.0));

        return matrix;
    }

private:
    glm::vec2 mPosition{};  // translation
    glm::vec2 mScale{};     // width (x), height (y)
    float mRotationInRad{}; // in radians!
};

#endif //OPENGL_EXAMPLES_TRANSFORM_H
