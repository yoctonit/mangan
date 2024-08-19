#include <iostream>
#include "Uniform.h"
#include <glm/gtc/type_ptr.hpp>

namespace Mn {

    Uniform::Uniform() = default;

//    Uniform::Uniform(int location, Type type) {
//        m_location = location;
//        m_type = type;
//    }

//Uniform::Uniform(GLuint programRef, const std::string &variableName) {
//    m_location = locate(programRef, variableName);
//}
//

    void Uniform::Create(int location, Type type) {
        m_location = location;
        m_type = type;
    }

    Uniform &Uniform::operator=(bool data) {
        if (m_type != Type::Bool) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got bool\n";
            return *this;
        }

        m_data.m_dataBool = data;
        return *this;
    }

    Uniform &Uniform::operator=(int data) {
        if (m_type != Type::Int) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got int\n";
            return *this;
        }

        m_data.m_dataInt = data;
        return *this;
    }

    Uniform &Uniform::operator=(float data) {
        if (m_type != Type::Float) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got float\n";
            return *this;
        }

        m_data.m_dataFloat = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::vec2 data) {
        if (m_type != Type::Vec2) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got vec2\n";
            return *this;
        }

        m_data.m_dataVec2 = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::vec3 data) {
        if (m_type != Type::Vec3) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got vec3\n";
            return *this;
        }

        m_data.m_dataVec3 = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::vec4 data) {
        if (m_type != Type::Vec4) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got vec4\n";
            return *this;
        }

        m_data.m_dataVec4 = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::mat4x4 data) {
        if (m_type != Type::Mat4x4) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got mat4x4\n";
            return *this;
        }

        m_data.m_dataMat4x4 = data;
        return *this;
    }

    void Uniform::Upload() const {
        if (m_location == -1) {
            std::cerr << "Uniform variable could not be uploaded: invalid location\n";
            return;
        }

        switch (m_type) {
            case Type::Bool:
                glUniform1i(m_location, (int) m_data.m_dataBool);
                break;
            case Type::Int:
                glUniform1i(m_location, m_data.m_dataInt);
                break;
            case Type::Float:
                glUniform1f(m_location, m_data.m_dataFloat);
                break;
            case Type::Vec2:
                glUniform2fv(m_location, 1, glm::value_ptr(m_data.m_dataVec2));
                break;
            case Type::Vec3:
                glUniform3fv(m_location, 1, glm::value_ptr(m_data.m_dataVec3));
                break;
            case Type::Vec4:
                glUniform4fv(m_location, 1, glm::value_ptr(m_data.m_dataVec4));
                break;
            case Type::Mat4x4:
                glUniformMatrix4fv(m_location, 1, GL_FALSE, glm::value_ptr(m_data.m_dataMat4x4));
                break;
            default:
                std::cerr << "Uniform variable could not be uploaded: unknown type\n";
        }
    }

    void Uniform::Debug(const std::string &msg) const {
        std::string typeName = TypeName();

        std::cout << msg << ":\n"
                  << "\tlocation: " << m_location << "\n"
                  << "\ttype:     " << typeName << "\n"
                  << "\tvalue:    ";

        switch (m_type) {
            case Type::Bool:
                std::cout << (m_data.m_dataBool ? "true" : "false") << "\n";
                break;
            case Type::Int:
                std::cout << m_data.m_dataInt << "\n";
                break;
            case Type::Float:
                std::cout << m_data.m_dataFloat << "\n";
                break;
            case Type::Vec2:
                std::cout << "("
                          << m_data.m_dataVec2.x << ", "
                          << m_data.m_dataVec2.y << ")\n";
                break;
            case Type::Vec3:
                std::cout << "("
                          << m_data.m_dataVec3.x << ", "
                          << m_data.m_dataVec3.y << ", "
                          << m_data.m_dataVec3.z << ")\n";
                break;
            case Type::Vec4:
                std::cout << "("
                          << m_data.m_dataVec4.x << ", "
                          << m_data.m_dataVec4.y << ", "
                          << m_data.m_dataVec4.z << ", "
                          << m_data.m_dataVec4.w << ")\n";
                break;
            case Type::Mat4x4:
                std::cout << m_data.m_dataMat4x4[0][0] << ", "
                          << m_data.m_dataMat4x4[0][1] << ", "
                          << m_data.m_dataMat4x4[0][2] << ", "
                          << m_data.m_dataMat4x4[0][3] << "\n"

                          << m_data.m_dataMat4x4[1][0] << ", "
                          << m_data.m_dataMat4x4[1][1] << ", "
                          << m_data.m_dataMat4x4[1][2] << ", "
                          << m_data.m_dataMat4x4[1][3] << "\n"

                          << m_data.m_dataMat4x4[2][0] << ", "
                          << m_data.m_dataMat4x4[2][1] << ", "
                          << m_data.m_dataMat4x4[2][2] << ", "
                          << m_data.m_dataMat4x4[2][3] << "\n"

                          << m_data.m_dataMat4x4[3][0] << ", "
                          << m_data.m_dataMat4x4[3][1] << ", "
                          << m_data.m_dataMat4x4[3][2] << ", "
                          << m_data.m_dataMat4x4[3][3] << "\n";
                break;
            default:
                std::cout << "undefined\n";
        }

    }

    std::string Uniform::TypeName() const {
        std::string typeName;

        switch (m_type) {
            case Type::Bool:
                typeName = "bool";
                break;
            case Type::Int:
                typeName = "int";
                break;
            case Type::Float:
                typeName = "float";
                break;
            case Type::Vec2:
                typeName = "vec2";
                break;
            case Type::Vec3:
                typeName = "vec3";
                break;
            case Type::Vec4:
                typeName = "vec4";
                break;
            case Type::Mat4x4:
                typeName = "mat4x4";
                break;
            default:
                typeName = "undefined";
        }

        return typeName;
    }
}
