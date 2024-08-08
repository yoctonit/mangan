#include "PhongMaterial.h"

PhongMaterial::PhongMaterial(const std::shared_ptr<Texture>& texture)
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

bool PhongMaterial::usesLight() const {
    return true;
}

void PhongMaterial::addBumpData(const std::shared_ptr<Texture> &bumpTexture, float bumpStrength) {
    m_uniforms["useBumpTexture"].data().m_dataBool = true;
    addUniform("bumpTexture", bumpTexture->textureRef(), 2);
    addUniform("bumpStrength", bumpStrength);
}
