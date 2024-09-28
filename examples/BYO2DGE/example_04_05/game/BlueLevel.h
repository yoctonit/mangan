#ifndef BYO2DGE_BLUE_LEVEL_H
#define BYO2DGE_BLUE_LEVEL_H

#include "engine/Window.h"
#include "../src/Core.h"
#include "../src/Renderable.h"
#include "../src/Loop.h"

class BlueLevel : public Scene {
public:
    explicit BlueLevel(const Core &engine, Loop &loop);

    ~BlueLevel();

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
    std::vector<Renderable> mSquares{};
};

#endif //BYO2DGE_BLUE_LEVEL_H
