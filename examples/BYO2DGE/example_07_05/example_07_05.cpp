#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/renderable/SpriteAnimateRenderable.h"
#include "byo2dge/renderable/FontRenderable.h"
#include "byo2dge/SceneFileParser.h"
#include "byo2dge/game_objects/GameObject.h"

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

        if (input.is_pressed(Mn::key::left)) {
            xf->incRotationByDegree(kDeltaDegree);
            auto forward_direction = getCurrentFrontDir();
            forward_direction = GameObject::RotateVec2(forward_direction, kDeltaRad);
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

class Minion : public GameObject {
public:
    Minion(const std::shared_ptr<ShaderInterface> &ss,
           const std::shared_ptr<SquareGeometryBuffer> &sq,
           const std::shared_ptr<Mn::Texture> &spriteTexture,
           float atX, float atY) : GameObject() {

        kDelta = 0.2f;
        mRenderComponent = std::make_shared<SpriteAnimateRenderable>(ss, sq, spriteTexture);
        mRenderComponent->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
        mRenderComponent->getXform()->setPosition(atX, atY);
        mRenderComponent->getXform()->setSize(12.0f, 9.6f);
        mRenderComponent->setSpriteSequence(512.0f,
                                            0.0f,      // first element pixel position: top-left 512 is top of image, 0 is left of image
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

    explicit TextureObject(const std::shared_ptr<TextureRenderable> &tr) : GameObject() {
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

        mHeroCam = std::make_shared<Camera>(
                glm::vec2(50.0f, 30.0f), // update each cycle to point to hero
                20.0f,
                glm::ivec4(490, 330, 150, 150),
                2
        );
        mHeroCam->setBackgroundColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

        mBrainCam = std::make_shared<Camera>(
                glm::vec2(50.0f, 30.0f), // update each cycle to point to hero
                10.0f,
                glm::ivec4(0, 330, 150, 150),
                2
        );
        mBrainCam->setBackgroundColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        mBrainCam->configLerp(0.7f, 10);

        mChoice = 'D';

        // auto bgTexture = std::make_shared<Mn::Texture>("assets/bg.png", GL_RGB);
        // auto bgTexture = std::make_shared<Mn::Texture>("assets/minion_collector.png", GL_RGBA);
        auto minionSpriteTexture = std::make_shared<Mn::Texture>("assets/minion_sprite.png", GL_RGBA);
        auto minionPortalTexture = std::make_shared<Mn::Texture>("assets/minion_portal.png", GL_RGBA);
        auto fontSysTexture = std::make_shared<Mn::Texture>("assets/fonts/system_default_font.png", GL_RGBA);

        mBg1 = std::make_shared<SpriteRenderable>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mBg1->getXform()->setSize(150.0f, 150.f);
        mBg1->getXform()->setPosition(50.0f, 35.f);
        mBg1->setElementPixelPositions(0.0f, 1024.0f, 0.0f, 1024.0f);
        mBg = std::make_shared<GameObject>(mBg1);

        mHero = std::make_shared<Hero>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mBrain = std::make_shared<Brain>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture
        );
        mPortal = std::make_shared<TextureObject>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionPortalTexture,
                50.0f, 30.0f, 10.0f, 10.0f
        );
        mLMinion = std::make_shared<Minion>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture,
                30.0f, 30.0f
        );
        mRMinion = std::make_shared<Minion>(
                engine->getSpriteShader(),
                engine->getSquareGeometryBuffer(),
                minionSpriteTexture,
                70.0f, 30.0f
        );
        mFocusObj = mHero;

        mFISys = parseFonts("assets/fonts/system_default_font.json");
        mMsg = std::make_shared<FontRenderable>(
                "Status Message",
                mFISys,
                std::make_shared<SpriteRenderable>(
                        engine->getSpriteShader(),
                        engine->getSquareGeometryBuffer(),
                        fontSysTexture
                ));
        mMsg->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        mMsg->getXform()->setPosition(2.0f, 4.0f);
        mMsg->setTextHeight(3.0f);

        // create an Oscillate object to simulate motion
        mBounce = std::make_shared<Oscillate>(2.0f, 6.0f, 120); // delta, freq, duration
    }

    void draw() const override {
        Engine::clearCanvas(0.0f, 1.0f, 0.0f, 1.0f);

        drawCamera(mCamera);
        mMsg->draw(*mCamera);
        drawCamera(mHeroCam);
        drawCamera(mBrainCam);
    }

    void drawCamera(const std::shared_ptr<Camera> &cam) const {
        cam->setViewAndCameraMatrix();

        mBg->draw(*cam);
        mHero->draw(*cam);
        mBrain->draw(*cam);
        mPortal->draw(*cam);
        mLMinion->draw(*cam);
        mRMinion->draw(*cam);
    }

    void update(const Mn::Input &input, double) override {
        float zoomDelta = 0.05;
        std::string msg = "L/R: Left or Right Minion; H: Dye; P: Portal]: ";

        mCamera->update();  // for sprite animation
        mHeroCam->update();
        mBrainCam->update();

        mLMinion->update(input);  // for sprite animation
        mRMinion->update(input);

        mHero->update(input);     // for WASD movement
        mPortal->update(input     // for arrow movement
//                Mn::key::up,
//                Mn::key::down,
//                Mn::key::left,
//                Mn::key::right
        );

        // Brain chasing the hero
        glm::vec2 h;
        if (!mHero->pixelTouches(mBrain, h)) {
            mBrain->rotateObjPointTo(mHero->getXform()->getPosition(), 0.01f);
            mBrain->forward();
        }

        // Pan camera to object
        if (input.is_clicked(Mn::key::l)) {
            mFocusObj = mLMinion;
            mChoice = 'L';
            mCamera->panTo(mLMinion->getXform()->getXPos(), mLMinion->getXform()->getYPos());
        }
        if (input.is_clicked(Mn::key::r)) {
            mFocusObj = mRMinion;
            mChoice = 'R';
            mCamera->panTo(mRMinion->getXform()->getXPos(), mRMinion->getXform()->getYPos());
        }
        if (input.is_clicked(Mn::key::p)) {
            mFocusObj = mPortal;
            mChoice = 'P';
        }
        if (input.is_clicked(Mn::key::h)) {
            mFocusObj = mHero;
            mChoice = 'H';
        }

        // zoom
        if (input.is_clicked(Mn::key::n)) {
            mCamera->zoomBy(1 - zoomDelta);
        }
        if (input.is_clicked(Mn::key::m)) {
            mCamera->zoomBy(1 + zoomDelta);
        }
        if (input.is_clicked(Mn::key::j)) {
            mCamera->zoomTowards(mFocusObj->getXform()->getPosition(), 1 - zoomDelta);
        }
        if (input.is_clicked(Mn::key::k)) {
            mCamera->zoomTowards(mFocusObj->getXform()->getPosition(), 1 + zoomDelta);
        }

        // interaction with the WC bound
        mCamera->clampAtBoundary(mBrain->getXform(), 0.9f);
        mCamera->clampAtBoundary(mPortal->getXform(), 0.8f);
        mCamera->panWith(mHero->getXform(), 0.9f);

        if (input.is_clicked(Mn::key::q)) {
            if (!mCamera->reShake())
                mCamera->shake(glm::vec2(6.0f, 1.0f), glm::vec2(10.0f, 3.0f), 60);

            // also re-start bouncing effect
            mBounce->reStart();
        }

        if (!mBounce->done()) {
            float d = mBounce->getNext();
            mHero->getXform()->incXPosBy(d);
        }

        // set the hero and brain cams    
        mHeroCam->panTo(mHero->getXform()->getXPos(), mHero->getXform()->getYPos());
        mBrainCam->panTo(mBrain->getXform()->getXPos(), mBrain->getXform()->getYPos());

        msg = "";
        // testing the mouse input
        if (input.is_pressed(Mn::mouse::button::left)) {
            msg += "[L Down]";
            if (mCamera->isMouseInViewport(input)) {
                mPortal->getXform()->setXPos(mCamera->mouseWCX(input));
                mPortal->getXform()->setYPos(mCamera->mouseWCY(input));
            }
        }

        if (input.is_pressed(Mn::mouse::button::middle)) {
            if (mHeroCam->isMouseInViewport(input)) {
                mHero->getXform()->setXPos(mHeroCam->mouseWCX(input));
                mHero->getXform()->setYPos(mHeroCam->mouseWCY(input));
            }
        }
        if (input.is_clicked(Mn::mouse::button::right)) {
            mPortal->setVisibility(false);
        }

        if (input.is_clicked(Mn::mouse::button::middle)) {
            mPortal->setVisibility(true);
        }

        msg += " X=" + std::to_string(input.get_mouse_x_screen_position()) +
               " Y=" + std::to_string(input.get_mouse_y_screen_position());
        msg += " X=" + std::to_string(mCamera->mouseWCX(input)) +
               " Y=" + std::to_string(mCamera->mouseWCY(input));
        mMsg->setText(msg);
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Camera> mHeroCam;
    std::shared_ptr<Camera> mBrainCam;

    std::shared_ptr<Hero> mHero;
    std::shared_ptr<Brain> mBrain;
    std::shared_ptr<TextureObject> mPortal;
    std::shared_ptr<Minion> mLMinion;
    std::shared_ptr<Minion> mRMinion;
    std::shared_ptr<GameObject> mBg;
    std::shared_ptr<SpriteRenderable> mBg1;
    std::shared_ptr<GameObject> mFocusObj;
    std::shared_ptr<Oscillate> mBounce;

    FontInfo mFISys{};
    std::shared_ptr<FontRenderable> mMsg;
    char mChoice{};
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    Mn::Run<Game>(game, window);
    return 0;
}
