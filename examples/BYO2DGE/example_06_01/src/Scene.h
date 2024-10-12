#ifndef BYO2DGE_SCENE_H
#define BYO2DGE_SCENE_H

#include "engine/Input.h"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void init() = 0;

    virtual void draw() = 0;

    virtual void update(const Mn::Input &input) = 0;

    [[nodiscard]] virtual bool isRunning() const {
        return mSceneRunning;
    }

protected:
    bool mSceneRunning{true};
};

#endif //BYO2DGE_SCENE_H
