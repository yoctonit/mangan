#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/SceneFileParser.h"
#include "byo2dge/Renderable.h"
#include "byo2dge/TextureRenderable.h"

class Level {
public:
    virtual void initialize(int, int, std::shared_ptr<Engine> engine) = 0;

    virtual void draw() const = 0;

    virtual void update(const Mn::Input &input, double) = 0;

    [[nodiscard]] bool isFinished() const { return mIsFinished; }

    void setFinished(bool flag) { mIsFinished = flag; }

private:
    bool mIsFinished{};
};

class Game {
public:
    Game() {
        mCurrentLevelIndex = -1;
    }

    void addLevel(const std::shared_ptr<Level> &level) {
        mLevels.push_back(level);
    }

    void initialize(int w, int h) {
        if (mLevels.empty()) {
            std::cout << "Game has no levels\n";
            return;
        }
        mEngine = std::make_shared<Engine>();
        mWidth = w;
        mHeight = h;
        next();
    }

    void draw() const {
        mCurrentLevel->draw();
    }

    void update(const Mn::Input &input, double dt) {
        if (mCurrentLevel->isFinished()) {
            mCurrentLevel->setFinished(false);
            next();
            return;
        }
        mCurrentLevel->update(input, dt);
    }

    void cleanup() {}

private:
    std::shared_ptr<Engine> mEngine;
    int mCurrentLevelIndex{};
    std::shared_ptr<Level> mCurrentLevel{};
    std::vector<std::shared_ptr<Level>> mLevels;
    int mWidth{};
    int mHeight{};

    void next() {
        mCurrentLevelIndex++;
        if (mCurrentLevelIndex >= mLevels.size()) {
            // return;
            mCurrentLevelIndex = 0;
        }
        std::cout << "Next Called -> mCurrentLevelIndex: " << mCurrentLevelIndex << "\n";
        mCurrentLevel = mLevels[mCurrentLevelIndex];
        mCurrentLevel->initialize(mWidth, mHeight, mEngine);
    }
};

class MyGame : public Level {
public:
    void initialize(int, int, std::shared_ptr<Engine> engine) override {
        mCamera = std::make_shared<Camera>(
                glm::vec2(20.0f, 60.0f), // center of the WC
                20.0f, // width of WC
                glm::ivec4(20, 40, 600, 300) // viewport:orgX, orgY, W, H
        );
        mCamera->setBackgroundColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

        mPortal = std::make_shared<TextureRenderable>(
                engine->getTextureShader(),
                engine->getSquareGeometryBuffer(),
                std::make_shared<Mn::Texture>("assets/minion_portal.png", GL_RGBA)
        );
        mPortal->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));
        mPortal->getXform()->setPosition(25.0f, 60.0f);
        mPortal->getXform()->setSize(3.0f, 3.0f);

        mCollector = std::make_shared<TextureRenderable>(
                engine->getTextureShader(),
                engine->getSquareGeometryBuffer(),
                std::make_shared<Mn::Texture>("assets/minion_collector.png", GL_RGBA)
        );
        mCollector->setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); // no tinting
        mCollector->getXform()->setPosition(15.0f, 60.0f);
        mCollector->getXform()->setSize(3.0f, 3.0f);

        mHero = std::make_shared<Renderable>(
                engine->getConstColorShader(),
                engine->getSquareGeometryBuffer()
        );
        mHero->setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        mHero->getXform()->setPosition(20.0f, 60.0f);
        mHero->getXform()->setSize(2.0f, 3.0f);
    }

    void draw() const override {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);
        mCamera->setViewAndCameraMatrix();
        mPortal->draw(*mCamera);
        mCollector->draw(*mCamera);
        mHero->draw(*mCamera);
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
        if (input.is_clicked(Mn::key::q)) {
            setFinished(true);
        }
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Renderable> mHero;
    std::shared_ptr<Renderable> mPortal;
    std::shared_ptr<Renderable> mCollector;
};

class BlueLevel : public Level {
public:
    void initialize(int, int, std::shared_ptr<Engine> engine) override {
        SceneFileParser sceneParser("assets/blue_level.json");

        camera = sceneParser.parseCamera();
        mSqSet.clear();
        auto constColorSquares = sceneParser.parseSquares(
                engine->getConstColorShader(),
                engine->getSquareGeometryBuffer());
        mSqSet.insert(mSqSet.begin(), constColorSquares.begin(), constColorSquares.end());

        auto textureSquares = sceneParser.parseTextureSquares(
                engine->getTextureShader(),
                engine->getSquareGeometryBuffer());
        mSqSet.insert(mSqSet.end(), textureSquares.begin(), textureSquares.end());
    }

    void draw() const override {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);
        camera->setViewAndCameraMatrix();
        for (auto &sq: mSqSet)
            sq->draw(*camera);
    }

    void update(const Mn::Input &input, double) override {
        float deltaX = 0.05;
        std::shared_ptr<Transform> xform = mSqSet[1]->getXform();

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
        if (input.is_clicked(Mn::key::q)) {
            setFinished(true);
        }
        // continuously change texture tinting
        glm::vec4 c = mSqSet[1]->getColor();
        float ca = c[3] + deltaX;
        if (ca > 1) {
            ca = 0;
        }
        c[3] = ca;
    }

    void cleanup() {}

private:
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Renderable>> mSqSet;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    Game game;
    game.addLevel(std::make_shared<MyGame>());
    game.addLevel(std::make_shared<BlueLevel>());
    Mn::Run<Game>(game, window);
    return 0;
}
