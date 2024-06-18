#ifndef DGF_GRAPHICS_CORE_UNIFORM_H
#define DGF_GRAPHICS_CORE_UNIFORM_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>
//#include "UniformVec3.h"
#include <glm/mat4x4.hpp>


class Uniform {
public:
    Uniform();

    Uniform(GLuint programRef, const std::string &variableName);

    static GLint locate(GLuint programRef, const std::string &variableName);

    virtual void upload() = 0;

protected:
    GLint m_variableRef{-1};
};

class UniformVec3 : public Uniform {
public:
    UniformVec3();

    explicit UniformVec3(std::vector<float> data);

    UniformVec3(GLuint programRef, const std::string &variableName, std::vector<float> data);

    void upload() override;

    std::vector<float> &data();

private:
    std::vector<float> m_data;
};

class UniformMat4x4 : public Uniform {
public:
    UniformMat4x4();

    explicit UniformMat4x4(glm::mat4 data);

    UniformMat4x4(GLuint programRef, const std::string &variableName, glm::mat4 data);

    void upload() override;

    glm::mat4 &data();

private:
    glm::mat4 m_data{};
};

/*
template<typename T>
class Uniform {
public:
    enum class Type {
        None, Int, Bool, Float, Vec2, Vec3, Vec4
    };

    Uniform();

    Uniform(Type dataType, T data);

    void locateVariable(GLuint programRef, const std::string &variableName);

    void uploadData();

private:
    Type m_dataType{Type::None};

    T m_data;

    GLint m_variableRef{-1};
};

template<typename T>
Uniform<T>::Uniform() = default;

template<typename T>
Uniform<T>::Uniform(Type dataType, T data) {
    m_dataType = dataType;
    m_data = std::move(data);
}

// get and store reference for program variable with given name
template<typename T>
void Uniform<T>::locateVariable(GLuint programRef, const std::string &variableName) {
    m_variableRef = glGetUniformLocation(programRef, variableName.c_str());
}

// store data in uniform variable previously located
template<typename T>
void Uniform<T>::uploadData() {
    // if the program does not reference the variable, then exit
    if (m_variableRef == -1) return;

    switch (m_dataType) {
//        case Type::Int:
//        case Type::Bool:
//            glUniform1i(m_variableRef, m_data);
//            break;
//        case Type::Float:
//            glUniform1f(m_variableRef, m_data);
//            break;
        case Type::Vec2:
            glUniform2f(m_variableRef, m_data[0], m_data[1]);
            break;
        case Type::Vec3:
            glUniform3f(m_variableRef, m_data[0], m_data[1], m_data[2]);
            break;
        case Type::Vec4:
            glUniform4f(m_variableRef, m_data[0], m_data[1], m_data[2], m_data[3]);
            break;
        default:
            std::cerr << "Unknown uniform data type\n";
    }
}
*/
#endif //DGF_GRAPHICS_CORE_UNIFORM_H
