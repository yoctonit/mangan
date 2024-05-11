#ifndef INCLUDED_MN_CORE_SHADER_H
#define INCLUDED_MN_CORE_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace Mn {

    class ShaderProgram {
    private:
        GLuint id_{};

    public:
        ShaderProgram();

        ShaderProgram(const std::string &vs_source, const std::string &fs_source);

        static ShaderProgram CreateFromFiles(const std::string &vs_file, const std::string &fs_file);

        [[nodiscard]] GLuint Id() const;

        void Use() const;

        void Release() const;

        [[nodiscard]] GLuint AttributeLocation(const std::string &name) const;

        [[nodiscard]] GLint UniformLocation(const std::string &name) const;

        void AttachAttribute(const std::string &attribute, GLint size, GLsizei stride, const void *pointer) const;

        void Uniform(const std::string &name, float v1, float v2, float v3) const;

        void Uniform(const std::string &name, float v1, float v2, float v3, float v4) const;

        void Uniform(const std::string &name, glm::vec4 v) const;

        void Uniform(const std::string &name, glm::mat4 matrix) const;

        void Uniform(const std::string &name, int v) const;

        static void Uniform(GLint location, float v1, float v2, float v3);

        static void Uniform(GLint location, float v1, float v2, float v3, float v4);

        static void Uniform(GLint location, glm::vec4 v);

        static void Uniform(GLint location, glm::mat4 matrix);

        static void Uniform(GLint location, int v);

    private:
        static std::string Load(const std::string &file_path);

        static GLuint Compile(const std::string &shader_source, GLenum shader_type);

        static GLuint Link(GLuint vs_id, GLuint fs_id);
    };

}

#endif // INCLUDED_MN_CORE_SHADER_H
