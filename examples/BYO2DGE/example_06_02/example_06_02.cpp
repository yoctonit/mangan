#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteAnimateRenderable.h"
#include "byo2dge/renderable/FontRenderable.h"
#include "byo2dge/SceneFileParser.h"
#include "byo2dge/game_objects/GameObject.h"
#include "byo2dge/game_objects/GameObjectSet.h"

class Brain : public GameObject {
public:
    Brain(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &spriteTexture)
            : GameObject() {

        kDeltaDegree = 1;
        kDeltaRad = M_PI * kDeltaDegree / 180.0f;
        kDeltaSpeed = 0.01;
        mRenderComponent = std::make_shared<SpriteRenderable>(ss, sq, spriteTexture);
        mRenderComponent->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mRenderComponent->getXform()->setPosition(50.0f, 10.0f);
        mRenderComponent->getXform()->setSize(3.0f, 5.4f);
        mRenderComponent->setElementPixelPositions(600.0f, 700.0f, 0.0f, 180.0f);

        setSpeed(0.05);
    }

    void update(const Mn::Input &input) override {
        GameObject::update(input);
        auto xf = getXform();
//        auto forward_direction = getCurrentFrontDir();

        if (input.is_pressed(Mn::key::left)) {
            xf->incRotationByDegree(kDeltaDegree);
            auto forward_direction = getCurrentFrontDir();
//            std::cout << "Current: " << forward_direction.x << ", " << forward_direction.y << std::endl;

            forward_direction = GameObject::RotateVec2(forward_direction, kDeltaRad);
//            std::cout << forward_direction.x << ", " << forward_direction.y << std::endl;
            setCurrentFrontDir(forward_direction);
        }
        if (input.is_pressed(Mn::key::right)) {
            xf->incRotationByRad(-kDeltaRad);
            auto forward_direction = getCurrentFrontDir();
            forward_direction = GameObject::RotateVec2(forward_direction, -kDeltaRad);
            setCurrentFrontDir(forward_direction);
        }
        if (input.is_pressed(Mn::key::up)) {
            incSpeedBy(kDeltaSpeed);
        }
        if (input.is_pressed(Mn::key::down)) {
            incSpeedBy(-kDeltaSpeed);
        }
    }

    void forward() {
        glm::vec2 pos = getXform()->getPosition();
        // vec2.scaleAndAdd(pos, pos, getCurrentFrontDir(), getSpeed());
        pos += mCurrentFrontDir * getSpeed();
        getXform()->setPosition(pos.x, pos.y);
    }

private:
    float kDeltaDegree;
    float kDeltaRad;
    float kDeltaSpeed;

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

        mMode = "H";

        mBrain = std::make_shared<Brain>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );

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
        mBrain->draw(*mCamera);
        mMsg->draw(*mCamera);
    }

    void update(const Mn::Input &input, double) override {
        std::string msg = "Brain [H:keys J:imm K:gradual]: ";
        float rate = 1.0f;

        mHero->update(input);

        if (mMode == "H") {
            mBrain->update(input);   // player steers with arrow keys
        } else if (mMode == "K") {
            rate = 0.02f; // gradual rate
            mBrain->rotateObjPointTo(mHero->getXform()->getPosition(), rate);
            mBrain->forward();
//            mBrain->update(input);
//            std::shared_ptr<GameObject> go = mBrain;
//            go->update(input);

            // After "K" is typed (in gradual mode), the following should also be executed.
        } else if (mMode == "J") {
            mBrain->rotateObjPointTo(mHero->getXform()->getPosition(), rate);
            mBrain->forward();
            // mBrain->update(input);
            // engine.GameObject.prototype.update.call(this.mBrain);  // the default GameObject: only move forward
//            std::shared_ptr<GameObject> go = mBrain;
//            go->update(input);
        }

        if (input.is_clicked(Mn::key::h)) {
            mMode = "H";
        }
        if (input.is_clicked(Mn::key::j)) {
            mMode = "J";
        }
        if (input.is_clicked(Mn::key::k)) {
            mMode = "K";
        }
        mMsg->setText(msg + mMode);
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;

    std::shared_ptr<Hero> mHero;
    std::shared_ptr<Brain> mBrain;

    FontInfo mFISys{};
    std::shared_ptr<FontRenderable> mMsg;
    std::string mMode;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    Mn::Run<Game>(game, window);
    return 0;
}
