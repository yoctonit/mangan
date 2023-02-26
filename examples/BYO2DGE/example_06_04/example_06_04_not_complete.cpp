#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteAnimateRenderable.h"
#include "byo2dge/renderable/FontRenderable.h"
#include "byo2dge/SceneFileParser.h"
#include "byo2dge/game_objects/GameObject.h"

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

class TextureObject : public GameObject {
public:
    TextureObject(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &spriteTexture,
            float x, float y, float w, float h
    ) : GameObject() {
        kDelta = 0.2f;

        mRenderComponent = std::make_shared<TextureRenderable>(ss, sq, spriteTexture);
        mRenderComponent->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
        mRenderComponent->getXform()->setPosition(x, y);
        mRenderComponent->getXform()->setSize(w, h);

//        mTest = std::make_shared<TextureRenderable>(
//                engine->getSpriteShader(),
//                engine->getSquareGeometryBuffer(),
//                minionCollectorTexture
//        );
//        mTest->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
//        mTest->getXform()->setPosition(50.0f, 30.0f);
//        mTest->getXform()->setSize(30.0f, 30.0f);

    }
    TextureObject(
            const std::shared_ptr<TextureRenderable> &tr,
            float x, float y, float w, float h
    ) : GameObject() {
        kDelta = 0.2f;

        mRenderComponent = tr;
    }

    void update1(const Mn::Input &input,
                 Mn::key up, Mn::key down, Mn::key left, Mn::key right) {
        auto xform = getXform();
        if (input.is_pressed(up)) {
            xform->incYPosBy(kDelta);
        }
        if (input.is_pressed(down)) {
            xform->incYPosBy(-kDelta);
        }
        if (input.is_pressed(left)) {
            xform->incXPosBy(-kDelta);
        }
        if (input.is_pressed(right)) {
            xform->incXPosBy(kDelta);
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
        auto minionCollectorTexture = std::make_shared<Mn::Texture>("assets/minion_collector.png", GL_RGBA);
        auto minionPortalTexture = std::make_shared<Mn::Texture>("assets/minion_portal.png", GL_RGBA);
//        auto fontSysTexture = std::make_shared<Mn::Texture>("assets/fonts/system_default_font.png", GL_RGBA);

        mDyePack = std::make_shared<DyePack>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mDyePack->setVisibility(false);

//        mCollector = std::make_shared<TextureObject>(
//                engine->getSpriteShader(),
//                engine->getSquareGeometryBuffer(),
//                minionCollectorTexture,
//                50.0f, 30.0f, 30.0f, 30.0f
//        );
//        mPortal = std::make_shared<TextureObject>(
//                engine->getSpriteShader(),
//                engine->getSquareGeometryBuffer(),
//                minionPortalTexture,
//                70.0f, 30.0f, 10.0f, 10.0f
//        );

        mTest = std::make_shared<TextureRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionCollectorTexture
        );
        mTest->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
        mTest->getXform()->setPosition(50.0f, 30.0f);
        mTest->getXform()->setSize(30.0f, 30.0f);
        mCollector = std::make_shared<TextureObject>(mTest, 70.0f, 30.0f, 10.0f, 10.0f);

        mTest = std::make_shared<TextureRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionPortalTexture
        );
        mTest->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.1f));
        mTest->getXform()->setPosition(70.0f, 30.0f);
        mTest->getXform()->setSize(10.0f, 10.0f);
        mPortal = std::make_shared<TextureObject>(mTest, 70.0f, 30.0f, 10.0f, 10.0f);

        // Create the fonts
//        mFISys = parseFonts("assets/fonts/system_default_font.json");
//        mMsg = std::make_shared<FontRenderable>(
//                "Status Message",
//                mFISys,
//                std::make_shared<SpriteRenderable>(
//                        engine->getSpriteShader(),
//                        engine->getSquareGeometryBuffer(),
//                        fontSysTexture
//                ));
//        mMsg->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//        mMsg->getXform()->setPosition(1.0f, 2.0f);
//        mMsg->setTextHeight(3.0f);
    }

    void draw() const override {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);

        mCamera->setViewAndCameraMatrix();

//        mTest->draw(*mCamera);
        mCollector->draw(*mCamera);
        mPortal->draw(*mCamera);
        mDyePack->draw(*mCamera);
//        mMsg->draw(*mCamera);
    }

    void update(const Mn::Input &input, double) override {
        std::string msg = "No Collision";

        mCollector->update1(input, Mn::key::w, Mn::key::s,
                            Mn::key::a, Mn::key::d);
        mPortal->update1(input, Mn::key::up, Mn::key::down,
                         Mn::key::left, Mn::key::right);

        glm::vec2 h;

        // Portal's resolution is 1/16 x 1/16 that of Collector!
        // if (mCollector.pixelTouches(mPortal, h)) {  // <-- VERY EXPENSIVE!!
        if (mPortal->pixelTouches(mCollector, h)) {
            msg = "Collided!: (" + std::to_string(h.x) + " " + std::to_string(h.y) + ")";
            mDyePack->setVisibility(true);
            mDyePack->getXform()->setXPos(h.x);
            mDyePack->getXform()->setYPos(h.y);
        } else {
            mDyePack->setVisibility(false);
        }
        // mMsg->setText(msg);
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;

    std::shared_ptr<DyePack> mDyePack;
    std::shared_ptr<TextureObject> mCollector;
    std::shared_ptr<TextureObject> mPortal;
    std::shared_ptr<TextureRenderable> mTest;

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
