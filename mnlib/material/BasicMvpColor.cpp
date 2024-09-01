#include "BasicMvpColor.h"

namespace Mn {

//    BasicMvpColor::BasicMvpColor() {
//
//        mShader = Shader::FromFiles(
//                "shader/basic_.vs",
//                "shader/basic_color.fs"
//        );
//
//        AddUniform("uModel", Uniform::Type::Mat4x4);
//        AddUniform("uView", Uniform::Type::Mat4x4);
//        AddUniform("uProjection", Uniform::Type::Mat4x4);
//        AddUniform("uColor", Uniform::Type::Vec3);
//    }

    void BasicMvpColor::Create() {
        mShader = Shader::FromFiles(
                "shader/basic_mvp.vs",
                "shader/basic_color.fs"
        );

        AddUniform("uModel", Uniform::Type::Mat4x4);
        AddUniform("uView", Uniform::Type::Mat4x4);
        AddUniform("uProjection", Uniform::Type::Mat4x4);
        AddUniform("uColor", Uniform::Type::Vec3);
    }

}