#include <iostream>
#include "Uniform.h"
#include <glm/gtc/type_ptr.hpp>

Uniform::Uniform() = default;

Uniform::Uniform(Type dataType) {
    m_dataType = dataType;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName) {
    m_variableRef = locate(programRef, variableName);
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, bool data) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Bool;
    m_data.m_dataBool = data;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, int data) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Int;
    m_data.m_dataInt = data;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, float data) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Float;
    m_data.m_dataFloat = data;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, glm::vec2 data) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Vec2;
    m_data.m_dataVec2 = data;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, glm::vec3 data) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Vec3;
    m_data.m_dataVec3 = data;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, glm::mat4x4 data) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Mat4x4;
    m_data.m_dataMat4x4 = data;
}

Uniform::Uniform(GLuint programRef, const std::string &variableName, unsigned int textureRef, int textureUnit) {
    m_variableRef = locate(programRef, variableName);
    m_dataType = Type::Sampler2D;
    m_data.m_dataVec2 = glm::vec2(
            static_cast<float>(textureRef),
            static_cast<float>(textureUnit)
    );
}

// get and store reference for program variable with given name
GLint Uniform::locate(GLuint programRef, const std::string &variableName) {
    m_variableRef = glGetUniformLocation(programRef, variableName.c_str());
    if (m_variableRef == -1) {
        std::cerr << "Uniform variable " << variableName << " not found.\n";
    }
    return m_variableRef;
}

void Uniform::upload() {
    // if the program does not reference the variable, then exit
    if (m_variableRef == -1) return;

    switch (m_dataType) {
        case Type::Bool:
            glUniform1i(m_variableRef, m_data.m_dataBool);
            break;
        case Type::Int:
            glUniform1i(m_variableRef, m_data.m_dataInt);
            break;
        case Type::Float:
            glUniform1f(m_variableRef, m_data.m_dataFloat);
            break;
        case Type::Vec2:
            glUniform2fv(m_variableRef, 1, glm::value_ptr(m_data.m_dataVec2));
            break;
        case Type::Vec3:
            glUniform3fv(m_variableRef, 1, glm::value_ptr(m_data.m_dataVec3));
            break;
        case Type::Vec4:
            glUniform4fv(m_variableRef, 1, glm::value_ptr(m_data.m_dataVec4));
            break;
        case Type::Mat4x4:
            glUniformMatrix4fv(m_variableRef, 1, GL_FALSE, glm::value_ptr(m_data.m_dataMat4x4));
            break;
        case Type::Sampler2D: {
            int textureObjectRef = static_cast<int>(m_data.m_dataVec2.x);
            int textureUnitRef = static_cast<int>(m_data.m_dataVec2.y);
            // activate texture unit
            glActiveTexture(GL_TEXTURE0 + textureUnitRef);
            // associate texture object reference to currently active texture unit
            glBindTexture(GL_TEXTURE_2D, textureObjectRef);
            // upload texture unit number (0...15) to uniform variable in shader
            glUniform1i(m_variableRef, textureUnitRef);
            break;
        }
        default:
            std::cerr << "Unknown uniform data type\n";
    }
}

Uniform::Data &Uniform::data() {
    return m_data;
}

/*
UniformVec3::UniformVec3() = default;

UniformVec3::UniformVec3(std::vector<float> data) {
    m_data = std::move(data);
}

UniformVec3::UniformVec3(GLuint programRef, const std::string &variableName, std::vector<float> data)
        : Uniform(programRef, variableName) {
    m_data = std::move(data);
}

void UniformVec3::upload() {
    // if the program does not reference the variable, then exit
    if (m_variableRef == -1) return;

    glUniform3f(m_variableRef, m_data[0], m_data[1], m_data[2]);
}

std::vector<float> &UniformVec3::data() {
    return m_data;
}

UniformMat4x4::UniformMat4x4() = default;

UniformMat4x4::UniformMat4x4(glm::mat4 data) {
    m_data = data;
}

UniformMat4x4::UniformMat4x4(GLuint programRef, const std::string &variableName, glm::mat4 data)
        : Uniform(programRef, variableName) {
    m_data = data;
}

void UniformMat4x4::upload() {
    // if the program does not reference the variable, then exit
    if (m_variableRef == -1) return;

    glUniformMatrix4fv(m_variableRef, 1, GL_FALSE, glm::value_ptr(m_data));
}

glm::mat4 &UniformMat4x4::data() {
    return m_data;
}
*/