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
        // Step C: Clear the entire canvas first
        Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);  // Clear the canvas

        // Step D: Setting up Viewport
        // Step D1: Set up the viewport: area on canvas to be drawn
        glViewport(
                20,        // x position of bottom-left corner of the area to be drawn
                40,        // y position of bottom-left corner of the area to be drawn
                600,    // width of the area to be drawn
                300    // height of the area to be drawn
        );

        // Step D2: set up the corresponding the scissor area to limit clear area
        glScissor(
                20,        // x position of bottom-left corner of the area to be drawn
                40,        // y position of bottom-left corner of the area to be drawn
                600,    // width of the area to be drawn
                300    // height of the area to be drawn
        );

        // Step D3: enable the scissor area, clear, and then disable the scissor area
        glEnable(GL_SCISSOR_TEST);
        Core::clearCanvas(0.8f, 0.8f, 0.8f, 1.0f);  // clear the scissor area
        glDisable(GL_SCISSOR_TEST);

        // Step E: Set up camera transform matrix
        // assume camera position and dimension
        glm::vec2 cameraCenter(20.0f, 60.0f);
        glm::vec2 wcSize(20.0f, 10.0f);
        glm::mat4 cameraMatrix{1.0f};
        // Step E1: following the translation, scale to: (-1, -1) to (1, 1): a 2x2 square at origin
        // mat4.scale(cameraMatrix, mat4.create(), vec3.fromValues(2.0 / wcSize[0], 2.0 / wcSize[1], 1.0));
        cameraMatrix = glm::scale(cameraMatrix, glm::vec3(2.0f / wcSize[0], 2.0f / wcSize[1], 1.0f));

        // Step E2: first operation to perform is to translate camera center to the origin
        // mat4.translate(cameraMatrix, cameraMatrix, vec3.fromValues(-cameraCenter[0], -cameraCenter[1], 0));
        cameraMatrix = glm::translate(cameraMatrix, glm::vec3(-cameraCenter[0], -cameraCenter[1], 0.0f));

        // Step F: Draw the blue square
        // Center Blue, slightly rotated square
        mBlueSq.getXform().setPosition(20.0f, 60.0f);
        mBlueSq.getXform().setRotationInRad(0.2f); // In Radians
        mBlueSq.getXform().setSize(5.0f, 5.0f);
        mBlueSq.draw(cameraMatrix);

        // Step G: Draw the center and the corner squares
        // center red square
        mRedSq.getXform().setPosition(20.0f, 60.0f);
        mRedSq.getXform().setSize(2.0f, 2.0f);
        mRedSq.draw(cameraMatrix);

        // top left
        mTLSq.getXform().setPosition(10.0f, 65.0f);
        mTLSq.draw(cameraMatrix);

        // top right
        mTRSq.getXform().setPosition(30.0f, 65.0f);
        mTRSq.draw(cameraMatrix);

        // bottom right
        mBRSq.getXform().setPosition(30.0f, 55.0f);
        mBRSq.draw(cameraMatrix);

        // bottom left
        mBLSq.getXform().setPosition(10.0f, 55.0f);
        mBLSq.draw(cameraMatrix);
        // ------------

        wnd.Display();
    }

    return 0;
}
