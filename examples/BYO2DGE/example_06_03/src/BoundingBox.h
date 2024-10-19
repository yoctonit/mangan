#ifndef BYO2DGE_BOUNDING_BOX_H
#define BYO2DGE_BOUNDING_BOX_H

#include <glm/vec2.hpp>

template<typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

enum class eBoundCollideStatus {
    eOutside = 0,
    eCollideLeft = 1,
    eCollideRight = 2,
    eCollideTop = 4,
    eCollideBottom = 8,
    eInside = 16
};

class BoundingBox {
public:
    BoundingBox(glm::vec2 centerPos, float width, float height) {
        mLL = glm::vec2(0.0f, 0.0f);
        setBounds(centerPos, width, height);
    }

    // rotation is ignored.
    void setBounds(glm::vec2 centerPos, float width, float height) {
        mWidth = width;
        mHeight = height;
        mLL.x = centerPos.x - (width / 2.0f);
        mLL.y = centerPos.y - (height / 2.0f);
    }

    [[nodiscard]] bool containsPoint(float x, float y) const {
        return ((x > minX()) && (x < maxX()) &&
                (y > minY()) && (y < maxY()));
    }

    [[nodiscard]] bool containsPoint(glm::vec2 point) const {
        return ((point.x > minX()) && (point.x < maxX()) &&
                (point.y > minY()) && (point.y < maxY()));
    }

    [[nodiscard]] bool intersectsBound(const BoundingBox &otherBound) const {
        return ((minX() < otherBound.maxX()) &&
                (maxX() > otherBound.minX()) &&
                (minY() < otherBound.maxY()) &&
                (maxY() > otherBound.minY()));
    }

    // returns the status of otherBound wrt to 
    [[nodiscard]] unsigned int boundCollideStatus(const BoundingBox &otherBound) const {
        unsigned int status = to_underlying(eBoundCollideStatus::eOutside);

        if (intersectsBound(otherBound)) {
            if (otherBound.minX() < minX()) {
                status |= to_underlying(eBoundCollideStatus::eCollideLeft);
            }
            if (otherBound.maxX() > maxX()) {
                status |= to_underlying(eBoundCollideStatus::eCollideRight);
            }
            if (otherBound.minY() < minY()) {
                status |= to_underlying(eBoundCollideStatus::eCollideBottom);
            }
            if (otherBound.maxY() > maxY()) {
                status |= to_underlying(eBoundCollideStatus::eCollideTop);
            }

            // if the bounds intersects and yet none of the sides overlaps
            // otherBound is completely inside thisBound
            if (status == to_underlying(eBoundCollideStatus::eOutside)) {
                status = to_underlying(eBoundCollideStatus::eInside);
            }
        }
        return status;
    }

    [[nodiscard]] float minX() const { return mLL.x; }

    [[nodiscard]] float maxX() const { return mLL.x + mWidth; }

    [[nodiscard]] float minY() const { return mLL.y; }

    [[nodiscard]] float maxY() const { return mLL.y + mHeight; }

private:
    glm::vec2 mLL{};
    float mWidth{};
    float mHeight{};
};

#endif //BYO2DGE_BOUNDING_BOX_H
