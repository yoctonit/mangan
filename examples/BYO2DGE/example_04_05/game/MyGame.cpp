#include "MyGame.h"
#include "BlueLevel.h"

MyGame::MyGame(const Core &engine, Loop &loop)
        : mEngine{engine}, mLoop{loop} {
    std::cout << "Create MyGame object\n";
}

MyGame::~MyGame() {
    std::cout << "Destruct MyGame object\n";
}

void MyGame::init() {
    // Step A: Set up the camera
    mCamera = Camera(
            glm::vec2(20.0f, 60.0f),     // center of the WC
            20.0f,                              // width of WC
            {20, 40, 600, 300}  // viewport (orgX, orgY, width, height)
    );
    // set the background to gray
    mCamera.setBackgroundColor({0.8f, 0.8f, 0.8f, 1.0f});

    // Step B: Create the Renderable objects:
    mSupport = mEngine.createRenderable();
    mSupport.setColor({0.8f, 0.2f, 0.2f, 1.0f});
    mSupport.getXform().setPosition(20.0f, 60.0f);
    mSupport.getXform().setSize(5.0f, 5.0f);

    // Step C: Create the hero object in blue
    mHero = mEngine.createRenderable();
    mHero.setColor({0.0f, 0.0f, 1.0f, 1.0f});
    mHero.getXform().setPosition(20.0f, 60.0f);
    mHero.getXform().setSize(2.0f, 3.0f);
}

void MyGame::draw() {
    // Step A: clear the canvas
    Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f); // clear to light gray
    mCamera.clear();

    // Step B: Activate the drawing Camera
    mCamera.setViewAndCameraMatrix();

    // Step C: draw everything
    mSupport.draw(mCamera);
    mHero.draw(mCamera);
}

void MyGame::update(const Mn::Input &input) {
    // For this very simple game, let's move the white square and pulse the red

    Transform &xform = mHero.getXform();
    auto deltaX = 0.05f;

    // Support hero movements
    if (input.IsPressedKey(MN_KEY_RIGHT)) {
        xform.incXPosBy(deltaX);
        if (xform.getXPos() > 30.0f) { // this is the right-bound of the window
            xform.setPosition(12.0f, 60.0f);
        }
    }

    if (input.IsPressedKey(MN_KEY_LEFT)) {
        xform.incXPosBy(-deltaX);
        if (xform.getXPos() < 11.0f) { // this is the left-bound of the window
            next();
        }
    }

    if (input.IsPressedKey(MN_KEY_Q)) {
        stop();
    }
}

void MyGame::next() {
    mLoop.stop();
    auto nextLevel = std::make_shared<BlueLevel>(mEngine, mLoop);
    nextLevel->start();
}

void MyGame::start() {
    mLoop.start(this);
}

void MyGame::stop() {
    mLoop.stop();
}
