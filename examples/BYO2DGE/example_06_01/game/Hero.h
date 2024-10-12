#ifndef BYO2DGE_HERO_H
#define BYO2DGE_HERO_H

#include "../src/Core.h"
#include "../src/GameObject.h"
#include "../src/SpriteRenderable.h"

class Hero : public GameObject<SpriteRenderable> {
public:
    Hero(const Core &engine, const Mn::Texture& texture)
            : GameObject<SpriteRenderable>(engine.createSpriteRenderable(texture)) {

        mRenderComponent.setColor({1.0f, 1.0f, 1.0f, 0.0f});
        mRenderComponent.getXform().setPosition(35.0f, 50.0f);
        mRenderComponent.getXform().setSize(9.0f, 12.0f);
        mRenderComponent.setElementPixelPositions(0.0f, 120.0f, 0.0f, 180.0f);
    }

    void update(const Mn::Input &input) override {
        Transform &xform = getXform();

        if (input.IsPressedKey(MN_KEY_W)) {
            xform.incYPosBy(kDelta);
        }
        if (input.IsPressedKey(MN_KEY_S)) {
            xform.incYPosBy(-kDelta);
        }
        if (input.IsPressedKey(MN_KEY_A)) {
            xform.incXPosBy(-kDelta);
        }
        if (input.IsPressedKey(MN_KEY_D)) {
            xform.incXPosBy(kDelta);
        }
    }

private:
    const float kDelta{0.3f};
};

#endif //BYO2DGE_HERO_H
