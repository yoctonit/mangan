#ifndef BYO2DGE_MINION_H
#define BYO2DGE_MINION_H

#include <cstdlib>
#include "../src/Core.h"
//#include "../src/GameObject.h"
#include "../src/SpriteAnimateRenderable.h"

class Minion {
public:
    Minion(const Core &engine, const Mn::Texture &texture, float atY) {
        mRenderComponent = engine.createSpriteAnimateRenderable(texture);
        mRenderComponent.setColor({1.0f, 1.0f, 1.0f, 0.0f});
        mRenderComponent.getXform().setPosition(static_cast<float>(rand() % 100), atY);
        mRenderComponent.getXform().setSize(12.0f, 9.6f);
        mRenderComponent.setSpriteSequence(
                512, 0,      // first element pixel position: top-left 512 is top of image, 0 is left of image
                204, 164,   // width x height in pixels
                5,          // number of elements in this sequence
                0           // horizontal padding in between
        );
        mRenderComponent.setAnimationType(eAnimationType::eSwing);
        mRenderComponent.setAnimationSpeed(15); // show each element for mAnimSpeed updates
    }

    void update(const Mn::Input &input) {
        mRenderComponent.updateAnimation();

        // move towards the left and wraps
        Transform &xform = mRenderComponent.getXform();
        const float kDelta{0.2f};
        xform.incXPosBy(-kDelta);

        // if fly off to the left, re-appear at the right
        if (xform.getXPos() < 0.0f) {
            xform.setXPos(100.0f);
            xform.setYPos(static_cast<float>(rand() % 65));
        }
    }

    void draw(const Camera &camera) {
        mRenderComponent.draw(camera);
    }

private:
    SpriteAnimateRenderable mRenderComponent;
};

#endif //BYO2DGE_MINION_H
