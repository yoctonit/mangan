//
// Created by Ivan on 25-Feb-23.
//

#ifndef OPENGL_EXAMPLES_BOUNDING_BOX_H
#define OPENGL_EXAMPLES_BOUNDING_BOX_H

#include <glm/glm.hpp>

class eBoundCollideStatus {
public:
    static unsigned eCollideLeft;
    static unsigned eCollideRight;
    static unsigned eCollideTop;
    static unsigned eCollideBottom;
    static unsigned eInside;
    static unsigned eOutside;
};

unsigned eBoundCollideStatus::eCollideLeft = 1;
unsigned eBoundCollideStatus::eCollideRight = 2;
unsigned eBoundCollideStatus::eCollideTop = 4;
unsigned eBoundCollideStatus::eCollideBottom = 8;
unsigned eBoundCollideStatus::eInside = 16;
unsigned eBoundCollideStatus::eOutside = 0;

class BoundingBox {
    glm::vec2 mLL{};
    float mWidth{};
    float mHeight{};

public:
    BoundingBox(glm::vec2 centerPos, float w, float h) {
        mLL = glm::vec2(0.0f, 0.0f);
        setBounds(centerPos, w, h);
    }

    // rotation is ignored.
    // centerPos is a vec2
    void setBounds(glm::vec2 centerPos, float w, float h) {
        mWidth = w;
        mHeight = h;
        mLL.x = centerPos.x - (w / 2);
        mLL.y = centerPos.y - (h / 2);
    }

    [[nodiscard]] bool containsPoint(float x, float y) const {
        return ((x > minX()) && (x < maxX()) &&
                (y > minY()) && (y < maxY()));
    }

    [[nodiscard]] bool intersectsBound(const BoundingBox &otherBound) const {
        return ((minX() < otherBound.maxX()) &&
                (maxX() > otherBound.minX()) &&
                (minY() < otherBound.maxY()) &&
                (maxY() > otherBound.minY()));
    }

    // returns the status of otherBound wrt to 
    [[nodiscard]] unsigned boundCollideStatus(const BoundingBox &otherBound) const {
        unsigned status = eBoundCollideStatus::eOutside;

        if (intersectsBound(otherBound)) {
            if (otherBound.minX() < minX()) {
                status |= eBoundCollideStatus::eCollideLeft;
            }
            if (otherBound.maxX() > maxX()) {
                status |= eBoundCollideStatus::eCollideRight;
            }
            if (otherBound.minY() < minY()) {
                status |= eBoundCollideStatus::eCollideBottom;
            }
            if (otherBound.maxY() > maxY()) {
                status |= eBoundCollideStatus::eCollideTop;
            }

            // if the bounds intersects and yet none of the sides overlaps
            // otherBound is completely inside thisBound
            if (status == eBoundCollideStatus::eOutside) {
                status = eBoundCollideStatus::eInside;
            }
        }
        return status;
    }

    [[nodiscard]] float minX() const { return mLL.x; }

    [[nodiscard]] float maxX() const { return mLL.x + mWidth; }

    [[nodiscard]] float minY() const { return mLL.y; }

    [[nodiscard]] float maxY() const { return mLL.y + mHeight; }
};

#endif //OPENGL_EXAMPLES_BOUNDING_BOX_H
