#include "FlatMaterial.h"

FlatMaterial::FlatMaterial(std::shared_ptr<Texture> texture)
        : Material(
        "shader/FlatMaterial.vert",
        "shader/FlatMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    // addUniform("Light", "light0", null );
    // addUniform("Light", "light1", null );
    // addUniform("Light", "light2", null );
    // addUniform("Light", "light3", null );

    if (texture == nullptr)
        // addUniform("bool", "useTexture", 0);
        addUniform("useTexture", false);
    else {
        // addUniform("bool", "useTexture", 1);
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
