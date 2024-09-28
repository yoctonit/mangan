#ifndef BYO2DGE_TRANSFORM_H
#define BYO2DGE_TRANSFORM_H

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class Transform {
public:
    Transform();

    [[nodiscard]] glm::vec2 getPosition() const;

    void setPosition(float xPos, float yPos);

    [[nodiscard]] float getXPos() const;

    void setXPos(float xPos);

    void incXPosBy(float delta);

    [[nodiscard]] float getYPos() const;

    void setYPos(float yPos);

    void incYPosBy(float delta);

    [[nodiscard]] glm::vec2 getSize() const;

    void setSize(float width, float height);

    void incSizeBy(float delta);

    [[nodiscard]] float getWidth() const;

    void setWidth(float width);

    void incWidthBy(float delta);

    [[nodiscard]] float getHeight() const;

    void setHeight(float height);

    void incHeightBy(float delta);

    [[nodiscard]] float getRotationInRad() const;

    void setRotationInRad(float rotationInRadians);

    void incRotationByRad(float deltaRad);

    [[nodiscard]] float getRotationInDegree() const;

    void setRotationInDegree(float rotationInDegree);

    void incRotationByDegree(float deltaDegree);

    // returns the matrix the concatenates the transformations defined
    [[nodiscard]] glm::mat4 getTRSMatrix() const;

private:
    glm::vec2 mPosition{};  // translation
    glm::vec2 mScale{};     // width (x), height (y)
    float mRotationInRad{}; // in radians!
};

#endif //BYO2DGE_TRANSFORM_H
