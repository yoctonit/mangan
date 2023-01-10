//
// Created by ivan on 26.9.2021..
//
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "openGLUtils.h"

GLuint OpenGLUtils::initializeShader(const std::string &shaderCode, GLenum shaderType) {
    // create empty shader object and return reference value
    GLuint shaderRef = glCreateShader(shaderType);

    // stores the source code in the shader
    auto source = reinterpret_cast<const GLchar *>(shaderCode.c_str());
    glShaderSource(shaderRef, 1, &source, nullptr);

    // compiles source code previously stored in the shader object
    glCompileShader(shaderRef);

    // queries whether shader compile was successful
    GLint compileSuccess = 0;
    glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(shaderRef, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(shaderRef, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(shaderRef);

        // Convert the infoLog to string
        std::ostringstream errorMessage;
        for (GLchar c: infoLog) errorMessage << c;

        // Failed compilation, raise exception
        std::string errorHeader = GL_VERTEX_SHADER == shaderType ? "Vertex" : "Fragment";
        errorHeader += " shader compile error: ";
        std::string error = errorHeader + errorMessage.str();
        throw std::runtime_error(error);
    }

    // compilation was successful; return shader reference value
    return shaderRef;
}

GLuint OpenGLUtils::initializeProgram(const std::string &vertexShaderCode, const std::string &fragmentShaderCode) {
    GLuint vertexShaderRef = OpenGLUtils::initializeShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShaderRef = OpenGLUtils::initializeShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Create empty program object and store reference to it
    GLuint programRef = glCreateProgram();

    // Attach previously compiled shader programs
    glAttachShader(programRef, vertexShaderRef);
    glAttachShader(programRef, fragmentShaderRef);

    // Link vertex shader to fragment shader
    glLinkProgram(programRef);

    // Queries whether program link was successful
    GLint linkSuccess;
    glGetProgramiv(programRef, GL_LINK_STATUS, &linkSuccess);

    if (linkSuccess == GL_FALSE) {
        GLint infoLogLength = 0;
        glGetProgramiv(programRef, GL_INFO_LOG_LENGTH, &infoLogLength);

        // The infoLogLength includes the NULL character
        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(programRef, infoLogLength, &infoLogLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(programRef);
        // Don't leak shaders either.
        glDeleteShader(vertexShaderRef);
        glDeleteShader(fragmentShaderRef);

        // Convert the infoLog to string
        std::ostringstream errorMessage;
        for (GLchar c: infoLog) {
            errorMessage << c;
        }

        // Failed linking, raise exception
        throw std::runtime_error("Shader link error: " + errorMessage.str());
    }

    // Always detach shaders after a successful link.
    glDetachShader(programRef, vertexShaderRef);
    glDetachShader(programRef, fragmentShaderRef);

    // linking was successful; return program reference value
    return programRef;
}

void OpenGLUtils::printSystemInfo() {
    std::cout << " Vendor: " << glGetString(GL_VENDOR) << '\n';
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
    std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << '\n';
    std::cout << " GLSL version supported: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
}
