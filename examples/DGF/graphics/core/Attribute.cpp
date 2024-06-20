#include <utility>
#include <iostream>
#include "Attribute.h"

Attribute::Attribute() = default;

Attribute::Attribute(Type dataType, std::vector<GLfloat> data) {
    m_dataType = dataType;

    // array of data to be stored in buffer
    m_data = std::move(data);

    // returns a single buffer reference
    glGenBuffers(1, &m_bufferRef);

    // upload data immediately
    uploadData();
}

void Attribute::uploadData() {
    // select buffer used by the following functions
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferRef);

    // store data in currently bound buffer
    auto dataSizeBytes = static_cast<GLsizeiptr>(m_data.size() * sizeof(GLfloat));
    glBufferData(GL_ARRAY_BUFFER, dataSizeBytes, m_data.data(), GL_STATIC_DRAW);
}

std::vector<GLfloat> &Attribute::getData() {
    return m_data;
}

// associate variable in program with this buffer
void Attribute::associateVariable(GLuint programRef, const std::string &variableName) const {
    // get reference for program variable with given name
    GLint variableRef = glGetAttribLocation(programRef, variableName.c_str());

    // if the program does not reference the variable, then exit
    if (variableRef == -1) {
        std::cerr << "Variable " << variableName << " does not exist in shader " << programRef << "\n.";
        return;
    }

    // select buffer used by the following functions
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferRef);

    // specify how data will be read from the currently bound buffer into the specified variable
    switch (m_dataType) {
        case Type::Int:
            glVertexAttribPointer(variableRef, 1, GL_INT, GL_FALSE, 0, nullptr);
            break;
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
            std::cerr << "Attribute " << variableName << " has unknown type\n";
            return;
    }

    // indicate that data will be streamed to this variable from a buffer
    glEnableVertexAttribArray(variableRef);
}
