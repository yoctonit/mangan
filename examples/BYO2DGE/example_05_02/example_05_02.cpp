#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteRenderable.h"

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

        mMinion = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mMinion->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mMinion->getXform()->setPosition(26.0f, 56.0f);
        mMinion->getXform()->setSize(5.0f, 2.5f);

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
        mMinion->draw(*mCamera);
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
//        if (input.is_clicked(Mn::key::q)) {
//            setFinished(true);
//        }
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

        // The minion image:
        // For minion: zoom to the bottom right corner by changing top left
        texCoord = mMinion->getElementUVCoordinateArray();
        // The 8 elements:
        //      mTexRight,  mTexTop,          // x,y of top-right
        //      mTexLeft,   mTexTop,
        //      mTexRight,  mTexBottom,
        //      mTexLeft,   mTexBottom
        float t = texCoord[1] - deltaT; // eTexCoordArrayIndex.eTop
        float l = texCoord[2] + deltaT; // eTexCoordArrayIndex.eLeft
        if (l > 0.5) {
            l = 0;
        }
        if (t < 0.5) {
            t = 1.0;
        }
        mMinion->setElementUVCoordinate(
                l,
                texCoord[0], // eTexCoordArrayIndex.eRight
                texCoord[5], // eTexCoordArrayIndex.eBottom
                t
        );
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Renderable> mHero;
    std::shared_ptr<Renderable> mPortal;
    std::shared_ptr<Renderable> mCollector;
    std::shared_ptr<Renderable> mFontImage;
    std::shared_ptr<Renderable> mMinion;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    Mn::Run<Game>(game, window);
    return 0;
}
