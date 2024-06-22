#ifndef DGF_GRAPHICS_CORE_GROUP_H
#define DGF_GRAPHICS_CORE_GROUP_H

#include "Object3D.h"

class Group : public Object3D {
public:
    explicit Group(const std::string &name);
};

#endif //DGF_GRAPHICS_CORE_GROUP_H
