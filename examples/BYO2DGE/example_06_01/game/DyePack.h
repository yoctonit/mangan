#ifndef BYO2DGE_DYE_PACK_H
#define BYO2DGE_DYE_PACK_H

#include "../src/Core.h"
#include "../src/GameObject.h"
#include "../src/SpriteRenderable.h"

class DyePack : public GameObject<SpriteRenderable> {
public:
    DyePack(const Core &engine, Mn::Texture texture)
            : GameObject<SpriteRenderable>(engine.createSpriteRenderable(texture)) {
        const float kRefWidth = 80.0f;
        const float kRefHeight = 130.0f;

        mRenderComponent.setColor({1.0f, 1.0f, 1.0f, 0.1f});
        mRenderComponent.getXform().setPosition(50.0f, 33.0f);
        mRenderComponent.getXform().setSize(kRefWidth / 50.0f, kRefHeight / 50.0f);
        mRenderComponent.setElementPixelPositions(510.0f, 595.0f, 23.0f, 153.0f);
    }
};

#endif //BYO2DGE_DYE_PACK_H
