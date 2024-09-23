#include "engine/Window.h"
#include "src/Core.h"
#include "src/Renderable.h"


int main() {

    Mn::Window wnd(640, 480, "Example 2.6");
    auto &input = Mn::Window::GetInput();

    // Step A: Initialize the game engine
    Core engine;
    engine.init();

    // Step B: Set up the camera
    Camera mCamera(
            glm::vec2(20.0f, 60.0f),     // center of the WC
            20.0f,                              // width of WC
            {20, 40, 600, 300}  // viewport (orgX, orgY, width, height)
    );

    // Step C: Create the Renderable objects:
    Renderable mBlueSq = engine.createRenderable();
    mBlueSq.setColor({0.25f, 0.25f, 0.95f, 1.0f});
    Renderable mRedSq = engine.createRenderable();
    mRedSq.setColor({1.0f, 0.25f, 0.25f, 1.0f});
    Renderable mTLSq = engine.createRenderable();
    mTLSq.setColor({0.9f, 0.1f, 0.1f, 1.0f});
    Renderable mTRSq = engine.createRenderable();
    mTRSq.setColor({0.1f, 0.9f, 0.1f, 1.0f});
    Renderable mBRSq = engine.createRenderable();
    mBRSq.setColor({0.1f, 0.1f, 0.9f, 1.0f});
    Renderable mBLSq = engine.createRenderable();
    mBLSq.setColor({0.1f, 0.1f, 0.1f, 1.0f});

    bool runScene = true;
    while (wnd.IsOpen() && runScene) {
        Mn::Window::PollEvents();

        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        // render scene
        // ------------
        // Step D: Clear the canvas
        Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);
        mCamera.clear();

        // Step E: Starts the drawing by activating the camera
        mCamera.setViewAndCameraMatrix();

        // Step F: Draw the blue square
        // Center Blue, slightly rotated square
        mBlueSq.getXform().setPosition(20.0f, 60.0f);
        mBlueSq.getXform().setRotationInRad(0.2f); // In Radians
        mBlueSq.getXform().setSize(5.0f, 5.0f);
        mBlueSq.draw(mCamera);

        // Step G: Draw the center and the corner squares
        // center red square
        mRedSq.getXform().setPosition(20.0f, 60.0f);
        mRedSq.getXform().setSize(2.0f, 2.0f);
        mRedSq.draw(mCamera);

        // top left
        mTLSq.getXform().setPosition(10.0f, 65.0f);
        mTLSq.draw(mCamera);

        // top right
        mTRSq.getXform().setPosition(30.0f, 65.0f);
        mTRSq.draw(mCamera);

        // bottom right
        mBRSq.getXform().setPosition(30.0f, 55.0f);
        mBRSq.draw(mCamera);

        // bottom left
        mBLSq.getXform().setPosition(10.0f, 55.0f);
        mBLSq.draw(mCamera);
        // ------------

        wnd.Display();
    }

    return 0;
}
