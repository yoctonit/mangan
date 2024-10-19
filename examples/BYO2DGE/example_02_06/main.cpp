#include "window/Window.h"
#include "engine/Core.h"

//class MyGame {
//    MyGame() {
//        // Step A: Initialize the game engine
//        engine.init(htmlCanvasID);
//
//        // Step B: Clear the canvas
//        engine.clearCanvas(0.0f, 0.8f, 0.0f, 1.0f);
//
//        // Step C: Draw the square in red
//        engine.drawSquare(1.0f, 0.0f, 0.0f, 1.0f);
//    }
//};

int main() {

    Mn::Window wnd(640, 480, "Example 2.6");
    auto &input = Mn::Window::GetInput();

    // Step A: Initialize the game engine
    Core engine;
    engine.init();

    bool runScene = true;
    while (wnd.IsOpen() && runScene) {
        Mn::Window::PollEvents();

        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        // render scene
        // ------------
        // Step B: Clear the canvas
        Core::clearCanvas(0.0f, 0.8f, 0.0f, 1.0f);

        // Step C: Draw the square in red
        engine.drawSquare(1.0f, 0.0f, 0.0f, 1.0f);
        // ------------

        wnd.Display();
    }

    return 0;
}
