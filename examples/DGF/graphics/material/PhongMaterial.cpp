#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(std::shared_ptr<Texture> texture)
        : Material(
        "shader/PhongMaterial.vert",
        "shader/PhongMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    // addUniform("Light", "light0", null );
    // addUniform("Light", "light1", null );
    // addUniform("Light", "light2", null );
    // addUniform("Light", "light3", null );

    addUniform("viewPosition", glm::vec3(0.0f, 0.0f, 0.0f));
    addUniform("specularStrength", 1.0f);
    addUniform("shininess", 32.0f);

    /*
    addUniform("bool", "useTexture", 0);

    if (texture != null)
        addTextureData(texture);

    addUniform("bool", "useBumpTexture", 0);

    addUniform("bool", "useShadow", 0);
     */

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
