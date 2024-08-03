#ifndef DGF_GRAPHICS_MATERIAL_FLAT_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_FLAT_MATERIAL_H

#include <memory>
#include "Material.h"
#include "../core/Texture.h"

class FlatMaterial : public Material {
public:
    explicit FlatMaterial(std::shared_ptr<Texture> texture);
};

#endif //DGF_GRAPHICS_MATERIAL_FLAT_MATERIAL_H
