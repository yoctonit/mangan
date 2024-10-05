#include <sstream>
#include "MyGame.h"

MyGame::MyGame(const Core &engine)
        : mEngine{engine} {
    std::cout << "Create MyGame object\n";
}

MyGame::~MyGame() {
    std::cout << "Destruct MyGame object\n";
}

void MyGame::init() {
    // Step A: Set up the camera
    mCamera = Camera(
            glm::vec2(50.0f, 33.0f),     // center of the WC
            100.0f,                              // width of WC
            {0, 0, 600, 400}  // viewport (orgX, orgY, width, height)
    );
    // set the background to gray
    mCamera.setBackgroundColor({0.8f, 0.8f, 0.8f, 1.0f});

    Mn::Texture minionSpriteTexture("assets/minion_sprite.png");

    // Step B: Create the font and minion images using sprite
    mFontImage = mEngine.createSpriteRenderable(Mn::Texture("assets/consolas-72.png"));
    mFontImage.setColor({1, 1, 1, 0});
    mFontImage.getXform().setPosition(15.0f, 50.0f);
    mFontImage.getXform().setSize(20.0f, 20.0f);

    mMinion = mEngine.createSpriteAnimateRenderable(minionSpriteTexture);
    mMinion.setColor({1.0f, 1.0f, 1.0f, 0.0f});
    mMinion.getXform().setPosition(15.0f, 25.0f);
    mMinion.getXform().setSize(24.0f, 19.2f);
    mMinion.setSpriteSequence(
            512, 0,     // first element pixel position: top-left 512 is top of image, 0 is left of image
            204, 164,       // width x height in pixels
            5,              // number of elements in this sequence
            0             // horizontal padding in between
    );
    mMinion.setAnimationType(eAnimationType::eSwing);
    mMinion.setAnimationSpeed(15); // show each element for mAnimSpeed updates

    // Step C: Create the hero object with texture from the lower-left corner
    mHero = mEngine.createSpriteRenderable(minionSpriteTexture);
    mHero.setColor({1.0f, 1.0f, 1.0f, 0.0f});
    mHero.getXform().setPosition(35.0f, 50.0f);
    mHero.getXform().setSize(12.0f, 18.0f);
    mHero.setElementPixelPositions(0, 120, 0, 180);

    // Create the fonts; prerequisite: fonts added in engine beforehand
    mTextSysFont = mEngine.createFontRenderable("system_default_font", "System Font: in Red");
    initText(mTextSysFont, 50, 60, {1.0f, 0.0f, 0.0f, 1.0f}, 3);

    mTextCon16 = mEngine.createFontRenderable("consolas-16", "Consolas 16: in black");
//    mTextCon16.setFontName(kFontCon16);
    initText(mTextCon16, 50, 55, {0.0f, 0.0f, 0.0f, 1.0f}, 2);

    mTextCon24 = mEngine.createFontRenderable("consolas-24", "Consolas 24: in black");
//    mTextCon24.setFontName(kFontCon24);
    initText(mTextCon24, 50, 50, {0.0f, 0.0f, 0.0f, 1.0f}, 3);

    mTextCon32 = mEngine.createFontRenderable("consolas-32", "Consolas 32: in white");
//    mTextCon32.setFontName(kFontCon32);
    initText(mTextCon32, 40, 40, {1.0f, 1.0f, 1.0f, 1.0f}, 4);

    mTextCon72 = mEngine.createFontRenderable("consolas-72", "Consolas 72: in blue");
//    mTextCon72.setFontName(kFontCon72);
    initText(mTextCon72, 30, 30, {0.0f, 0.0f, 1.0f, 1.0f}, 6);

    mTextSeg96 = mEngine.createFontRenderable("segment7-96", "Segment7-92");
//    mTextSeg96.setFontName(kFontSeg96);
    initText(mTextSeg96, 30, 15, {1.0f, 1.0f, 0.0f, 1.0f}, 7);

    mTextToWork = &mTextCon16;
}

void MyGame::initText(
        FontRenderable &font,
        float posX,
        float posY,
        glm::vec4 color,
        float textH
) {
    font.setColor(color);
    font.getXform().setPosition(posX, posY);
    font.setTextHeight(textH);
}

void MyGame::draw() {
    // Step A: clear the canvas
    Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f); // clear to light gray
    mCamera.clear();

    // Step B: Activate the drawing Camera
    mCamera.setViewAndCameraMatrix();

    // Step C: draw everything
    mHero.draw(mCamera);
    mFontImage.draw(mCamera);
    mMinion.draw(mCamera);

    // drawing the text output
    mTextSysFont.draw(mCamera);
    mTextCon16.draw(mCamera);
    mTextCon24.draw(mCamera);
    mTextCon32.draw(mCamera);
    mTextCon72.draw(mCamera);
    mTextSeg96.draw(mCamera);
}

void MyGame::update(const Mn::Input &input) {
    if (input.IsClickedKey(MN_KEY_ESCAPE)) {
        mSceneRunning = false;
    }

    // Let's only allow the movement of hero
    Transform &xform = mHero.getXform();
    auto deltaX = 0.5f;

    // Support hero movements
    if (input.IsPressedKey(MN_KEY_RIGHT)) {
        xform.incXPosBy(deltaX);
        if (xform.getXPos() > 100.0f) { // this is the right-bound of the window
            xform.setPosition(0.0f, 50.0f);
        }
    }

    if (input.IsPressedKey(MN_KEY_LEFT)) {
        xform.incXPosBy(-deltaX);
        if (xform.getXPos() < 0.0f) { // this is the left-bound of the window
            xform.setPosition(100.0f, 50.0f);
        }
    }

    // New update code for changing the sub-texture regions being shown
    float deltaT = 0.001f;

    // The font image:
    // zoom into the texture by updating texture coordinate
    // For font: zoom to the upper left corner by changing bottom right
    std::vector<float> texCoord = mFontImage.getElementUVCoordinateArray();
    // The 8 elements:
    //      mTexRight,  mTexTop,          // x,y of top-right
    //      mTexLeft,   mTexTop,
    //      mTexRight,  mTexBottom,
    //      mTexLeft,   mTexBottom
    float b = texCoord[5] + deltaT; // bottom
    float r = texCoord[0] - deltaT; // right
    if (b > 1.0f) {
        b = 0.0f;
    }
    if (r < 0.0f) {
        r = 1.0f;
    }
    mFontImage.setElementUVCoordinate(
            texCoord[2], // left
            r,
            b,
            texCoord[1] // top
    );

    // remember to update the minion's animation
    mMinion.updateAnimation();

    // interactive control of the display size

    // choose which text to work on
    if (input.IsClickedKey(MN_KEY_0)) {
        mTextToWork = &mTextCon16;
    }
    if (input.IsClickedKey(MN_KEY_1)) {
        mTextToWork = &mTextCon24;
    }
    if (input.IsClickedKey(MN_KEY_3)) {
        mTextToWork = &mTextCon32;
    }
    if (input.IsClickedKey(MN_KEY_4)) {
        mTextToWork = &mTextCon72;
    }

    float deltaF = 0.005f;
    if (input.IsPressedKey(MN_KEY_UP)) {
        if (input.IsPressedKey(MN_KEY_X)) {
            mTextToWork->getXform().incWidthBy(deltaF);
        }
        if (input.IsPressedKey(MN_KEY_Y)) {
            mTextToWork->getXform().incHeightBy(deltaF);
        }
        std::string msg = textFromNumber(mTextToWork->getXform().getWidth()) + " x " + textFromNumber(mTextToWork->getXform().getHeight());
        mTextSysFont.setText(msg);
    }

    if (input.IsPressedKey(MN_KEY_DOWN)) {
        if (input.IsPressedKey(MN_KEY_X)) {
            mTextToWork->getXform().incWidthBy(-deltaF);
        }
        if (input.IsPressedKey(MN_KEY_Y)) {
            mTextToWork->getXform().incHeightBy(-deltaF);
        }
        std::string msg = textFromNumber(mTextToWork->getXform().getWidth()) + " x " + textFromNumber(mTextToWork->getXform().getHeight());
        mTextSysFont.setText(msg);
    }
}

std::string MyGame::textFromNumber(float n) {
    std::stringstream s{};
    s << n;
    return s.str();
}
