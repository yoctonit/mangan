#ifndef BYO2DGE_MY_GAME_H
#define BYO2DGE_MY_GAME_H

#include "../src/Core.h"
#include "../src/Font.h"
#include "../src/FontRenderable.h"
#include "../src/GameObjectSet.h"
#include "DyePack.h"
#include "Minion.h"
#include "Hero.h"


class MyGame : public Scene {
public:
    explicit MyGame(const Core &engine);

    ~MyGame() override;

    void init() override;

    // This is the draw function, make sure to set up proper drawing environment,
    // and more importantly, make sure to NOT change any state.
    void draw() override;

    // The update function, updates the application state.
    // Make sure to NOT draw anything from this function!
    void update(const Mn::Input &input) override;

private:
    const Core &mEngine;

    Camera mCamera{};

    Mn::Texture mMinionSpriteTexture;
    Hero mHero;
    GameObjectSet<Minion> mMinionSet{};
    DyePack mDyePack;

    FontRenderable mTextSysFont{};

    static std::string textFromNumber(float n);
};

#endif //BYO2DGE_MY_GAME_H
