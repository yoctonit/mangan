#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(const Texture &texture)
        : Material(
        "shader/TextureMaterial.vert",
        "shader/TextureMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    addUniform("tex", texture.textureRef(), 1);
    addUniform("repeatUV", glm::vec2(1.0f, 1.0f));
    addUniform("offsetUV", glm::vec2(0.0f, 0.0f));

    m_renderSettings.Activate(RenderSettings::Type::DoubleSide);
    m_renderSettings.set(RenderSettings::Type::DoubleSide, true);

    m_renderSettings.Activate(RenderSettings::Type::Wireframe);
    m_renderSettings.set(RenderSettings::Type::Wireframe, false);

    m_renderSettings.Activate(RenderSettings::Type::LineWidth);
}
