//
// Created by Ivan on 22-Feb-23.
//

#ifndef OPENGL_EXAMPLES_GAME_OBJECT_H
#define OPENGL_EXAMPLES_GAME_OBJECT_H

#include <memory>
#include <glm/gtx/rotate_vector.hpp>
#include "../renderable/Renderable.h"
#include "../BoundingBox.h"

class GameObject {
public:
    GameObject() : mVisible(true), mCurrentFrontDir(glm::vec2(0.0f, 1.0f)), mSpeed(0.0f) {};

    explicit GameObject(const std::shared_ptr<Renderable> &renderable) {
        mRenderComponent = renderable;
        mVisible = true;
        mCurrentFrontDir = glm::vec2(0.0f, 1.0f);
        mSpeed = 0.0f;
    }

    std::shared_ptr<Transform> getXform() { return mRenderComponent->getXform(); }

    BoundingBox getBBox() {
        auto xform = getXform();
        BoundingBox b(xform->getPosition(), xform->getWidth(), xform->getHeight());
        return b;
    }

    void setVisibility(bool f) { mVisible = f; }

    [[nodiscard]] bool isVisible() const { return mVisible; }

    void setSpeed(float s) { mSpeed = s; }

    [[nodiscard]] float getSpeed() const { return mSpeed; }

    void incSpeedBy(float delta) { mSpeed += delta; }

    void setCurrentFrontDir(glm::vec2 f) {
        // vec2.normalize(mCurrentFrontDir, f);
        mCurrentFrontDir = glm::normalize(f);
    }

    glm::vec2 getCurrentFrontDir() { return mCurrentFrontDir; }

    std::shared_ptr<Renderable> getRenderable() { return mRenderComponent; }

    // Orientate the entire object to point towards point p
    // will rotate Xform() accordingly
    void rotateObjPointTo(glm::vec2 p, float rate) {
        const float MIN_VALUE = 0.001;
        // Step A: determine if reached the destination position p
        glm::vec2 direction;
        // vec2.sub(direction, p, getXform().getPosition());
        direction = p - getXform()->getPosition();
        float directionLength = glm::length(direction); // vec2.length(direction);
        if (directionLength < MIN_VALUE) {
            return; // we are there.
        }
        // vec2.scale(direction, direction, 1 / directionLength);
        direction = direction / directionLength; // or direction = glm::normalize(direction)

        // Step B: compute the angle to rotate
        glm::vec2 frontDirection = getCurrentFrontDir();
        float cosTheta = glm::dot(direction, frontDirection);

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
        glm::vec3 dir3d(direction.x, direction.y, 0.0f);
        glm::vec3 f3d(frontDirection.x, frontDirection.y, 0.0f);
        glm::vec3 r3d;
        // vec3.cross(r3d, f3d, dir3d);
        r3d = glm::cross(f3d, dir3d);

        float rad = std::acos(cosTheta); // Math.acos(cosTheta);  // radian to rotate
        if (r3d.z < 0.0f) {
            rad = -rad;
        }

        // Step E: rotate the facing direction with the angle and rate
        rad *= rate;  // actual angle need to rotate from Object's front
        // vec2.rotate(getCurrentFrontDir(), getCurrentFrontDir(), rad);
        mCurrentFrontDir = RotateVec2(getCurrentFrontDir(), rad);
        getXform()->incRotationByRad(rad);
    }

    static glm::vec2 RotateVec2(glm::vec2 d, float rad) {
//        glm::mat4 rotationMatrix;
//        glm::rotate(rotationMatrix, rad, glm::vec3(0.f, 0.f, 1.0f));
//        glm::vec4 temp = rotationMatrix * glm::vec4(d.x, d.y, 0.0f, 1.0f);
//        return {temp.x, temp.y};

            glm::vec3 t(d.x, d.y, 0.0f);
            t = glm::rotateZ(t, rad);
//            std::cout << "T " << t.x << ", " << t.y << ", " << t.z << std::endl;
            return {t.x, t.y};

//        glm::vec2 r;
//        // perform rotation
//        r.x = d.x*std::cos(rad) - d.y*std::sin(rad);
//        r.y = d.x*std::sin(rad) + d.y*std::cos(rad);
////        out[0] = r[0];
////        out[1] = r[1];
//        return r;
    }

    virtual void update(const Mn::Input &input) {
        // simple default behavior
        glm::vec2 pos = getXform()->getPosition();
        // vec2.scaleAndAdd(pos, pos, getCurrentFrontDir(), getSpeed());
        pos += mCurrentFrontDir * getSpeed();
        getXform()->setPosition(pos.x, pos.y);
    }

    void draw(const Camera &aCamera) {
        if (isVisible()) {
            mRenderComponent->draw(aCamera);
        }
    }

    // Support for per-pixel collision
    bool pixelTouches(const std::shared_ptr<GameObject>& otherObj, glm::vec2& wcTouchPos) {
        // only continue if both objects have getColorArray defined
        // if defined, should have other texture intersection support!
        bool pixelTouch = false;
        auto myRen = getRenderable();
        auto otherRen = otherObj->getRenderable();

        auto otherBbox = otherObj->getBBox();
        if (otherBbox.intersectsBound(getBBox())) {
            myRen->setColorArray();
            otherRen->setColorArray();
            pixelTouch = myRen->pixelTouches(otherRen, wcTouchPos);
        }
        return pixelTouch;

//        if ((typeof myRen.pixelTouches === "function") && (typeof otherRen.pixelTouches === "function")) {
//            let otherBbox = otherObj.getBBox();
//            if (otherBbox.intersectsBound(this.getBBox())) {
//                myRen.setColorArray();
//                otherRen.setColorArray();
//                pixelTouch = myRen.pixelTouches(otherRen, wcTouchPos);
//            }
//            return pixelTouch;
//        }
    }

protected:
    std::shared_ptr<Renderable> mRenderComponent;
    bool mVisible{};
    glm::vec2 mCurrentFrontDir{};
    float mSpeed{};
};

#endif //OPENGL_EXAMPLES_GAME_OBJECT_H
