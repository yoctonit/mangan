#ifndef BYO2DGE_SIMPLE_SHADER_H
#define BYO2DGE_SIMPLE_SHADER_H

#include "core/Shader.h"

class SimpleShader {
public:
    SimpleShader();

    void Create();

    void Release();

    [[nodiscard]] Mn::ShaderProgram Shader() const;

    [[nodiscard]] GLuint VertexPositionRef() const;

    [[nodiscard]] GLint PixelColorRef() const;

    [[nodiscard]] GLint ModelMatrixRef() const;

    [[nodiscard]] GLint CameraMatrixRef() const;

    void Activate(glm::vec4 pixelColor, glm::mat4 trsMatrix, glm::mat4 cameraMatrix) const;

private:
    Mn::ShaderProgram mCompiledShader{};

    GLuint mVertexPositionRef{};
    GLint mPixelColorRef{};
    GLint mModelMatrixRef{};
    GLint mCameraMatrixRef{};
};

#endif //BYO2DGE_SIMPLE_SHADER_H
