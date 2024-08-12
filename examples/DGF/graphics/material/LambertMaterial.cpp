#include "LambertMaterial.h"

LambertMaterial::LambertMaterial(const std::shared_ptr<Texture> &texture)
        : Material(
        "shader/LambertMaterial.vert",
        "shader/LambertMaterial.frag"
) {
    addUniform("baseColor", glm::vec3(1.0f, 1.0f, 1.0f));

    addUniform("useTexture", false);

    if (texture != nullptr) {
        addTextureData(texture);
    }

    addUniform("useBumpTexture", false);

    addUniform("useShadow", false);

    m_renderSettings.Activate(RenderSettings::Type::DoubleSide);
    m_renderSettings.set(RenderSettings::Type::DoubleSide, true);

    m_renderSettings.Activate(RenderSettings::Type::Wireframe);
    m_renderSettings.set(RenderSettings::Type::Wireframe, false);

    m_renderSettings.Activate(RenderSettings::Type::LineWidth);
}

bool LambertMaterial::usesLight() const {
    return true;
}

void LambertMaterial::addTextureData(const std::shared_ptr<Texture> &texture) {
    m_uniforms["useTexture"].data().m_dataBool = true;
    addUniform("tex", texture->textureRef(), 1);
}

void LambertMaterial::addBumpData(const std::shared_ptr<Texture> &bumpTexture, float bumpStrength) {
    m_uniforms["useBumpTexture"].data().m_dataBool = true;
    addUniform("bumpTexture", bumpTexture->textureRef(), 2);
    addUniform("bumpStrength", bumpStrength);
}

void LambertMaterial::enableShadow() {
    m_uniforms["useShadow"].data().m_dataBool = true;
    // addUniform("Shadow", "shadow0", null);
    // variableRefMap.put("lightDirection", glGetUniformLocation(programRef, variableName + ".lightDirection") );
    m_uniforms["shadow0.lightDirection"] = Uniform(m_programRef, "shadow0.lightDirection", glm::vec3(0.0, 0.0, 0.0));

    // variableRefMap.put("projectionMatrix", glGetUniformLocation(programRef, variableName + ".projectionMatrix") );
    m_uniforms["shadow0.projectionMatrix"] = Uniform(m_programRef, "shadow0.projectionMatrix", glm::mat4x4{});

    // variableRefMap.put("viewMatrix", glGetUniformLocation(programRef, variableName + ".viewMatrix") );
    m_uniforms["shadow0.viewMatrix"] = Uniform(m_programRef, "shadow0.viewMatrix", glm::mat4x4{});

    // variableRefMap.put("depthTexture", glGetUniformLocation(programRef, variableName + ".depthTexture") );
    m_uniforms["shadow0.depthTexture"] = Uniform(m_programRef, "shadow0.depthTexture", 0, 0);

    // variableRefMap.put("strength", glGetUniformLocation(programRef, variableName + ".strength") );
    m_uniforms["shadow0.strength"] = Uniform(m_programRef, "shadow0.strength", 0.0f);

    // variableRefMap.put("bias", glGetUniformLocation(programRef,variableName + ".bias") );
    m_uniforms["shadow0.bias"] = Uniform(m_programRef, "shadow0.bias", 0.0f);
}

void LambertMaterial::setShadowUniform(const std::string &name, const std::shared_ptr<Shadow> &shadowObject) {
    m_uniforms["shadow0.lightDirection"].data().m_dataVec3 = shadowObject->lightSource->direction();
    m_uniforms["shadow0.projectionMatrix"].data().m_dataMat4x4 = shadowObject->camera->projectionMatrix();
    m_uniforms["shadow0.viewMatrix"].data().m_dataMat4x4 = shadowObject->camera->viewMatrix();
    m_uniforms["shadow0.depthTexture"].data().m_dataVec2 = glm::vec2(shadowObject->renderTarget->texture->textureRef(),
                                                                     15);
    m_uniforms["shadow0.strength"].data().m_dataFloat = shadowObject->strength;
    m_uniforms["shadow0.bias"].data().m_dataFloat = shadowObject->bias;
}
