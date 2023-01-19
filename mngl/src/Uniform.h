//
// Created by ivan on 10.1.2023..
//

#ifndef INCLUDED_MN_UNIFORM_H
#define INCLUDED_MN_UNIFORM_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Mn::Shader {

    class Uniform {
    public:
        Uniform() : _location{-1} {};

        Uniform(GLuint shader, const std::string &name)
            : _location{ -1 } {
            init(shader, name);
        }

        void init(GLuint shader, const std::string &name) {
            _location = glGetUniformLocation(shader, name.c_str());
            if (_location == -1) {
                std::cout << "Could not find uniform: " << name << "\n";
            }
        }

        [[nodiscard]] GLint location() const {
            return _location;
        }

        void upload(float value) const {
            glUniform1f(_location, value);
        }

        void upload(glm::vec2 value) const {
            glUniform2f(_location, value.x, value.y);
        }

        void upload(glm::vec3 value) const {
            glUniform3f(_location, value.x, value.y, value.z);
        }

        void upload(glm::mat4 value) const {
            glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(value));
        }

        void upload(bool value) const {
            glUniform1i(_location, value ? 1 : 0);
        }

        void upload(unsigned int textureObjectRef, int textureUnitRef) const {
//            Vector v = (Vector)data;
//            int textureObjectRef = (int)v.values[0];
//            int textureUnitRef = (int)v.values[1];
            // activate texture unit
            glActiveTexture(GL_TEXTURE0 + textureUnitRef);
            // associate texture object reference
            // to currently active texture unit
            glBindTexture(GL_TEXTURE_2D, textureObjectRef);
            // upload texture unit number (0...15)
            // to uniform variable in shader
            glUniform1i(_location, textureUnitRef);
        }

    protected:
        GLint _location;
    };

    void UploadUniform(const Uniform &uniform, float value) {
        glUniform1f(uniform.location(), value);
    }

    void UploadUniform(const Uniform &uniform, glm::vec3 value) {
        glUniform3f(uniform.location(), value.x, value.y, value.z);
    }

    void UploadUniform(const Uniform &uniform, glm::mat4 value) {
        glUniformMatrix4fv(uniform.location(), 1, GL_FALSE, glm::value_ptr(value));
    }

    void UploadUniform(const Uniform &uniform, bool value) {
        glUniform1i(uniform.location(), value ? 1 : 0);
    }

    void UploadUniformSampler(const Uniform &uniform, int textureObjectRef, int textureUnitRef) {
//            Vector v = (Vector)data;
//            int textureObjectRef = (int)v.values[0];
//            int textureUnitRef = (int)v.values[1];
        // activate texture unit
        glActiveTexture(GL_TEXTURE0 + textureUnitRef);
        // associate texture object reference
        // to currently active texture unit
        glBindTexture(GL_TEXTURE_2D, textureObjectRef);
        // upload texture unit number (0...15)
        // to uniform variable in shader
        glUniform1i(uniform.location(), textureUnitRef);
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
