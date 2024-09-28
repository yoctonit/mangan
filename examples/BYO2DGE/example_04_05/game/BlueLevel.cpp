#include "BlueLevel.h"
#include "MyGame.h"
#include "SceneFileParser.h"

BlueLevel::BlueLevel(const Core &engine, Loop &loop)
        : mEngine{engine}, mLoop(loop) {
    std::cout << "Create BlueLevel object\n";
};

BlueLevel::~BlueLevel() {
    std::cout << "Destruct BlueLevel object\n";
}

void BlueLevel::init() {
    SceneFileParser sceneParser("assets/blue_level.json");

    // Step A: Read in the camera
    mCamera = sceneParser.parseCamera();

    // Step B: Read all the squares
    mSquares = sceneParser.parseSquares(mEngine);
}

void BlueLevel::draw() {
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

void BlueLevel::update(const Mn::Input &input) {
    // For this very simple game, let's move the first square
    Transform &xform = mSquares[1].getXform();
    auto deltaX = 0.05f;

    // Move right and swap over
    if (input.IsPressedKey(MN_KEY_RIGHT)) {
        xform.incXPosBy(deltaX);
        if (xform.getXPos() > 30.0f) {// this is the right-bound of the window
            xform.setPosition(12.0f, 60.0f);
        }
    }

    if (input.IsPressedKey(MN_KEY_LEFT)) {
        xform.incXPosBy(-deltaX);
        if (xform.getXPos() < 11.0f) {// this is the left-bound of the window
            next();
        }
    }

    if (input.IsPressedKey(MN_KEY_Q)) {
        stop();
    }
}

void BlueLevel::next() {
    mLoop.stop();
    auto nextLevel = std::make_shared<MyGame>(mEngine, mLoop);
    nextLevel->start();
}

void BlueLevel::start() {
    mLoop.start(this);
}

void BlueLevel::stop() {
    mLoop.stop();
}
