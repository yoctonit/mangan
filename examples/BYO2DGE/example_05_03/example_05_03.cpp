#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteAnimateRenderable.h"

class MyGame : public Level {
public:
    void initialize(int, int, std::shared_ptr<Engine> engine) override {
        mCamera = std::make_shared<Camera>(
                glm::vec2(20.0f, 60.0f), // center of the WC
                20.0f, // width of WC
                glm::ivec4(20, 40, 600, 300) // viewport:orgX, orgY, W, H
        );
        mCamera->setBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

        auto fontTexture = std::make_shared<Mn::Texture>("assets/consolas-72.png", GL_RGBA);
        auto minionSpriteTexture = std::make_shared<Mn::Texture>("assets/minion_sprite.png", GL_RGBA);

        mPortal = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mPortal->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.2f)); // tints red
        mPortal->getXform()->setPosition(25.0f, 60.0f);
        mPortal->getXform()->setSize(3.0f, 3.0f);
        mPortal->setElementPixelPositions(130.0f, 310.0f, 0.0f, 180.0f);

        mCollector = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mCollector->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); // no tinting
        mCollector->getXform()->setPosition(15.0f, 60.0f);
        mCollector->getXform()->setSize(3.0f, 3.0f);
        mCollector->setElementUVCoordinate(0.308f, 0.483f, 0.0f, 0.352f);

        mFontImage = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                fontTexture
        );
        mFontImage->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mFontImage->getXform()->setPosition(13.0f, 62.0f);
        mFontImage->getXform()->setSize(4.0f, 4.0f);

        mRightMinion = std::make_shared<SpriteAnimateRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mRightMinion->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mRightMinion->getXform()->setPosition(26.0f, 56.5f);
        mRightMinion->getXform()->setSize(4.0f, 3.2f);
        mRightMinion->setSpriteSequence(512,
                                        0,                           // first element pixel position: top-left 512 is top of image, 0 is left of image
                                        204, 164, // width x height in pixels
                                        5,                       // number of elements in this sequence
                                        0);                    // horizontal padding in between
        mRightMinion->setAnimationType(eAnimationType::eRight);
        mRightMinion->setAnimationSpeed(50);

        mLeftMinion = std::make_shared<SpriteAnimateRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mLeftMinion->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mLeftMinion->getXform()->setPosition(15.0f, 56.5f);
        mLeftMinion->getXform()->setSize(4.0f, 3.2f);
        mLeftMinion->setSpriteSequence(348,
                                        0,                           // first element pixel position: top-left 512 is top of image, 0 is left of image
                                        204, 164, // width x height in pixels
                                        5,                       // number of elements in this sequence
                                        0);                    // horizontal padding in between
        mLeftMinion->setAnimationType(eAnimationType::eRight);
        mLeftMinion->setAnimationSpeed(50);

        mHero = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mHero->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mHero->getXform()->setPosition(20.0f, 60.0f);
        mHero->getXform()->setSize(2.0f, 3.0f);
        mHero->setElementPixelPositions(0.0f, 120.0f, 0.0f, 180.0f);
    }

    void draw() const override {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);

        mCamera->setViewAndCameraMatrix();

        mPortal->draw(*mCamera);
        mCollector->draw(*mCamera);
        mHero->draw(*mCamera);
        mFontImage->draw(*mCamera);
        mRightMinion->draw(*mCamera);
        mLeftMinion->draw(*mCamera);
    }

    void update(const Mn::Input &input, double) override {
        float deltaX = 0.05;
        std::shared_ptr<Transform> xform = mHero->getXform();

        if (input.is_pressed(Mn::key::right)) {
            xform->incXPosBy(deltaX);
            if (xform->getXPos() > 30.0f) // the right-bound of the window
                xform->setPosition(12.0f, 60.0f);
        }
        if (input.is_pressed(Mn::key::left)) {
            xform->incXPosBy(-deltaX);
            if (xform->getXPos() < 11.0f) // the right-bound of the window
                setFinished(true);
        }

        // continuously change texture tinting
        glm::vec4 c = mPortal->getColor();
        float ca = c[3] + deltaX / 2.0f;
        if (ca > 1.0f) {
            ca = 0.0f;
        }
        c[3] = ca;
        mPortal->setColor(c);

        // New update code for changing the sub-texture regions being shown"
        float deltaT = 0.001;

        // The font image:
        // zoom into the texture by updating texture coordinate
        // For font: zoom to the upper left corner by changing bottom right
        std::vector<float> texCoord = mFontImage->getElementUVCoordinateArray();
        // The 8 elements:
        //      mTexRight,  mTexTop,          // x,y of top-right
        //      mTexLeft,   mTexTop,
        //      mTexRight,  mTexBottom,
        //      mTexLeft,   mTexBottom
        float b = texCoord[5] + deltaT; // eTexCoordArrayIndex.eBottom
        float r = texCoord[0] - deltaT; // eTexCoordArrayIndex.eRight
        if (b > 1.0) {
            b = 0;
        }
        if (r < 0) {
            r = 1.0;
        }
        mFontImage->setElementUVCoordinate(
                texCoord[2], // eTexCoordArrayIndex.eLeft
                r,
                b,
                texCoord[1] // eTexCoordArrayIndex.eTop
        );

        // New code for controlling the sprite animation
        // controlling the sprite animation:
        // remember to update the minion's animation
        mRightMinion->updateAnimation();
        mLeftMinion->updateAnimation();

        // Animate left on the sprite sheet
        if (input.is_clicked(Mn::key::a)) {
            mRightMinion->setAnimationType(eAnimationType::eLeft);
            mLeftMinion->setAnimationType(eAnimationType::eLeft);
        }

        // swing animation
        if (input.is_clicked(Mn::key::s)) {
            mRightMinion->setAnimationType(eAnimationType::eSwing);
            mLeftMinion->setAnimationType(eAnimationType::eSwing);
        }

        // Animate right on the sprite sheet
        if (input.is_clicked(Mn::key::d)) {
            mRightMinion->setAnimationType(eAnimationType::eRight);
            mLeftMinion->setAnimationType(eAnimationType::eRight);
        }

        // decrease the duration of showing each sprite element, thereby speeding up the animation
        if (input.is_clicked(Mn::key::q)) {
            mRightMinion->incAnimationSpeed(-2);
            mLeftMinion->incAnimationSpeed(-2);
        }

        // increase the duration of showing each sprite element, thereby slowing down the animation
        if (input.is_clicked(Mn::key::e)) {
            mRightMinion->incAnimationSpeed(2);
            mLeftMinion->incAnimationSpeed(2);
        }
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Renderable> mHero;
    std::shared_ptr<Renderable> mPortal;
    std::shared_ptr<Renderable> mCollector;
    std::shared_ptr<Renderable> mFontImage;
    std::shared_ptr<Renderable> mRightMinion;
    std::shared_ptr<Renderable> mLeftMinion;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    Mn::Run<Game>(game, window);
    return 0;
}
