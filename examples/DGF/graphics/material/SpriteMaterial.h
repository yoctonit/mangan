#ifndef DGF_GRAPHICS_MATERIAL_SPRITE_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_SPRITE_MATERIAL_H

#include "../core/Texture.h"
#include "Material.h"

class SpriteMaterial : public Material {
public:
    explicit SpriteMaterial(const Texture &texture);
};

#endif //DGF_GRAPHICS_MATERIAL_SPRITE_MATERIAL_H
