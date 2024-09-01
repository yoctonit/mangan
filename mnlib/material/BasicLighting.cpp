#include "BasicLighting.h"

namespace Mn {

    void BasicLighting::Create() {
        mShader = Shader::FromFiles(
                "shader/basic_lighting.vs",
                "shader/basic_lighting.fs"
        );

        AddUniform("uModel", Uniform::Type::Mat4x4);
        AddUniform("uView", Uniform::Type::Mat4x4);
        AddUniform("uProjection", Uniform::Type::Mat4x4);

        AddUniform("uViewPosition", Uniform::Type::Vec3);
        AddUniform("uMaterial.ambient", Uniform::Type::Vec3);
        AddUniform("uMaterial.diffuse", Uniform::Type::Vec3);
        AddUniform("uMaterial.specular", Uniform::Type::Vec3);
        AddUniform("uMaterial.shininess", Uniform::Type::Float);

        AddUniform("uLight.position", Uniform::Type::Vec3);
        AddUniform("uLight.ambient", Uniform::Type::Vec3);
        AddUniform("uLight.diffuse", Uniform::Type::Vec3);
        AddUniform("uLight.specular", Uniform::Type::Vec3);

    }

}
