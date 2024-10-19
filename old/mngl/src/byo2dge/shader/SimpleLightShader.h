#ifndef OPENGL_EXAMPLES_SIMPLE_LIGHT_SHADER_H
#define OPENGL_EXAMPLES_SIMPLE_LIGHT_SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../SquareGeometryBuffer.h"
#include "ShaderInterface.h"
#include "../../Shader.h"

class SimpleLightShader : public ShaderInterface {
public:
    SimpleLightShader(const std::string &vs_file, const std::string &fs_file) {
        mCompiledShader = Mn::Shader::CreateFromFiles(vs_file, fs_file);
        glGenVertexArrays(1, &VAO);
        mVertexPositionRef = glGetAttribLocation(mCompiledShader, "aVertexPosition");
        mPixelColorRef = glGetUniformLocation(mCompiledShader, "uPixelColor");
        mModelMatrixRef = glGetUniformLocation(mCompiledShader, "uModelXformMatrix");
        mCameraMatrixRef = glGetUniformLocation(mCompiledShader, "uCameraXformMatrix");
        mGlobalAmbientColorRef = glGetUniformLocation(mCompiledShader, "uGlobalAmbientColor");
        mGlobalAmbientIntensityRef = glGetUniformLocation(mCompiledShader, "uGlobalAmbientIntensity");
    }

    void activate(
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            glm::vec4 pixelColor,
            glm::mat4 trsMatrix,
            glm::mat4 cameraMatrix,
            glm::vec4 ambientColor,
            float ambientIntensity
    ) const override {
        glUseProgram(mCompiledShader);
        glBindVertexArray(VAO);

        sq->getVertexBuffer()->activate();
        glVertexAttribPointer(mVertexPositionRef, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(mVertexPositionRef);

        glUniform4fv(mPixelColorRef, 1, glm::value_ptr(pixelColor));
        glUniformMatrix4fv(mModelMatrixRef, 1, GL_FALSE, glm::value_ptr(trsMatrix));
        glUniformMatrix4fv(mCameraMatrixRef, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
        glUniform4fv(mGlobalAmbientColorRef, 1, glm::value_ptr(ambientColor));
        glUniform1f(mGlobalAmbientIntensityRef, ambientIntensity);
    }

protected:
    unsigned int mCompiledShader{};
    int mVertexPositionRef{};
    int mPixelColorRef{};
    int mModelMatrixRef{};
    int mCameraMatrixRef{};
    int mGlobalAmbientColorRef{};
    int mGlobalAmbientIntensityRef{};
    unsigned int VAO{};
};

#endif //OPENGL_EXAMPLES_SIMPLE_LIGHT_SHADER_H
