//
// Created by ivan on 27.9.2021..
//
#include <stdexcept>
#include "uniform.h"

// Page 53, use templates?
namespace Mn {

    Uniform::Uniform() {
        _dataType = Type::None;
    }

    Uniform::Uniform(GLint data) {
        _dataType = Type::Int;
        _dataInt = data;
    }

    Uniform::Uniform(GLboolean data) {
        _dataType = Type::Bool;
        _dataBool = data;
    }

    Uniform::Uniform(GLfloat data) {
        _dataType = Type::Float;
        _dataFloat = data;
    }

    Uniform::Uniform(Type dataType, std::vector<GLfloat> data) {
        // type of elements in data array:
        // vec2 | vec3 | vec4
        _dataType = dataType;

        // array of data to be stored in buffer
        _dataVec = std::move(data);
    }

// get and store reference for program variable with given name
    void Uniform::locateVariable(GLuint programRef, const std::string &variableName) {
        // get reference for program variable with given name
        _variableRef = glGetUniformLocation(programRef, variableName.c_str());
    }

// store data in uniform variable previously located
    void Uniform::uploadData() const {
        // if the program does not reference the variable, then exit
        if (_variableRef == -1) return;

        switch (_dataType) {
            case Type::Int:
                glUniform1i(_variableRef, _dataInt);
                break;
            case Type::Bool:
                glUniform1i(_variableRef, _dataBool);
                break;
            case Type::Float:
                glUniform1f(_variableRef, _dataFloat);
                break;
            case Type::Vec2:
                glUniform2f(_variableRef, _dataVec[0], _dataVec[1]);
                break;
            case Type::Vec3:
                glUniform3f(_variableRef, _dataVec[0], _dataVec[1], _dataVec[2]);
                break;
            case Type::Vec4:
                glUniform4f(_variableRef, _dataVec[0], _dataVec[1], _dataVec[2], _dataVec[3]);
                break;
            case Type::None:
                throw std::runtime_error("Uniform with type None\n");
        }
    }
}
