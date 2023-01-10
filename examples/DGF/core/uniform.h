//
// Created by ivan on 27.9.2021..
//

#ifndef GLFRAMEWORK_UNIFORM_H
#define GLFRAMEWORK_UNIFORM_H

#include <glad/glad.h>
#include <string>
#include <vector>

class Uniform1 {
public:
    enum class Type {
        None, Int, Bool, Float, Vec2, Vec3, Vec4
    };

    Uniform();

    explicit Uniform(GLint data);

    explicit Uniform(GLboolean data);

    explicit Uniform(GLfloat data);

    Uniform(Type dataType, std::vector<GLfloat> data);

    void locateVariable(GLuint programRef, const std::string &variableName);

    void uploadData();

    std::vector<GLfloat>& Vector() { return _dataVec; }

private:
    Type _dataType{};

    GLint _dataInt{};
    GLboolean _dataBool{};
    GLfloat _dataFloat{};
    std::vector<GLfloat> _dataVec{};

    GLint _variableRef{};
};

#endif //GLFRAMEWORK_UNIFORM_H
