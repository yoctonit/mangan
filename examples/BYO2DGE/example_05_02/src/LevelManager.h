#ifndef BYO2DGE_LEVEL_MANAGER_H
#define BYO2DGE_LEVEL_MANAGER_H

#include <memory>
#include <utility>
#include "engine/Input.h"

class LevelManager;

class Level {
public:
    explicit Level(LevelManager &levelManager) : mLevelManager{levelManager} {}

    virtual ~Level() = default;

    virtual void init() = 0;

    virtual void draw() = 0;

    virtual void update(const Mn::Input &input) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void next() = 0;

    [[nodiscard]] virtual bool isRunning() const {
        return mLevelRunning;
    }

protected:
    LevelManager &mLevelManager;
    bool mLevelRunning{false};
};

class LevelManager {
public:
    void setLevel(std::shared_ptr<Level> level) {
        level->init();
        mCurrentLevel = std::move(level);
        mCurrentLevel->start();
    }

    std::shared_ptr<Level> currentLevel() {
        return mCurrentLevel;
    }

//    void draw() {
//        mCurrentLevel->draw();
//    }
//
//    void update(const Mn::Input &input) {
//        mCurrentLevel->update(input);
//    }
//
//    [[nodiscard]] bool isRunning() const {
//        return mCurrentLevel->isRunning();
//    }

protected:
    std::shared_ptr<Level> mCurrentLevel;
};

#endif //BYO2DGE_LEVEL_MANAGER_H
