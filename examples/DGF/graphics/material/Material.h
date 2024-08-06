#ifndef DGF_GRAPHICS_MATERIAL_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_MATERIAL_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <glm/mat4x4.hpp>
#include "../core/Uniform.h"
#include "../core/RenderSettings.h"

class Material {
public:
    Material(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);

    void addUniform(const std::string &variableName, bool data);

    void addUniform(const std::string &variableName, float data);

    void addUniform(const std::string &variableName, glm::vec2 data);

    void addUniform(const std::string &variableName, glm::vec3 data);

    void addUniform(const std::string &variableName, glm::mat4x4 data);

    void addUniform(const std::string &variableName, unsigned int textureRef, int textureUnit);

    [[nodiscard]] GLuint programRef() const;

    [[nodiscard]] GLint drawStyle() const;

    [[nodiscard]] std::map<std::string, Uniform> &uniforms();

    [[nodiscard]] RenderSettings &renderSettings();

    [[nodiscard]] virtual bool usesLight() const;

    [[nodiscard]] bool containsUniform(const std::string &name) const;

protected:
    GLuint m_programRef{};

    GLint m_drawStyle{};

    // Store Uniform objects, indexed by name of associated variable in shader.
    std::map<std::string, Uniform> m_uniforms;

    // Store OpenGL render settings
    RenderSettings m_renderSettings{};
};

#endif //DGF_GRAPHICS_MATERIAL_MATERIAL_H
