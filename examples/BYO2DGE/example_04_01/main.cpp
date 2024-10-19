#include "window/Window.h"
#include "src/Core.h"
#include "src/Renderable.h"
#include "src/Loop.h"

class MyGame : public Scene {
public:
    explicit MyGame(const Core &engine) : mEngine{engine} {};

    void init() override {
        // Step A: Set up the camera
        mCamera = Camera(
                glm::vec2(20.0f, 60.0f),     // center of the WC
                20.0f,                              // width of WC
                {20, 40, 600, 300}  // viewport (orgX, orgY, width, height)
        );
        // set the background to gray
        mCamera.setBackgroundColor({0.8f, 0.8f, 0.8f, 1.0f});

        // Step B: Create the Renderable objects:
        mWhiteSq = mEngine.createRenderable();
        mWhiteSq.setColor({1.0f, 1.0f, 1.0f, 1.0f});
        mRedSq = mEngine.createRenderable();
        mRedSq.setColor({1.0f, 0.0f, 0.0f, 1.0f});

        // Step  C: Initialize the white Renderable object: centered, 5x5, rotated
        mWhiteSq.getXform().setPosition(20.0f, 60.0f);
        mWhiteSq.getXform().setRotationInRad(0.2f); // In Radians
        mWhiteSq.getXform().setSize(5.0f, 5.0f);

        // Step  D: Initialize the red Renderable object: centered 2x2
        mRedSq.getXform().setPosition(20.0f, 60.0f);
        mRedSq.getXform().setSize(2.0f, 2.0f);
    }

    // This is the draw function, make sure to set up proper drawing environment,
    // and more importantly, make sure to NOT change any state.
    void draw() override {
        // Step A: clear the canvas
        Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f); // clear to light gray
        mCamera.clear();

        // Step  B: Activate the drawing Camera
        mCamera.setViewAndCameraMatrix();

        // Step  C: Activate the white shader to draw
        mWhiteSq.draw(mCamera);

        // Step  D: Activate the red shader to draw
        mRedSq.draw(mCamera);
    }


    // The update function, updates the application state.
    // Make sure to NOT draw anything from this function!
    void update() override {
        // For this very simple game, let's move the white square and pulse the red
        Transform &whiteXform = mWhiteSq.getXform();
        auto deltaX = 0.05f;

        // Step A: Rotate the white square
        if (whiteXform.getXPos() > 30.0f) {// this is the right-bound of the window
            whiteXform.setPosition(10.0f, 60.0f);
        }
        whiteXform.incXPosBy(deltaX);
        whiteXform.incRotationByDegree(1);

        // Step B: pulse the red square
        Transform &redXform = mRedSq.getXform();
        if (redXform.getWidth() > 5.0f) {
            redXform.setSize(2.0f, 2.0f);
        }
        redXform.incSizeBy(0.05f);
    }

private:
    const Core &mEngine;
    Renderable mWhiteSq{};
    Renderable mRedSq{};
    Camera mCamera{};
};

int main() {

    Mn::Window wnd(640, 480, "Example 2.6");
    auto &input = Mn::Window::GetInput();

    // Initialize the game engine
    Core engine;
    engine.init();

    MyGame myGame(engine);

    Loop loop;
    loop.start(&myGame, wnd);

    return 0;
}
//int main() {
//
//    Mn::Window wnd(640, 480, "Example 2.6");
//    auto &input = Mn::Window::GetInput();
//
//    // Initialize the game engine
//    Core engine;
//    engine.init();
//
//    MyGame myGame(engine);
//    myGame.init();
//
//    bool runScene = true;
//    while (wnd.IsOpen() && runScene) {
//        Mn::Window::PollEvents();
//
//        input.Update();
//        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
//            runScene = false;
//        }
//
//        // render scene
//        // ------------
//        myGame.update();
//        myGame.draw();
//        // ------------
//
//        wnd.Display();
//    }
//
//    return 0;
//}
