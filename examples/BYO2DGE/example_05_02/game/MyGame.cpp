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
            glm::vec2(20.0f, 60.0f),     // center of the WC
            20.0f,                              // width of WC
            {20, 40, 600, 300}  // viewport (orgX, orgY, width, height)
    );
    // set the background to gray
    mCamera.setBackgroundColor({0.8f, 0.8f, 0.8f, 1.0f});

    Mn::Texture minionSpriteTexture("assets/minion_sprite.png");

    // Step B: Create the support objects:
    mPortal = mEngine.createSpriteRenderable(minionSpriteTexture);
    mPortal.setColor({1.0f, 0.0f, 0.0f, 0.2f});
    mPortal.getXform().setPosition(25.0f, 60.0f);
    mPortal.getXform().setSize(3.0f, 3.0f);
    mPortal.setElementPixelPositions(130, 310, 0, 180);

    mCollector = mEngine.createSpriteRenderable(minionSpriteTexture);
    mCollector.setColor({0.0f, 0.0f, 0.0f, 0.0f}); // no tinting
    mCollector.getXform().setPosition(15.0f, 60.0f);
    mCollector.getXform().setSize(3.0f, 3.0f);
    mCollector.setElementUVCoordinate(0.308, 0.483, 0, 0.352);

    // Step C: Create the font and minion images using sprite
    mFontImage = mEngine.createSpriteRenderable(Mn::Texture("assets/consolas-72.png"));
    mFontImage.setColor({1, 1, 1, 0});
    mFontImage.getXform().setPosition(13.0f, 62.0f);
    mFontImage.getXform().setSize(4.0f, 4.0f);

    mMinion = mEngine.createSpriteRenderable(minionSpriteTexture);
    mMinion.setColor({1.0f, 1.0f, 1.0f, 0.0f});
    mMinion.getXform().setPosition(26.0f, 56.0f);
    mMinion.getXform().setSize(5.0f, 2.5f);

    // Step D: Create the hero object with texture from the lower-left corner
    mHero = mEngine.createSpriteRenderable(minionSpriteTexture);
    mHero.setColor({1.0f, 1.0f, 1.0f, 0.0f});
    mHero.getXform().setPosition(20.0f, 60.0f);
    mHero.getXform().setSize(2.0f, 3.0f);
    mHero.setElementPixelPositions(0, 120, 0, 180);
}

void MyGame::draw() {
    // Step A: clear the canvas
    Core::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f); // clear to light gray
    mCamera.clear();

    // Step B: Activate the drawing Camera
    mCamera.setViewAndCameraMatrix();

    // Step C: draw everything
    mPortal.draw(mCamera);
    mCollector.draw(mCamera);
    mHero.draw(mCamera);
    mFontImage.draw(mCamera);
    mMinion.draw(mCamera);
}

void MyGame::update(const Mn::Input &input) {
    if (input.IsClickedKey(MN_KEY_ESCAPE)) {
        mSceneRunning = false;
    }

    // Let's only allow the movement of hero
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
            xform.setXPos(20.0f);
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

    // The minion image:
    // For minion: zoom to the bottom right corner by changing top left
    texCoord = mMinion.getElementUVCoordinateArray();
    // The 8 elements:
    //      mTexRight,  mTexTop,          // x,y of top-right
    //      mTexLeft,   mTexTop,
    //      mTexRight,  mTexBottom,
    //      mTexLeft,   mTexBottom
    float t = texCoord[1] - deltaT; // top
    float l = texCoord[2] + deltaT; // left

    if (l > 0.5f) {
        l = 0.0f;
    }
    if (t < 0.5f) {
        t = 1.0f;
    }

    mMinion.setElementUVCoordinate(
            l,
            texCoord[0], // right
            texCoord[5], // bottom
            t
    );
}
