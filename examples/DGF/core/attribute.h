//
// Created by ivan on 26.9.2021..
//

#ifndef GLFRAMEWORK_ATTRIBUTE_H
#define GLFRAMEWORK_ATTRIBUTE_H

#include <glad/glad.h>
#include <string>
#include <vector>

class Attribute {
public:
    enum class Type {
        /* Int,*/ Float, Vec2, Vec3, Vec4
    };
    Attribute() = default;
    Attribute(Type dataType, std::vector<GLfloat> data);

    void uploadData();

    void associateVariable(GLuint programRef, const std::string &variableName);

private:
    Type _dataType{};
    GLuint _bufferRef{};
    std::vector<GLfloat> _data;
};

#endif //GLFRAMEWORK_ATTRIBUTE_H
