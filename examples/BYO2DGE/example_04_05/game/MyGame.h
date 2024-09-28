#ifndef BYO2DGE_MY_GAME_H
#define BYO2DGE_MY_GAME_H

#include "engine/Window.h"
#include "../src/Core.h"
#include "../src/Renderable.h"
#include "../src/Loop.h"

class MyGame : public Scene {
public:
    explicit MyGame(const Core &engine, Loop &loop);

    ~MyGame();

    void init() override;

    // This is the draw function, make sure to set up proper drawing environment,
    // and more importantly, make sure to NOT change any state.
    void draw() override;

    // The update function, updates the application state.
    // Make sure to NOT draw anything from this function!
    void update(const Mn::Input &input) override;

    void next() override;

    void start() override;

    void stop() override;

private:
    const Core &mEngine;
    Loop &mLoop;

    Camera mCamera{};
    Renderable mHero{};
    Renderable mSupport{};
};

#endif //BYO2DGE_MY_GAME_H
