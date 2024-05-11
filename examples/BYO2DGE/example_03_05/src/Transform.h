#ifndef BYO2DGE_TRANSFORM_H
#define BYO2DGE_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <glm/gtc/matrix_transform.hpp>

class Transform {
public:
    Transform();

    void Position(float xPos, float yPos);

    [[nodiscard]] glm::vec2 Position() const;

    [[nodiscard]] float XPos() const;

    void XPos(float xPos);

    void IncXPosBy(float delta);

    [[nodiscard]] float YPos() const;

    void YPos(float yPos);

    void IncYPosBy(float delta);

    void Size(float width, float height);

    [[nodiscard]] glm::vec2 Size() const;

    void IncSizeBy(float delta);

    [[nodiscard]] float Width() const;

    void Width(float width);

    void IncWidthBy(float delta);

    [[nodiscard]] float Height() const;

    void Height(float height);

    void IncHeightBy(float delta);

    [[nodiscard]] float RotationInRad() const;

    void RotationInRad(float rotationInRadians);

    void IncRotationByRad(float deltaRad);

    [[nodiscard]] float RotationInDegree() const;

    void RotationInDegree(float rotationInDegree);

    void IncRotationByDegree(float deltaDegree);

    // returns the matrix the concatenates the transformations defined
    [[nodiscard]] glm::mat4 TRSMatrix() const;

private:
    glm::vec2 mPosition{};  // translation
    glm::vec2 mScale{};     // width (x), height (y)
    float mRotationInRad{}; // in radians!
};

#endif //BYO2DGE_TRANSFORM_H
