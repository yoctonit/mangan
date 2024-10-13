#ifndef BYO2DGE_BRAIN_H
#define BYO2DGE_BRAIN_H

#include "../src/Core.h"
#include "../src/GameObject.h"
#include "../src/SpriteRenderable.h"
#include <glm/gtc/matrix_transform.hpp>

class Brain {
public:
    Brain(const Core &engine, const Mn::Texture &texture) {
        mRenderComponent = engine.createSpriteRenderable(texture);
        mRenderComponent.setColor({1.0f, 1.0f, 1.0f, 0.0f});
        mRenderComponent.getXform().setPosition(50.0f, 10.0f);
        mRenderComponent.getXform().setSize(3.0f, 5.4f);
        mRenderComponent.setElementPixelPositions(600.0f, 700.0f, 0.0f, 180.0f);

        mCurrentFrontDir = glm::vec2{0.0f, 1.0f};
        mSpeed = 0.05f;
        mVisible = true;
    }

    void update() {
        // simple default behavior
        glm::vec2 pos = mRenderComponent.getXform().getPosition();
        pos += getSpeed() * getCurrentFrontDir();
        mRenderComponent.getXform().setPosition(pos);
    }

    void update(const Mn::Input &input) {
        update();
        Transform &xf = mRenderComponent.getXform();
        // glm::vec2 frontDir = getCurrentFrontDir();

        const float kDeltaDegree = 1.0f;
        const float kDeltaRad = 3.1415f * kDeltaDegree / 180.0f;
        const float kDeltaSpeed = 0.01f;

        if (input.IsPressedKey(MN_KEY_LEFT)) {
            xf.incRotationByDegree(kDeltaDegree);
            auto m = glm::rotate(glm::mat4{1.0f}, kDeltaRad, glm::vec3(0.0f, 0.0f, 1.0f));
            auto f = m * glm::vec4(getCurrentFrontDir(), 0.0f, 1.0f);
            setCurrentFrontDir(glm::vec2{f.x, f.y});
        }
        if (input.IsPressedKey(MN_KEY_RIGHT)) {
            xf.incRotationByDegree(-kDeltaDegree);
            auto m = glm::rotate(glm::mat4{1.0f}, -kDeltaRad, glm::vec3(0.0f, 0.0f, 1.0f));
            auto f = m * glm::vec4(getCurrentFrontDir(), 0.0f, 1.0f);
            setCurrentFrontDir(glm::vec2{f.x, f.y});
        }
        if (input.IsPressedKey(MN_KEY_UP)) {
            incSpeedBy(kDeltaSpeed);
        }
        if (input.IsPressedKey(MN_KEY_DOWN)) {
            incSpeedBy(-kDeltaSpeed);
        }
    }

    void draw(const Camera &camera) {
        if (isVisible()) {
            mRenderComponent.draw(camera);
        }
    }

    void setVisibility(bool visible) {
        mVisible = visible;
    }

    bool isVisible() const {
        return mVisible;
    }

    void setSpeed(float speed) {
        mSpeed = speed;
    }

    void incSpeedBy(float delta) {
        mSpeed += delta;
    }

    float getSpeed() const {
        return mSpeed;
    }

    void setCurrentFrontDir(glm::vec2 frontDir) {
        mCurrentFrontDir = glm::normalize(frontDir);
    }

    glm::vec2 getCurrentFrontDir() const {
        return mCurrentFrontDir;
    }

    // Orientate the entire object to point towards point p
    // will rotate Xform() accordingly
    void rotateObjPointTo(glm::vec2 targetPos, float rate) {
        // Step A: determine if reached the destination position p
        glm::vec2 dir = targetPos - mRenderComponent.getXform().getPosition();
        float len = glm::length(dir);
        const float MIN_VALUE = 0.01f;
        if (len < MIN_VALUE) {
            return; // we are there.
        }
        dir = glm::normalize(dir);

        // Step B: compute the angle to rotate
        glm::vec2 frontDir = getCurrentFrontDir();
        float cosTheta = glm::dot(dir, frontDir);

        if (cosTheta > 0.999999) { // almost exactly the same direction
            return;
        }

        // Step C: clamp the cosTheta to -1 to 1
        // in a perfect world, this would never happen! BUT ...
        if (cosTheta > 1.0f) {
            cosTheta = 1.0f;
        } else {
            if (cosTheta < -1.0f) {
                cosTheta = -1.0f;
            }
        }

        // Step D: compute whether to rotate clockwise, or counterclockwise
        glm::vec3 dir3d{dir.x, dir.y, 0.0f};
        glm::vec3 frontDir3d{frontDir.x, frontDir.y, 0.0f};
        glm::vec3 r3d = glm::cross(frontDir3d, dir3d);

        float rad = std::acos(cosTheta);  // radian to rotate
        if (r3d.z < 0.0f) {
            rad = -rad;
        }

        // Step E: rotate the facing direction with the angle and rate
        rad *= rate;  // actual angle need to rotate from Object's front
        // vec2.rotate(this.getCurrentFrontDir(), this.getCurrentFrontDir(), rad);
        auto m = glm::rotate(glm::mat4{1.0f}, rad, glm::vec3(0.0f, 0.0f, 1.0f));
        auto f = m * glm::vec4(getCurrentFrontDir(), 0.0f, 1.0f);
        setCurrentFrontDir(glm::vec2{f.x, f.y});
        mRenderComponent.getXform().incRotationByRad(rad);
    }

private:
    SpriteRenderable mRenderComponent;
    glm::vec2 mCurrentFrontDir{};
    float mSpeed;
    bool mVisible;
};


#endif //BYO2DGE_BRAIN_H
