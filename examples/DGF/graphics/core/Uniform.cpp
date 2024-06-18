#include <iostream>
#include "Uniform.h"
#include <glm/gtc/type_ptr.hpp>

Uniform::Uniform() = default;

Uniform::Uniform(GLuint programRef, const std::string &variableName) {
    m_variableRef = locate(programRef, variableName);
}

// get and store reference for program variable with given name
GLint Uniform::locate(GLuint programRef, const std::string &variableName) {
    GLint variableRef = glGetUniformLocation(programRef, variableName.c_str());
    if (variableRef == -1) {
        std::cerr << "Uniform variable " << variableName << " not found.\n";
    }
    return variableRef;
}

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
