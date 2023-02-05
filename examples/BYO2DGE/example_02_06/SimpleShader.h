//
// Created by Ivan on 27-Jan-23.
//

#ifndef OPENGL_EXAMPLES_SIMPLE_SHADER_H
#define OPENGL_EXAMPLES_SIMPLE_SHADER_H

#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../Shader.h"
#include "../VBO.h"

class SimpleShader {
public:
    SimpleShader(const std::string &vs_file, const std::string &fs_file) {
        mCompiledShader = Mn::Shader::CreateFromFiles(vs_file, fs_file);
        glGenVertexArrays(1, &VAO);
        mVertexPositionRef = glGetAttribLocation(mCompiledShader, "aVertexPosition");
        mPixelColorRef = glGetUniformLocation(mCompiledShader, "uPixelColor");
    }

    void activate(const Mn::VBO &vb, glm::vec4 pixelColor) const {
        glUseProgram(mCompiledShader);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, vb.get());
        glVertexAttribPointer(mVertexPositionRef, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(mVertexPositionRef);

        // load uniforms
        glUniform4f(mPixelColorRef, pixelColor.r, pixelColor.g, pixelColor.b, pixelColor.a);
    }

private:
    unsigned int mCompiledShader{};
    int mVertexPositionRef{};
    int mPixelColorRef{};
    unsigned int VAO{};
};

#endif //OPENGL_EXAMPLES_SIMPLE_SHADER_H
