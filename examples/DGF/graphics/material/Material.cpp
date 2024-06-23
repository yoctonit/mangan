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

void Material::addUniform(const std::string &variableName, float data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, glm::vec3 data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
}

void Material::addUniform(const std::string &variableName, glm::mat4x4 data) {
    m_uniforms[variableName] = Uniform(m_programRef, variableName, data);
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
