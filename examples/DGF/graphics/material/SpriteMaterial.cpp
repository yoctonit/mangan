#include "SpriteMaterial.h"

SpriteMaterial::SpriteMaterial(const Texture &texture)
        : Material(
        "shader/SpriteMaterial.vert",
        "shader/SpriteMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));
    addUniform("tex", texture.textureRef(), 1);
    addUniform("billboard", false);
    addUniform("tileNumber", -1.0f);
    addUniform("tileCount", glm::vec2(1.0f, 1.0f));

    m_renderSettings.Activate(RenderSettings::Type::DoubleSide);
    m_renderSettings.set(RenderSettings::Type::DoubleSide, true);
}
