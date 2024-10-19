#include "window/Window.h"
#include "src/Core.h"
#include "src/Renderable.h"
#include <glm/gtc/matrix_transform.hpp>


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

        // create a new identity transform operator
        auto trsMatrix = glm::mat4(1.0f);

        // Step D: compute the white square transform
        trsMatrix = glm::translate(trsMatrix, glm::vec3(-0.25f, 0.25f, 0.0f));
        trsMatrix = glm::rotate(trsMatrix, 0.2f, glm::vec3(0.0f, 0.0f, 1.0f)); // rotation is in radian
        trsMatrix = glm::scale(trsMatrix, glm::vec3(1.2f, 1.2f, 1.0f));

        // Step E: draw the white square with the computed transform
        mWhiteSq.draw(trsMatrix);

        // Step F: compute the red square transform
        trsMatrix = glm::mat4(1.0f); // restart
        trsMatrix = glm::translate(trsMatrix, glm::vec3(0.25f, -0.25f, 0.0f));
        trsMatrix = glm::rotate(trsMatrix, -0.785f,
                                glm::vec3(0.0f, 0.0f, 1.0f)); // rotation is in radian (about -45-degree)
        trsMatrix = glm::scale(trsMatrix, glm::vec3(0.4f, 0.4f, 1.0f));

        // Step G: draw the red square with the computed transform
        mRedSq.draw(trsMatrix);
        // ------------

        wnd.Display();
    }

    return 0;
}
