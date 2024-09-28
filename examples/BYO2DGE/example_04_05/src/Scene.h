#ifndef BYO2DGE_SCENE_H
#define BYO2DGE_SCENE_H

#include "engine/Input.h"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void init() = 0;

    virtual void draw() = 0;

    virtual void update(const Mn::Input &input) = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void next() = 0;
};

#endif //BYO2DGE_SCENE_H
