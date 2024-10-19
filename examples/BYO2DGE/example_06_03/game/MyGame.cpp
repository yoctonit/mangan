#include <sstream>
#include "MyGame.h"

MyGame::MyGame(const Core &engine)
        : mEngine{engine},
          mMinionSpriteTexture("assets/minion_sprite.png"),
          mHero(engine, mMinionSpriteTexture),
          mBrain(engine, mMinionSpriteTexture) {
    std::cout << "Create MyGame object\n";
}

MyGame::~MyGame() {
    std::cout << "Destruct MyGame object\n";
}

void MyGame::init() {
    // Step A: Set up the camera
    mCamera = Camera(
            glm::vec2(50.0f, 37.5f),     // center of the WC
            100.0f,                              // width of WC
            {0, 0, 640, 480}  // viewport (orgX, orgY, width, height)
    );
    // set the background to gray
    mCamera.setBackgroundColor({0.8f, 0.8f, 0.8f, 1.0f});

    mTextSysFont = mEngine.createFontRenderable("system_default_font", "Status Message");
    mTextSysFont.setColor({0.0f, 0.0f, 0.0f, 1.0f});
    mTextSysFont.getXform().setPosition(1.0f, 2.0f);
    mTextSysFont.setTextHeight(3.0f);
}

void MyGame::draw() {
    // Step A: clear the canvas
    Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f); // clear to light gray
    mCamera.clear();

    // Step B: Activate the drawing Camera
    mCamera.setViewAndCameraMatrix();

    // Step C: draw everything
    mHero.draw(mCamera);
    mBrain.draw(mCamera);

    mTextSysFont.draw(mCamera);
}

void MyGame::update(const Mn::Input &input) {
    if (input.IsClickedKey(MN_KEY_ESCAPE)) {
        mSceneRunning = false;
    }

    std::string msg = "Brain [H:keys J:imm K:gradual]: ";
    float rate = 1.0f;

    mHero.update(input);

    // get the bounding box for collision
    auto hBbox = mHero.getBBox();
    auto bBbox = mBrain.getBBox();
    switch (mMode) {
        case 'H':
            mBrain.update(input);   // player steers with arrow keys
            break;
        case 'K':
            rate = 0.02f;   // gradual rate
            // After "K" is typed (in gradual mode), the following should also be executed.
        case 'J':
            if (!hBbox.intersectsBound(bBbox)) {  // stop the brain when it touches hero bound
                mBrain.rotateObjPointTo(mHero.getXform().getPosition(), rate);
                // engine.GameObject.prototype.update.call(this.mBrain);  // the default GameObject: only move forward
                mBrain.update();
            }
            break;
    }

    // Check for hero going outside 80% of the WC Window bound
    auto status = mCamera.collideWCBound(mHero.getXform(), 0.8);

    if (input.IsClickedKey(MN_KEY_H)) {
        mMode = 'H';
    }
    if (input.IsClickedKey(MN_KEY_J)) {
        mMode = 'J';
    }
    if (input.IsClickedKey(MN_KEY_K)) {
        mMode = 'K';
    }

    std::stringstream ss;
    ss << status;
    mTextSysFont.setText(msg + mMode + " [Hero bound=" + ss.str() + "]");
}
