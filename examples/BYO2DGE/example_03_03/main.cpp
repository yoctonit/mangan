#include "window/Window.h"
#include "src/Core.h"
#include "src/Renderable.h"


int main() {

    Mn::Window wnd(640, 480, "Example 2.6");
    auto &input = Mn::Window::GetInput();

    // Step A: Initialize the game engine
    Core engine;
    engine.init();

    // Step B: Create the Renderable objects:
    Renderable mWhiteSq = engine.createRenderable();
    mWhiteSq.setColor({1.0f, 1.0f, 1.0f, 1.0f});
    Renderable mRedSq = engine.createRenderable();
    mRedSq.setColor({1.0f, 0.0f, 0.0f, 1.0f});

    bool runScene = true;
    while (wnd.IsOpen() && runScene) {
        Mn::Window::PollEvents();

        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        // render scene
        // ------------
        // Step C: Draw!
        Core::clearCanvas(0.0f, 0.8f, 0.0f, 1.0f);  // Clear the canvas

        // instead of simply drawing the squares, let's apply simple transforms
        // Step D: sets the blue Renderable object's transform
        mWhiteSq.getXform().setPosition(-0.25f, 0.25f);
        mWhiteSq.getXform().setRotationInRad(0.2f); // In Radians
        mWhiteSq.getXform().setSize(1.2f, 1.2f);
        // Step E: draw the white square with the computed transform
        mWhiteSq.draw();

        // Step F: sets the red square transform
        mRedSq.getXform().setXPos(0.25f);  // to show alternative to setPosition
        mRedSq.getXform().setYPos(-0.25f); // it is possible to setX/Y separately
        mRedSq.getXform().setRotationInDegree(45.0f);  // this is in Degree
        mRedSq.getXform().setWidth(0.4f);  // to show alternative to setSize
        mRedSq.getXform().setHeight(0.4f);  // that it is possible to width/height separately
        // Step G: draw the red square (transform in the object)
        mRedSq.draw();
        // ------------

        wnd.Display();
    }

    return 0;
}
