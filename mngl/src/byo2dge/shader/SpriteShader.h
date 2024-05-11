#ifndef OPENGL_EXAMPLES_SPRITE_SHADER_H
#define OPENGL_EXAMPLES_SPRITE_SHADER_H

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../SquareGeometryBuffer.h"
#include "ShaderInterface.h"
#include "../../Shader.h"

class SpriteShader : public ShaderInterface {
public:
    SpriteShader(const std::string &vs_file, const std::string &fs_file) {
        mCompiledShader = Mn::Shader::CreateFromFiles(vs_file, fs_file);
        glGenVertexArrays(1, &VAO);
        mVertexPositionRef = glGetAttribLocation(mCompiledShader, "aVertexPosition");
        mPixelColorRef = glGetUniformLocation(mCompiledShader, "uPixelColor");
        mModelMatrixRef = glGetUniformLocation(mCompiledShader, "uModelXformMatrix");
        mCameraMatrixRef = glGetUniformLocation(mCompiledShader, "uCameraXformMatrix");
        mTextureCoordinateRef = glGetAttribLocation(mCompiledShader, "aTextureCoordinate");
        mSamplerRef = glGetAttribLocation(mCompiledShader, "uSampler");

        std::vector<float> initTexCoord = {
                1.0f, 1.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
        };
        mTexCoordBuffer = std::make_shared<Mn::VBO>(initTexCoord, GL_DYNAMIC_DRAW);

    }

//    _getTexCoordBuffer() {
//        return this.mTexCoordBuffer;
//    }
//
    void setTextureCoordinate(const std::vector<float> &texCoord) override {
        mTexCoordBuffer->load(texCoord);
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

        mTexCoordBuffer->activate();
        glVertexAttribPointer(mTextureCoordinateRef, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(mTextureCoordinateRef);

        glUniform4fv(mPixelColorRef, 1, glm::value_ptr(pixelColor));
        glUniformMatrix4fv(mModelMatrixRef, 1, GL_FALSE, glm::value_ptr(trsMatrix));
        glUniformMatrix4fv(mCameraMatrixRef, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
        glUniform1i(mSamplerRef, 0);
    }

private:
    unsigned int mCompiledShader{};
    int mVertexPositionRef{};
    int mPixelColorRef{};
    int mModelMatrixRef{};
    int mCameraMatrixRef{};
    unsigned int VAO{};
    int mTextureCoordinateRef{};
    int mSamplerRef{};
    std::shared_ptr<Mn::VBO> mTexCoordBuffer{};
};

#endif //OPENGL_EXAMPLES_SPRITE_SHADER_H
