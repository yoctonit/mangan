#ifndef DGF_GRAPHICS_MATERIAL_MATERIAL_H
#define DGF_GRAPHICS_MATERIAL_MATERIAL_H

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <glm/mat4x4.hpp>
#include "../core/Shader.h"
#include "../core/Uniform.h"
#include "../core/RenderSetting.h"

class Material {
public:

    Material(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);

    // void addUniform(Uniform::Type dataType, const std::string &variableName);

    void addUniform(const std::string &variableName, bool data);

    void addUniform(const std::string &variableName, glm::vec3 data);

    void addUniform(const std::string &variableName, glm::mat4x4 data);

    // initialize all uniform variable references
    // void locateUniforms();

    void addRenderSetting(const std::shared_ptr<RenderSetting> &setting);

protected:
    GLuint m_programRef{};

    int m_drawStyle{};

    // Store Uniform objects, indexed by name of associated variable in shader.
    std::map<std::string, Uniform> m_uniforms;

    // Store OpenGL render settings, indexed by variable name.
    // Additional settings added by extending classes.
    std::vector<std::shared_ptr<RenderSetting>> m_renderSettings;

};

#endif //DGF_GRAPHICS_MATERIAL_MATERIAL_H
