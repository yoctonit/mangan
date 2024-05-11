#ifndef BYO2DGE_SIMPLE_SHADER_H
#define BYO2DGE_SIMPLE_SHADER_H

#include "core/Buffer.h"
#include "core/Shader.h"
#include "core/Vao.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class SimpleShader {
public:
    SimpleShader();

    [[nodiscard]] Mn::ShaderProgram Shader() const;

    void Activate(glm::vec4 pixelColor) const;

    [[nodiscard]] GLuint VertexPositionRef() const;

    [[nodiscard]] GLint PixelColorRef() const;

private:
    Mn::ShaderProgram mCompiledShader{};

    GLuint mVertexPositionRef{};
    GLint mPixelColorRef{};
};

#endif //BYO2DGE_SIMPLE_SHADER_H
