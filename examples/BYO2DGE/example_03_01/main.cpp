#include "engine/Window.h"
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

        // Step C1: Draw Renderable objects with the white shader
        mWhiteSq.draw();

        // Step C2: Draw Renderable objects with the red shader
        mRedSq.draw();
        // ------------

        wnd.Display();
    }

    return 0;
}
