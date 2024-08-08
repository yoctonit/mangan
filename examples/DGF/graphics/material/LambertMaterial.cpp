#include "LambertMaterial.h"

LambertMaterial::LambertMaterial(const std::shared_ptr<Texture> &texture)
        : Material(
        "shader/LambertMaterial.vert",
        "shader/LambertMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));

    /*
    addUniform("bool", "useTexture", 0);

    if (texture != null)
        addTextureData(texture);
    */
    addUniform("useBumpTexture", false);

//    addUniform("bool", "useShadow", 0);

    if (texture == nullptr)
        addUniform("useTexture", false);
    else {
        addUniform("useTexture", true);
        addUniform("tex", texture->textureRef(), 1);
    }

    m_renderSettings.Activate(RenderSettings::Type::DoubleSide);
    m_renderSettings.set(RenderSettings::Type::DoubleSide, true);

    m_renderSettings.Activate(RenderSettings::Type::Wireframe);
    m_renderSettings.set(RenderSettings::Type::Wireframe, false);

    m_renderSettings.Activate(RenderSettings::Type::LineWidth);
}

bool LambertMaterial::usesLight() const {
    return true;
}

void LambertMaterial::addBumpData(const std::shared_ptr<Texture> &bumpTexture, float bumpStrength) {
    m_uniforms["useBumpTexture"].data().m_dataBool = true;
    addUniform("bumpTexture", bumpTexture->textureRef(), 2);
    addUniform("bumpStrength", bumpStrength);
}
