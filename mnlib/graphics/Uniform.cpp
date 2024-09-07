#include <glad/glad.h>
#include <iostream>
#include "Uniform.h"
#include <glm/gtc/type_ptr.hpp>

namespace Mn {

    Uniform::Uniform() = default;

    Uniform::Uniform(int location, int type) {
        mLocation = location;
        mType = type;
    }

    Uniform &Uniform::operator=(bool data) {
        if (mType != GL_BOOL) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got bool\n";
            return *this;
        }

        mData.mDataBool = data;
        return *this;
    }

    Uniform &Uniform::operator=(int data) {
        if ((mType != GL_INT) && (mType != GL_SAMPLER_2D)) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got int\n";
            return *this;
        }

        mData.mDataInt = data;
        return *this;
    }

    Uniform &Uniform::operator=(float data) {
        if (mType != GL_FLOAT) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got float\n";
            return *this;
        }

        mData.mDataFloat = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::vec2 data) {
        if (mType != GL_FLOAT_VEC2) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got vec2\n";
            return *this;
        }

        mData.mDataVec2 = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::vec3 data) {
        if (mType != GL_FLOAT_VEC3) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got vec3\n";
            return *this;
        }

        mData.mDataVec3 = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::vec4 data) {
        if (mType != GL_FLOAT_VEC4) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got vec4\n";
            return *this;
        }

        mData.mDataVec4 = data;
        return *this;
    }

    Uniform &Uniform::operator=(glm::mat4x4 data) {
        if (mType != GL_FLOAT_MAT4) {
            std::cerr << "Uniform assignment invalid type: expected " << TypeName() << ", got mat4x4\n";
            return *this;
        }

        mData.mDataMat4x4 = data;
        return *this;
    }

    void Uniform::Upload() const {
        if (mLocation == -1) {
            std::cerr << "Uniform variable could not be uploaded: invalid location\n";
            return;
        }

        switch (mType) {
            case GL_BOOL:
                glUniform1i(mLocation, (int) mData.mDataBool);
                break;
            case GL_INT:
            case GL_SAMPLER_2D:
                glUniform1i(mLocation, mData.mDataInt);
                break;
            case GL_FLOAT:
                glUniform1f(mLocation, mData.mDataFloat);
                break;
            case GL_FLOAT_VEC2:
                glUniform2fv(mLocation, 1, glm::value_ptr(mData.mDataVec2));
                break;
            case GL_FLOAT_VEC3:
                glUniform3fv(mLocation, 1, glm::value_ptr(mData.mDataVec3));
                break;
            case GL_FLOAT_VEC4:
                glUniform4fv(mLocation, 1, glm::value_ptr(mData.mDataVec4));
                break;
            case GL_FLOAT_MAT4:
                glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(mData.mDataMat4x4));
                break;
            default:
                std::cerr << "Uniform variable could not be uploaded: unknown type\n";
        }
    }

    void Uniform::Debug(const std::string &msg) const {
        std::string typeName = TypeName();

        std::cout << msg << ":\n"
                  << "\tlocation: " << mLocation << "\n"
                  << "\ttype:     " << typeName << "\n"
                  << "\tvalue:    ";

        switch (mType) {
            case GL_BOOL:
                std::cout << (mData.mDataBool ? "true" : "false") << "\n";
                break;
            case GL_INT:
            case GL_SAMPLER_2D:
                std::cout << mData.mDataInt << "\n";
                break;
            case GL_FLOAT:
                std::cout << mData.mDataFloat << "\n";
                break;
            case GL_FLOAT_VEC2:
                std::cout << "("
                          << mData.mDataVec2.x << ", "
                          << mData.mDataVec2.y << ")\n";
                break;
            case GL_FLOAT_VEC3:
                std::cout << "("
                          << mData.mDataVec3.x << ", "
                          << mData.mDataVec3.y << ", "
                          << mData.mDataVec3.z << ")\n";
                break;
            case GL_FLOAT_VEC4:
                std::cout << "("
                          << mData.mDataVec4.x << ", "
                          << mData.mDataVec4.y << ", "
                          << mData.mDataVec4.z << ", "
                          << mData.mDataVec4.w << ")\n";
                break;
            case GL_FLOAT_MAT4:
                std::cout << mData.mDataMat4x4[0][0] << ", "
                          << mData.mDataMat4x4[0][1] << ", "
                          << mData.mDataMat4x4[0][2] << ", "
                          << mData.mDataMat4x4[0][3] << "\n"

                          << mData.mDataMat4x4[1][0] << ", "
                          << mData.mDataMat4x4[1][1] << ", "
                          << mData.mDataMat4x4[1][2] << ", "
                          << mData.mDataMat4x4[1][3] << "\n"

                          << mData.mDataMat4x4[2][0] << ", "
                          << mData.mDataMat4x4[2][1] << ", "
                          << mData.mDataMat4x4[2][2] << ", "
                          << mData.mDataMat4x4[2][3] << "\n"

                          << mData.mDataMat4x4[3][0] << ", "
                          << mData.mDataMat4x4[3][1] << ", "
                          << mData.mDataMat4x4[3][2] << ", "
                          << mData.mDataMat4x4[3][3] << "\n";
                break;
            default:
                std::cout << "undefined\n";
        }

    }

    std::string Uniform::TypeName() const {
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
