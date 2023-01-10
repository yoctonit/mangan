//
// Created by ivan on 26.9.2021..
//

#ifndef INCLUDED_MN_ATTRIBUTE_H
#define INCLUDED_MN_ATTRIBUTE_H

#include <glad/glad.h>
#include <string>
#include <vector>

namespace Mn {

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

}

#endif //INCLUDED_MN_ATTRIBUTE_H
