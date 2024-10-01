#ifndef BYO2DGE_BLUE_LEVEL_H
#define BYO2DGE_BLUE_LEVEL_H

#include "../src/Core.h"
#include "../src/Renderable.h"


class BlueLevel : public Level {
public:
    explicit BlueLevel(const Core &engine, LevelManager &levelManager);

    ~BlueLevel() override;

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
    std::vector<Renderable> mSquares{};
    std::vector<TextureRenderable> mTexturedSquares{};
};

#endif //BYO2DGE_BLUE_LEVEL_H
