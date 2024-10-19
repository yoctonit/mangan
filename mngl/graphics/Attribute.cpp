#include <glad/glad.h>
#include <iostream>
#include "Attribute.h"

namespace Mn {
    Attribute::Attribute() = default;

    Attribute::Attribute(int location, int type) {
        mLocation = location;
        mType = type;
    }

    int Attribute::Location() const {
        return mLocation;
    }

    void Attribute::Debug(const std::string &msg) const {
        std::cout << msg << ": location(" << mLocation << "), type(" << TypeName() << ")\n";
    }

    std::string Attribute::TypeName() const {
        std::string typeName;

        switch (mType) {
            case GL_BOOL:
                typeName = "bool";
                break;
            case GL_INT:
                typeName = "int";
                break;
            case GL_SAMPLER_2D:
                typeName = "sampler2D";
                break;
            case GL_FLOAT:
                typeName = "float";
                break;
            case GL_FLOAT_VEC2:
                typeName = "vec2";
                break;
            case GL_FLOAT_VEC3:
                typeName = "vec3";
                break;
            case GL_FLOAT_VEC4:
                typeName = "vec4";
                break;
            case GL_FLOAT_MAT4:
                typeName = "mat4x4";
                break;
            default:
                typeName = "undefined";
        }

        return typeName;
    }


}