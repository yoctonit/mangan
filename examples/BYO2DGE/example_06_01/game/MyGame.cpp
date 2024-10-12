#include <sstream>
#include "MyGame.h"

MyGame::MyGame(const Core &engine)
        : mEngine{engine},
          mMinionSpriteTexture("assets/minion_sprite.png"),
          mHero(engine, mMinionSpriteTexture),
          mDyePack(engine, mMinionSpriteTexture) {
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

    for (int i = 0; i < 5; i++) {
        auto randomY = static_cast<float>(rand() % 65);
        Minion aMinion(mEngine, mMinionSpriteTexture, randomY);
//        mMinionSet.addToSet(textFromNumber(i), Minion{mEngine, mMinionSpriteTexture, randomY});
        mMinionSet.addToSet(textFromNumber(static_cast<float>(i)), aMinion);
    }

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
    mMinionSet.draw(mCamera);
    mDyePack.draw(mCamera);

    // drawing the text output
    mTextSysFont.draw(mCamera);
}

void MyGame::update(const Mn::Input &input) {
    if (input.IsClickedKey(MN_KEY_ESCAPE)) {
        mSceneRunning = false;
    }

    mHero.update(input);
    mMinionSet.update(input);
    mDyePack.update(input);
}

std::string MyGame::textFromNumber(float n) {
    std::stringstream s{};
    s << n;
    return s.str();
}
