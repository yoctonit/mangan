#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "Shader.h"

namespace Mn {

    Shader::Shader() = default;

    Shader::Shader(GLuint id) {
        m_id = id;
    }

    GLuint Shader::id() const {
        return m_id;
    }

    Shader Shader::FromFiles(const std::string &vertexShaderFile, const std::string &fragmentShaderFile) {
        std::string vertexShaderSource = LoadFile(vertexShaderFile);
        GLuint vertexShaderId = Compile(vertexShaderSource, GL_VERTEX_SHADER);

        std::string fragmentShaderSource = LoadFile(fragmentShaderFile);
        GLuint fragmentShaderId = Compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

        return Shader{Link(vertexShaderId, fragmentShaderId)};
    }

    GLuint Shader::Compile(const std::string &shaderSource, GLenum shaderType) {
        GLuint shaderId = glCreateShader(shaderType);

        // Send the shader source code to GL.
        // Note that std::string's .c_str is NULL character terminated.
        auto source = (const GLchar *) shaderSource.c_str();
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        GLint isCompiled = 0;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shaderId anymore.
            glDeleteShader(shaderId);
            shaderId = 0;

            // Convert the infoLog to string
            std::ostringstream errorMessage;
            for (GLchar c: infoLog) {
                errorMessage << c;
            }

            std::cerr << "Compile shader error: " << errorMessage.str() << "\n";
        }
        return shaderId;
    }

    GLuint Shader::Link(GLuint vertexShaderId, GLuint fragmentShaderId) {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Create empty program object and store reference to it.
        GLuint programId = glCreateProgram();

        // Attach previously compiled shader programs
        glAttachShader(programId, vertexShaderId);
        glAttachShader(programId, fragmentShaderId);

        // Link vertex shader to fragment shader
        glLinkProgram(programId);

        // Queries whether program link was successful
        GLint linkSuccess;
        glGetProgramiv(programId, GL_LINK_STATUS, &linkSuccess);

        if (linkSuccess == GL_FALSE) {
            GLint infoLogLength = 0;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

            // The infoLogLength includes the NULL character
            std::vector<GLchar> infoLog(infoLogLength);
            glGetProgramInfoLog(programId, infoLogLength, &infoLogLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(programId);
            programId = 0;
            // Don't leak shaders either.
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);

            // Convert the infoLog to string
            std::ostringstream errorMessage;
            for (GLchar c: infoLog) {
                errorMessage << c;
            }

            std::cerr << "Link shader error: " << errorMessage.str() << "\n";
            return programId;
            // Failed linking, raise exception
            // throw std::runtime_error("Shader link error: " + errorMessage.str());
        }

        // Always detach shaders after a successful link.
        glDetachShader(programId, vertexShaderId);
        glDetachShader(programId, fragmentShaderId);

        // linking was successful; return program reference value
        return programId;
    }

    /*
     * Read contents of the file as string
     * @param [in] fileName - Path to the file
     * @param [out] - On successful read file contents, on failed read empty string;
     */
    std::string Shader::LoadFile(const std::string &fileName) {
        std::ifstream fileStream(fileName, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "Could not open " << fileName << "\n";
            return ""; // throw exception?
        }

        std::stringstream str;
        str << fileStream.rdbuf();

        fileStream.close();
        return str.str();
    }

}
