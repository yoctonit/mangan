#ifndef DGF_GRAPHICS_CORE_SCENE_H
#define DGF_GRAPHICS_CORE_SCENE_H

#include "Object3D.h"

class Scene : public Object3D {
public:
    explicit Scene(const std::string& name = "main");
};

#endif //DGF_GRAPHICS_CORE_SCENE_H
