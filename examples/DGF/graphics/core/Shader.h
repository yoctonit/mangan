#ifndef DGF_GRAPHICS_CORE_SHADER_H
#define DGF_GRAPHICS_CORE_SHADER_H

#include "glad/glad.h"
#include <string>

class Shader {
public:
    Shader();

    explicit Shader(GLuint id);

    [[nodiscard]] GLuint id() const;

    static Shader FromFiles(const std::string &vertexShaderFile, const std::string &fragmentShaderFile);

private:
    GLuint m_id{};

    static std::string LoadFile(const std::string &fileName);

    static GLuint Compile(const std::string &shaderSource, GLenum shaderType);

    static GLuint Link(GLuint vertexShaderId, GLuint fragmentShaderId);

};

#endif //DGF_GRAPHICS_CORE_SHADER_H
