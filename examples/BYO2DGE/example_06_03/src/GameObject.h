#ifndef BYO2DGE_GAME_OBJECT_H
#define BYO2DGE_GAME_OBJECT_H

#include "window/Input.h"
#include "Camera.h"
#include "Transform.h"
#include "BoundingBox.h"

template<typename T>
class GameObject {
public:
    explicit GameObject(T renderable) : mRenderComponent{renderable} {}

    [[nodiscard]] Transform &getXform() {
        return mRenderComponent.getXform();
    }

    BoundingBox getBBox() {
        const Transform &xform = getXform();
        return {xform.getPosition(), xform.getWidth(), xform.getHeight()};
    }

    [[nodiscard]] T &getRenderable() {
        return mRenderComponent;
    }

    virtual void update(const Mn::Input &input) {}

    virtual void draw(const Camera &camera) {
        mRenderComponent.draw(camera);
    }

protected:
    T mRenderComponent;
};

#endif //BYO2DGE_GAME_OBJECT_H
