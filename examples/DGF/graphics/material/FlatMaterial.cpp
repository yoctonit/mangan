#include "FlatMaterial.h"

FlatMaterial::FlatMaterial(const std::shared_ptr<Texture> &texture)
        : Material(
        "shader/FlatMaterial.vert",
        "shader/FlatMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));

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

bool FlatMaterial::usesLight() const {
    return true;
}
