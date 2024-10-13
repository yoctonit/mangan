#ifndef BYO2DGE_MY_GAME_H
#define BYO2DGE_MY_GAME_H

#include "../src/Core.h"
#include "../src/Font.h"
#include "../src/FontRenderable.h"
#include "Hero.h"
#include "Brain.h"


class MyGame : public Scene {
public:
    explicit MyGame(const Core &engine);

    ~MyGame() override;

    void init() override;

    void draw() override;

    void update(const Mn::Input &input) override;

private:
    const Core &mEngine;

    Camera mCamera{};

    Mn::Texture mMinionSpriteTexture;
    Hero mHero;
    Brain mBrain;

    FontRenderable mTextSysFont{};
    // mode of running:
    //   H: Player drive brain
    //   J: Dye drive brain, immediate orientation change
    //   K: Dye drive brain, gradual orientation change
    char mMode{'H'};
};

#endif //BYO2DGE_MY_GAME_H
