//
// Created by ivan on 26.9.2021..
//
#include <stdexcept>
#include <utility>
#include "attribute.h"

Attribute::Attribute(Type dataType, std::vector<GLfloat> data) {
    // type of elements in data array:
    // int | float | vec2 | vec3 | vec4
    _dataType = dataType;

    // array of data to be stored in buffer
    _data = std::move(data);

    // reference of available buffer from GPU
    glGenBuffers(1, &_bufferRef);

    // upload data immediately
    uploadData();
}

void Attribute::uploadData() {
    // select buffer used by the following functions
    glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

    // store data in currently bound buffer
    auto dataSizeInBytes = static_cast<GLsizeiptr>(_data.size() * sizeof(GLfloat));
    glBufferData(GL_ARRAY_BUFFER, dataSizeInBytes, _data.data(), GL_STATIC_DRAW);

    // deactivate buffer
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// associate variable in program with this buffer
void Attribute::associateVariable(GLuint programRef, const std::string &variableName) {
    // get reference for program variable with given name
    GLint variableRef = glGetAttribLocation(programRef, variableName.c_str());

    // if the program does not reference the variable, then exit
    if (variableRef == -1) return;

    // select buffer used by the following functions
    glBindBuffer(GL_ARRAY_BUFFER, _bufferRef);

    // specify how data will be read from the currently bound buffer
    // into the specified variable
    switch (_dataType) {
//        case Type::Int:
//            glVertexAttribPointer(variableRef, 1, GL_INT, GL_FALSE, 0, nullptr);
//            break;
        case Type::Float:
            glVertexAttribPointer(variableRef, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case Type::Vec2:
            glVertexAttribPointer(variableRef, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case Type::Vec3:
            glVertexAttribPointer(variableRef, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case Type::Vec4:
            glVertexAttribPointer(variableRef, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        default:
            throw std::runtime_error("Attribute " + variableName + " has unknown type\n");
    }

    // indicate that data will be streamed to this variable
    glEnableVertexAttribArray(variableRef);
}
