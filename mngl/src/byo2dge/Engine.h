#ifndef OPENGL_EXAMPLES_ENGINE_H
#define OPENGL_EXAMPLES_ENGINE_H

#include <memory>
#include "SquareGeometryBuffer.h"
#include "shader/SimpleShader.h"
#include "shader/TextureShader.h"
#include "shader/SpriteShader.h"

class Engine {
public:
    Engine() {
        mSquareGeometryBuffer = std::make_shared<SquareGeometryBuffer>();

        mConstColorShader = std::make_shared<SimpleShader>(
                "shader/simple.vs",
                "shader/simple.fs");
        mTextureShader = std::make_shared<TextureShader>(
                "shader/texture.vs",
                "shader/texture.fs");
        mSpriteShader = std::make_shared<SpriteShader>(
                "shader/texture.vs",
                "shader/texture.fs");
    }

    static void clearCanvas(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Allows transparency with textures.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    [[nodiscard]] std::shared_ptr<SquareGeometryBuffer> getSquareGeometryBuffer() const { return mSquareGeometryBuffer; }

    [[nodiscard]] std::shared_ptr<SimpleShader> getConstColorShader() const { return mConstColorShader; }

    [[nodiscard]] std::shared_ptr<TextureShader> getTextureShader() const { return mTextureShader; }
    [[nodiscard]] std::shared_ptr<SpriteShader> getSpriteShader() const { return mSpriteShader; }

private:
    std::shared_ptr<SquareGeometryBuffer> mSquareGeometryBuffer;
    std::shared_ptr<SimpleShader> mConstColorShader{};
    std::shared_ptr<TextureShader> mTextureShader{};
    std::shared_ptr<SpriteShader> mSpriteShader{};
};

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

#endif //OPENGL_EXAMPLES_ENGINE_H
