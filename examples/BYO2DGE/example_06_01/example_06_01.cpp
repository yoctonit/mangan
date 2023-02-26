#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteAnimateRenderable.h"
#include "byo2dge/renderable/FontRenderable.h"
#include "byo2dge/SceneFileParser.h"
#include "byo2dge/game_objects/GameObject.h"
#include "byo2dge/game_objects/GameObjectSet.h"

class DyePack : public GameObject {
public:
    DyePack(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &spriteTexture
    ) : GameObject() {
        kRefWidth = 80.0f;
        kRefHeight = 130.0f;

        mRenderComponent = std::make_shared<SpriteRenderable>(ss, sq, spriteTexture);
        mRenderComponent->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
        mRenderComponent->getXform()->setPosition(50.0f, 33.0f);
        mRenderComponent->getXform()->setSize(kRefWidth / 50.0f, kRefHeight / 50.0f);
        mRenderComponent->setElementPixelPositions(510.0f, 595.0f, 23.0f, 153.0f);
    }

private:
    float kRefWidth;
    float kRefHeight;
};


class Hero : public GameObject {
public:
    Hero(const std::shared_ptr<ShaderInterface> &ss,
         const std::shared_ptr<SquareGeometryBuffer> &sq,
         const std::shared_ptr<Mn::Texture> &spriteTexture
    ) : GameObject() {
        kDelta = 0.3f;

        mRenderComponent = std::make_shared<SpriteRenderable>(ss, sq, spriteTexture);
        mRenderComponent->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mRenderComponent->getXform()->setPosition(35.0f, 50.0f);
        mRenderComponent->getXform()->setSize(9.0f, 12.0f);
        mRenderComponent->setElementPixelPositions(0.0f, 120.0f, 0.0f, 180.0f);
    }

    void update(const Mn::Input &input) override {
        // control by WASD
        auto xform = getXform();
        if (input.is_pressed(Mn::key::w)) {
            xform->incYPosBy(kDelta);
        }
        if (input.is_pressed(Mn::key::s)) {
            xform->incYPosBy(-kDelta);
        }
        if (input.is_pressed(Mn::key::a)) {
            xform->incXPosBy(-kDelta);
        }
        if (input.is_pressed(Mn::key::d)) {
            xform->incXPosBy(kDelta);
        }
    }

private:
    float kDelta{};
};

class Minion : public GameObject {
public:
    Minion(const std::shared_ptr<ShaderInterface> &ss,
           const std::shared_ptr<SquareGeometryBuffer> &sq,
           const std::shared_ptr<Mn::Texture> &spriteTexture,
           float atY) : GameObject() {

        kDelta = 0.2f;
        mRenderComponent = std::make_shared<SpriteAnimateRenderable>(ss, sq, spriteTexture);
        mRenderComponent->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mRenderComponent->getXform()->setPosition(float(rand() % 100), atY);
        mRenderComponent->getXform()->setSize(12.0f, 9.6f);
        mRenderComponent->setSpriteSequence(512.0f,0.0f,      // first element pixel position: top-left 512 is top of image, 0 is left of image
                                            204.0f, 164.0f,   // width x height in pixels
                                            5.0f,          // number of elements in this sequence
                                            0.0f);         // horizontal padding in between
        mRenderComponent->setAnimationType(eAnimationType::eSwing);
        mRenderComponent->setAnimationSpeed(15);
        // show each element for mAnimSpeed updates
    }

    void update(const Mn::Input &input) override {
        // remember to update mRenderComponent's animation
        mRenderComponent->updateAnimation();

        // move towards the left and wraps
        auto xform = getXform();
        xform->incXPosBy(-kDelta);

        // if fly off to the left, re-appear at the right
        if (xform->getXPos() < 0) {
            xform->setXPos(100);
            xform->setYPos(rand() % 65);
            // xform->setYPos(65 * Math.random());
        }
    }

private:
    float kDelta{};
};

class MyGame : public Level {
public:
    void initialize(int, int, std::shared_ptr<Engine> engine) override {
        mCamera = std::make_shared<Camera>(
                glm::vec2(50.0f, 37.5f), // center of the WC
                100.0f, // width of WC
                glm::ivec4(0, 0, 640, 480) // viewport:orgX, orgY, W, H
        );
        mCamera->setBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

        auto minionSpriteTexture = std::make_shared<Mn::Texture>("assets/minion_sprite.png", GL_RGBA);
        auto fontSysTexture = std::make_shared<Mn::Texture>("assets/fonts/system_default_font.png", GL_RGBA);

        mDyePack = std::make_shared<DyePack>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );

        float randomY;
        // create 5 minions at random Y values
        // float randomPositions[5] = {17.0f, 24.0f,38.0f,45.0f,60.0f};
        for (int i = 0; i < 5; i++) {
            // randomY = Math.random() * 65;
            randomY = rand() % 65;
            // aMinion = new Minion(this.kMinionSprite, randomY);
            auto aMinion = std::make_shared<Minion>(
                    engine->getSpriteShader(),
                    engine->getSquareGeometryBuffer(),
                    minionSpriteTexture,
                    randomY
            );
            mMinionSet.addToSet(aMinion);
        }

        mHero = std::make_shared<Hero>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );

        // Create the fonts
        mFISys = parseFonts("assets/fonts/system_default_font.json");
        mMsg = std::make_shared<FontRenderable>(
                "Status Message",
                mFISys,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontSysTexture
                ));
        mMsg->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        mMsg->getXform()->setPosition(1.0f, 2.0f);
        mMsg->setTextHeight(3.0f);
    }

    void draw() const override {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);

        mCamera->setViewAndCameraMatrix();

        mHero->draw(*mCamera);
        mMinionSet.draw(*mCamera);
        mDyePack->draw(*mCamera);
        mMsg->draw(*mCamera);
    }

    void update(const Mn::Input &input, double) override {
        mHero->update(input);
        mMinionSet.update(input);
        mDyePack->update(input);
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;

    std::shared_ptr<Hero> mHero;
    GameObjectSet mMinionSet;
    std::shared_ptr<DyePack> mDyePack;

    FontInfo mFISys{};
    std::shared_ptr<FontRenderable> mMsg;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    Mn::Run<Game>(game, window);
    return 0;
}
