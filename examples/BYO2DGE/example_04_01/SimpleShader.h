//
// Created by Ivan on 27-Jan-23.
//

#ifndef OPENGL_EXAMPLES_SIMPLE_SHADER_H
#define OPENGL_EXAMPLES_SIMPLE_SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Shader.h"
#include "../VBO.h"

class SimpleShader {
public:
    SimpleShader(const std::string &vs_file, const std::string &fs_file) {
        mCompiledShader = Mn::Shader::CreateFromFiles(vs_file, fs_file);
        glGenVertexArrays(1, &VAO);
        mVertexPositionRef = glGetAttribLocation(mCompiledShader, "aVertexPosition");
        mPixelColorRef = glGetUniformLocation(mCompiledShader, "uPixelColor");
        mModelMatrixRef = glGetUniformLocation(mCompiledShader, "uModelXformMatrix");
        mCameraMatrixRef = glGetUniformLocation(mCompiledShader, "uCameraXformMatrix");
    }

    void activate(
            const std::shared_ptr<Mn::VBO> &vb,
            glm::vec4 pixelColor,
            glm::mat4 trsMatrix,
            glm::mat4 cameraMatrix
    ) const {
        glUseProgram(mCompiledShader);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, vb->get());
        glVertexAttribPointer(mVertexPositionRef, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(mVertexPositionRef);

        // load uniforms
        glUniform4fv(mPixelColorRef, 1, glm::value_ptr(pixelColor));
        glUniformMatrix4fv(mModelMatrixRef, 1, GL_FALSE, glm::value_ptr(trsMatrix));
        glUniformMatrix4fv(mCameraMatrixRef, 1, GL_FALSE, glm::value_ptr(cameraMatrix));
    }

private:
    unsigned int mCompiledShader{};
    int mVertexPositionRef{};
    int mPixelColorRef{};
    int mModelMatrixRef{};
    int mCameraMatrixRef{};
    unsigned int VAO{};
};

#endif //OPENGL_EXAMPLES_SIMPLE_SHADER_H
