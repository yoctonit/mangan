//
// Created by ivan on 26.9.2021..
//

#ifndef GLFRAMEWORK_OPENGLUTILS_H
#define GLFRAMEWORK_OPENGLUTILS_H

#include <glad/glad.h>
#include <string>

// static methods to load and compile OpenGL shaders and link to create programs
class OpenGLUtils {
public:
    static GLuint initializeShader(const std::string &shaderCode, GLenum shaderType);

    static GLuint initializeProgram(const std::string &vertexShaderCode, const std::string &fragmentShaderCode);

    static void printSystemInfo();
};

#endif //GLFRAMEWORK_OPENGLUTILS_H
