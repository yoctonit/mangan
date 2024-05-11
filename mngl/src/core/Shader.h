#ifndef INCLUDED_MN_SHADER_H
#define INCLUDED_MN_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Mn {

    class ShaderProgram {
    private:
        GLuint _id{};

    public:
        ShaderProgram(const std::string &vs_file, const std::string &fs_file) {
            _id = create_from_files(vs_file, fs_file);
            std::cout << "Created shader program with id " << _id << "\n";
        }

        ~ShaderProgram() {
            glDeleteProgram(_id);
            std::cout << "Deleted shader program with id " << _id << "\n";
        }

        [[nodiscard]] GLuint id() const { return _id; }

        void use() const { glUseProgram(_id); }

        [[nodiscard]] GLint location(const std::string &name) const {
            GLint location = glGetAttribLocation(_id, name.c_str());
            if (location == -1) {
                location = glGetUniformLocation(_id, name.c_str());
            }

            if (location == -1) {
                std::cerr << "No attribute/uniform " << name << " in shader program " << _id << "\n";
            }
            return location;
        }

        void uniform(const std::string &name, float v1, float v2, float v3) const {
            glUniform3f(location(name), v1, v2, v3);
        }

        void uniform(const std::string &name, float v1, float v2, float v3, float v4) const {
            glUniform4f(location(name), v1, v2, v3, v4);
        }

        void uniform(const std::string &name, glm::mat4 matrix) const {
            glUniformMatrix4fv(location(name), 1, GL_FALSE, glm::value_ptr(matrix));
        }

        void uniform(const std::string &name, int v) const {
            glUniform1i(location(name), v);
        }

        static void uniform(GLint location, float v1, float v2, float v3) {
            glUniform3f(location, v1, v2, v3);
        }

        static void uniform(GLint location, float v1, float v2, float v3, float v4) {
            glUniform4f(location, v1, v2, v3, v4);
        }

        static void uniform(GLint location, glm::mat4 matrix) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        }

        static void uniform(GLint location, int v) {
            glUniform1i(location, v);
        }

    private:
        static std::string Load(const std::string &file_path) {
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

        static GLuint create_from_files(
                const std::string &vertex_shader_file_name,
                const std::string &fragment_shader_file_name) {
            std::string vertex_shader_source = Load(vertex_shader_file_name);
            GLuint vertex_shader_id = Compile(vertex_shader_source, GL_VERTEX_SHADER);

            std::string fragment_shader_source = Load(fragment_shader_file_name);
            GLuint fragment_shader_id = Compile(fragment_shader_source, GL_FRAGMENT_SHADER);

            return Link(vertex_shader_id, fragment_shader_id);
        }

        static GLuint Compile(const std::string &shader_source, GLenum shader_type) {
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
                glGetShaderInfoLog(shader_id, max_length, &max_length, &info_log[0]);

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

        static GLuint Link(GLuint vertex_shader_id, GLuint fragment_shader_id) {
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
                glGetProgramInfoLog(program_id, info_log_length, &info_log_length, &info_log[0]);

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
    };

}

#endif // INCLUDED_MN_SHADER_H
