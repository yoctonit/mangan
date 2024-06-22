#ifndef DGF_GRAPHICS_CORE_MESH_H
#define DGF_GRAPHICS_CORE_MESH_H

#include <memory>
#include "Object3D.h"
#include "../geometry/Geometry.h"
#include "../material/Material.h"


class Mesh : public Object3D {
public:
    Mesh(const std::string &name, std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);
};

#endif //DGF_GRAPHICS_CORE_MESH_H
