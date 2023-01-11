//
// Created by ivan on 10.1.2023..
//

#ifndef INCLUDED_MN_UNIFORM_H
#define INCLUDED_MN_UNIFORM_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Mn::Shader
{

    class Uniform
    {
    public:
        Uniform() : _location{-1} {};

        void init(GLuint shader, const std::string &name)
        {
            _location = glGetUniformLocation(shader, name.c_str());
        }

        [[nodiscard]] GLint location() const
        {
            return _location;
        }

    protected:
        GLint _location;
    };

    void UploadUniform(const Uniform &uniform, glm::vec3 value)
    {
        glUniform3f(uniform.location(), value.x, value.y, value.z);
    }

    void UploadUniform(const Uniform &uniform, glm::mat4 value)
    {
        glUniformMatrix4fv(uniform.location(), 1, GL_FALSE, glm::value_ptr(value));
    }

    void UploadUniform(const Uniform &uniform, bool value)
    {
        glUniform1i(uniform.location(), value ? 1 : 0);
    }

    // class UniformUploader
    // {
    // public:
    //     UniformUploader() : _uniform{} {};
    //     virtual void upload() const = 0;

    // protected:
    //     Uniform _uniform;
    // };

    // class UniformUploaderVector3 : public UniformUploader
    // {
    // public:
    //     UniformUploaderVector3(glm::vec3 value)
    //         : UniformUploader{}, _value{value}
    //     {
    //     }

    //     void upload() const
    //     {
    //         glUniform3f(_uniform.location(), _value.x, _value.y, _value.z);
    //     }

    // private:
    //     glm::vec3 _value;
    // };

    // class UniformUploaderMatrix4 : public UniformUploader
    // {
    // public:
    //     explicit UniformUploaderMatrix4(glm::mat4 value)
    //         : UniformUploader{}, _value{value}
    //     {
    //     }

    //     void upload() const
    //     {
    //         glUniformMatrix4fv(_uniform.location(), 1, GL_FALSE, glm::value_ptr(_value));
    //     }

    // private:
    //     glm::mat4 _value;
    // };

    // class UniformUploaderBool : public UniformUploader
    // {
    // public:
    //     UniformUploaderBool(bool value) : UniformUploader{}, _value{value}
    //     {
    //     }

    //     void upload() const
    //     {
    //         glUniform1i(_uniform.location(), _value ? 1 : 0);
    //     }

    // private:
    //     bool _value;
    // };

}

#endif // INCLUDED_MN_UNIFORM_H
