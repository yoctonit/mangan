#include "Material.h"
#include "../core/Shader.h"

Material::Material(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName) {
    m_programRef = Shader::FromFiles(vertexShaderFileName, fragmentShaderFileName).id();

    m_drawStyle = GL_TRIANGLES;

    // Each shader typically contains these uniforms;
    // values will be set during render process from Mesh/Camera.
    // Additional uniforms added by extending classes.
    addUniform("modelMatrix", glm::mat4x4{1.0f});
    addUniform("viewMatrix", glm::mat4x4{1.0f});
    addUniform("projectionMatrix", glm::mat4x4{1.0f});
}

void Material::addUniform(const std::string &variableName, bool data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, int data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, float data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, glm::vec2 data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, glm::vec3 data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, glm::mat4x4 data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, unsigned int textureRef, int textureUnit) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, textureRef, textureUnit);
}

GLuint Material::programRef() const {
    return m_programRef;
}

GLint Material::drawStyle() const {
    return m_drawStyle;
}

std::map<std::string, Uniform> &Material::uniforms() {
    return m_uniforms;
}

RenderSettings &Material::renderSettings() {
    return m_renderSettings;
}

bool Material::usesLight() const {
    return false;
}

bool Material::containsUniform(const std::string &name) const {
    return m_uniforms.find(name) != m_uniforms.end();
}

void Material::setShadowUniform(const std::string &name, const std::shared_ptr<Shadow> &shadowObject) {
}
