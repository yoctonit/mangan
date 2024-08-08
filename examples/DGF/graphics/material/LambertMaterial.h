#ifndef DGF_GRAPHICS_MATERIAL_LAMBERT_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_LAMBERT_MATERIAL_H

#include <memory>
#include "Material.h"
#include "../core/Texture.h"

class LambertMaterial : public Material {
public:
    explicit LambertMaterial(const std::shared_ptr<Texture>& texture);

    [[nodiscard]] bool usesLight() const override;

//    void addTextureData(std::shared_ptr<Texture> texture);

    void addBumpData(const std::shared_ptr<Texture> &bumpTexture, float bumpStrength);

//    void enableShadow();
};

#endif //DGF_GRAPHICS_MATERIAL_LAMBERT_MATERIAL_H
