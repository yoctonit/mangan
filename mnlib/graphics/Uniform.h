#ifndef INCLUDED_MN_GRAPHICS_UNIFORM_H
#define INCLUDED_MN_GRAPHICS_UNIFORM_H

#include <glad/glad.h>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Mn {


//    struct Sampler {
//        unsigned int textureRef;
//        int textureUnit;
//    };


    class Uniform {
    public:
        enum class Type {
            Undefined, Bool, Int, Float, Vec2, Vec3, Vec4, Mat4x4 //, Sampler2D
        };

        Uniform();

        Uniform(int location, Type type);

        void Create(int location, Type type);

//    Uniform(GLuint programRef, const std::string &variableName);

//    Uniform(GLuint programRef, const std::string &variableName, bool data);

        Uniform &operator=(int data);

        Uniform &operator=(float data);

//    Uniform(GLuint programRef, const std::string &variableName, glm::vec2 data);

        Uniform &operator=(glm::vec3 data);

        Uniform &operator=(glm::vec4 data);
//    Uniform(GLuint programRef, const std::string &variableName, glm::mat4x4 data);

//    Uniform(GLuint programRef, const std::string &variableName, unsigned int textureRef, int textureUnit);

        void Upload() const;

        void Debug(const std::string &msg) const;

    private:
        int m_location{-1};

        Type m_type{Type::Undefined};

        union Data {
            bool m_dataBool;
            int m_dataInt;
            float m_dataFloat;
            glm::vec2 m_dataVec2;
            glm::vec3 m_dataVec3;
            glm::vec4 m_dataVec4;
            glm::mat4x4 m_dataMat4x4;
//            Sampler m_dataSampler;
        } m_data{};

        [[nodiscard]] std::string TypeName() const;

    };

}
#endif //INCLUDED_MN_GRAPHICS_UNIFORM_H
