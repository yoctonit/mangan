#include "LambertMaterial.h"

LambertMaterial::LambertMaterial(std::shared_ptr<Texture> texture)
        : Material(
        "shader/LambertMaterial.vert",
        "shader/LambertMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    // addUniform("Light", "light0", null );
    // addUniform("Light", "light1", null );
    // addUniform("Light", "light2", null );
    // addUniform("Light", "light3", null );

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
