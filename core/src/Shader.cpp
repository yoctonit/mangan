#include "core/Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Mn {
    ShaderProgram::ShaderProgram() = default;

    ShaderProgram::ShaderProgram(const std::string &vs_source, const std::string &fs_source) {
        GLuint vertex_shader_id = Compile(vs_source, GL_VERTEX_SHADER);
        GLuint fragment_shader_id = Compile(fs_source, GL_FRAGMENT_SHADER);
        id_ = Link(vertex_shader_id, fragment_shader_id);
        std::cout << "Created shader program with id " << id_ << "\n";
    }

    ShaderProgram ShaderProgram::CreateFromFiles(const std::string &vs_file, const std::string &fs_file) {
        std::cout << "Creating shader program from files " << vs_file << " and " << fs_file << "\n";
        std::string vertex_shader_source = Load(vs_file);
        std::string fragment_shader_source = Load(fs_file);
        return {vertex_shader_source, fragment_shader_source};
    }

    void ShaderProgram::Release() const {
        glDeleteProgram(id_);
        std::cout << "Released shader program with id " << id_ << "\n";
    }

    GLuint ShaderProgram::Id() const {
        return id_;
    }

    void ShaderProgram::Use() const {
        glUseProgram(id_);
    }

    GLuint ShaderProgram::AttributeLocation(const std::string &name) const {
        GLuint location = glGetAttribLocation(id_, name.c_str());
        if (location == -1) {
            std::cerr << "No attribute " << name << " in shader program " << id_ << "\n";
        }
        return location;
    }

    GLint ShaderProgram::UniformLocation(const std::string &name) const {
        GLint location = glGetUniformLocation(id_, name.c_str());
        if (location == -1) {
            std::cerr << "No uniform " << name << " in shader program " << id_ << "\n";
        }
        return location;
    }

    void ShaderProgram::AttachAttribute(
            const std::string &attribute,
            GLint size,
            GLsizei stride,
            const void *pointer
    ) const {
        GLuint location = glGetAttribLocation(id_, attribute.c_str());
        if (location == -1) {
            std::cerr << "No attribute " << attribute << " in shader program " << id_ << "\n";
        }
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride * sizeof(GLfloat)),
                              pointer);
    }

    void ShaderProgram::Uniform(const std::string &name, float v1, float v2, float v3) const {
        glUniform3f(UniformLocation(name), v1, v2, v3);
    }

    void ShaderProgram::Uniform(const std::string &name, float v1, float v2, float v3, float v4) const {
        glUniform4f(UniformLocation(name), v1, v2, v3, v4);
    }

    void ShaderProgram::Uniform(const std::string &name, glm::vec4 v) const {
        glUniform4f(UniformLocation(name), v[0], v[1], v[2], v[3]);
    }

    void ShaderProgram::Uniform(const std::string &name, glm::mat4 matrix) const {
        glUniformMatrix4fv(UniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::Uniform(const std::string &name, int v) const {
        glUniform1i(UniformLocation(name), v);
    }

    void ShaderProgram::Uniform(GLint location, float v1, float v2, float v3) {
        glUniform3f(location, v1, v2, v3);
    }

    void ShaderProgram::Uniform(GLint location, float v1, float v2, float v3, float v4) {
        glUniform4f(location, v1, v2, v3, v4);
    }

    void ShaderProgram::Uniform(GLint location, glm::vec4 v) {
        glUniform4f(location, v[0], v[1], v[2], v[3]);
    }

    void ShaderProgram::Uniform(GLint location, glm::mat4 matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void ShaderProgram::Uniform(GLint location, int v) {
        glUniform1i(location, v);
    }

    std::string ShaderProgram::Load(const std::string &file_path) {
        std::ifstream file_stream(file_path, std::ios::in);
        if (!file_stream.is_open()) {
            std::cerr << "Could not open " << file_path << "\n";
            return ""; // throw exception?
        }

        std::stringstream str;
        str << file_stream.rdbuf();
        file_stream.close();

        return str.str();
    }

    GLuint ShaderProgram::Compile(const std::string &shader_source, GLenum shader_type) {
        GLuint shader_id = glCreateShader(shader_type);

        auto *source = (const GLchar *) shader_source.c_str();
        glShaderSource(shader_id, 1, &source, nullptr);
        glCompileShader(shader_id);

        GLint is_compiled = 0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
        if (is_compiled == GL_FALSE) {
            GLint max_length = 0;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

            // The max_length includes the NULL character
            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(shader_id, max_length, &max_length, info_log.data());
//            glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

            // We don't need the shader_id anymore.
            glDeleteShader(shader_id);
            shader_id = 0;

            // Convert the info_log to string
            std::ostringstream error_message;
            for (GLchar c: info_log) {
                error_message << c;
            }
            std::cerr << "Compile: " << error_message.str() << "\n";
        }
        return shader_id;
    }

    GLuint ShaderProgram::Link(GLuint vertex_shader_id, GLuint fragment_shader_id) {
        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a shader program.
        GLuint program_id = glCreateProgram();
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        glLinkProgram(program_id);

        GLint is_linked = 0;
        glGetProgramiv(program_id, GL_LINK_STATUS, (int *) &is_linked);
        if (is_linked == GL_FALSE) {
            GLint info_log_length = 0;
            glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

            // The info_log_length includes the NULL character
            std::vector<GLchar> info_log(info_log_length);
//            glGetProgramInfoLog(program_id, info_log_length, &info_log_length, &info_log[0]);
            glGetProgramInfoLog(program_id, info_log_length, &info_log_length, info_log.data());

            // We don't need the program anymore.
            glDeleteProgram(program_id);
            program_id = 0;
            // Don't leak shaders either.
            glDeleteShader(vertex_shader_id);
            glDeleteShader(fragment_shader_id);

            // Convert the info_log to string
            std::ostringstream error_message;
            for (GLchar c: info_log) {
                error_message << c;
            }
            std::cerr << "Link: " << error_message.str() << "\n";
            return program_id;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program_id, vertex_shader_id);
        glDetachShader(program_id, fragment_shader_id);

        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);

        return program_id;
    }

}
