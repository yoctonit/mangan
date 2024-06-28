#ifndef DGF_GRAPHICS_MATERIAL_TEXTURE_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_TEXTURE_MATERIAL_H

#include "../core/Texture.h"
#include "Material.h"

class TextureMaterial : public Material {
public:
    explicit TextureMaterial(const Texture &texture);
};

#endif //DGF_GRAPHICS_MATERIAL_TEXTURE_MATERIAL_H
