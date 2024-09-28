#include "MyGame.h"
#include "SceneFileParser.h"

MyGame::MyGame(const Core &engine) : mEngine{engine} {};

void MyGame::init() {
    SceneFileParser sceneParser("assets/scene.json");

    // Step A: Read in the camera
    mCamera = sceneParser.parseCamera();

    // Step B: Read all the squares
    mSquares = sceneParser.parseSquares(mEngine);
}

void MyGame::draw() {
    // Step A: clear the canvas
    Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f); // clear to light gray
    mCamera.clear();

    // Step  B: Activate the drawing Camera
    mCamera.setViewAndCameraMatrix();

    // Step  C: draw all the squares
    for (auto &square: mSquares) {
        square.draw(mCamera);
    }
}

void MyGame::update(const Mn::Input &input) {
    // For this very simple game, let's move the white square and pulse the red

    Transform &whiteXform = mSquares[0].getXform();
    auto deltaX = 0.05f;

    // Step A: test for white square movement
    if (input.IsPressedKey(MN_KEY_RIGHT)) {
        if (whiteXform.getXPos() > 30.0f) {// this is the right-bound of the window
            whiteXform.setPosition(10.0f, 60.0f);
        }
        whiteXform.incXPosBy(deltaX);
    }

    // Step B: test for white square rotation
    if (input.IsPressedKey(MN_KEY_UP)) {
        whiteXform.incRotationByDegree(1);
//            std::cout << whiteXform.getRotationInDegree() << " -> "
//                << whiteXform.getRotationInRad() << "\n";
    }

    Transform &redXform = mSquares[1].getXform();
    // Step C: test for pulsing the red square
    if (input.IsPressedKey(MN_KEY_DOWN)) {
        if (redXform.getWidth() > 5.0f) {
            redXform.setSize(2.0f, 2.0f);
        }
        redXform.incSizeBy(0.05f);
    }
}
