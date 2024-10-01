#ifndef BYO2DGE_MY_GAME_H
#define BYO2DGE_MY_GAME_H

#include "../src/Core.h"
#include "../src/Renderable.h"


class MyGame : public Level {
public:
    MyGame(const Core &engine, LevelManager &levelManager);

    ~MyGame() override;

    void init() override;

    // This is the draw function, make sure to set up proper drawing environment,
    // and more importantly, make sure to NOT change any state.
    void draw() override;

    // The update function, updates the application state.
    // Make sure to NOT draw anything from this function!
    void update(const Mn::Input &input) override;

    void start() override;

    void stop() override;

    void next() override;

private:
    const Core &mEngine;

    Camera mCamera{};
    Renderable mHero{};
    Renderable mSupport{};
};

#endif //BYO2DGE_MY_GAME_H
