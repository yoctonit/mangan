#ifndef DGF_GRAPHICS_CORE_UNIFORM_VEC3_H
#define DGF_GRAPHICS_CORE_UNIFORM_VEC3_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>


template<typename T>
class UniformVec3 {
public:
    UniformVec3();

    explicit UniformVec3(T data);

    void upload(GLint variableRef);

    T &data();

private:
    T m_data;
};

template<typename T>
UniformVec3<T>::UniformVec3() = default;

template<typename T>
UniformVec3<T>::UniformVec3(T data) {
    m_data = std::move(data);
}

template<typename T>
void UniformVec3<T>::upload(GLint variableRef) {
    // if the program does not reference the variable, then exit
    if (variableRef == -1) return;

    glUniform3f(variableRef, m_data[0], m_data[1], m_data[2]);
}

template<typename T>
T &UniformVec3<T>::data() {
    return m_data;
}

#endif //DGF_GRAPHICS_CORE_UNIFORM_VEC3_H
