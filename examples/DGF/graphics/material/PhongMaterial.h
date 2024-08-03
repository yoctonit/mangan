#ifndef DGF_GRAPHICS_MATERIAL_PHONG_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_PHONG_MATERIAL_H

#include <memory>
#include "Material.h"
#include "../core/Texture.h"

class PhongMaterial : public Material {
public:
    explicit PhongMaterial(std::shared_ptr<Texture> texture);

//    void addTextureData(std::shared_ptr<Texture> texture);
//
//    void addBumpData(std::shared_ptr<Texture> bumpTexture, float bumpStrength);
//
//    void enableShadow();
};

#endif //DGF_GRAPHICS_MATERIAL_PHONG_MATERIAL_H
