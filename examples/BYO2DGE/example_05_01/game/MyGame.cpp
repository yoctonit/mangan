#include "MyGame.h"
#include "BlueLevel.h"

MyGame::MyGame(const Core &engine, LevelManager &levelManager)
        : Level{levelManager}, mEngine{engine} {
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

    // Step B: Create the game objects:
    mPortal = mEngine.createTextureRenderable(Mn::Texture("assets/minion_portal.png"));
    mPortal.setColor({1.0f, 0.0f, 0.0f, 0.2f});
    mPortal.getXform().setPosition(25.0f, 60.0f);
    mPortal.getXform().setSize(3.0f, 3.0f);

    mCollector = mEngine.createTextureRenderable(Mn::Texture("assets/minion_collector.png"));
    mCollector.setColor({0.0f, 0.0f, 0.0f, 0.0f}); // no tinting
    mCollector.getXform().setPosition(15.0f, 60.0f);
    mCollector.getXform().setSize(3.0f, 3.0f);

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
    mPortal.draw(mCamera);
    mHero.draw(mCamera);
    mCollector.draw(mCamera);
}

void MyGame::update(const Mn::Input &input) {
    if (input.IsClickedKey(MN_KEY_ESCAPE)) {
        mLevelRunning = false;
    }

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
            return;
        }
    }

    // continuously change texture tinting
    auto c = mPortal.getColor();
    auto ca = c[3] + deltaX;
    if (ca > 1.0f) {
        ca = 0.0f;
    }
    c[3] = ca;
    mPortal.setColor(c);
}

void MyGame::start() {
    mLevelRunning = true;
}

void MyGame::stop() {
    mLevelRunning = false;
}

void MyGame::next() {
    auto nextLevel = std::make_shared<BlueLevel>(mEngine, mLevelManager);
    mLevelManager.setLevel(nextLevel);
}

