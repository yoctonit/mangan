//
// Created by Ivan on 30-Jan-23.
//

#ifndef OPENGL_EXAMPLES_SHADER_RESOURCES_H
#define OPENGL_EXAMPLES_SHADER_RESOURCES_H

#include <memory>
#include "SimpleShader.h"

class ShaderResources {
public:
    ShaderResources() {
        mConstColorShader = std::make_shared<SimpleShader>("shader/simple.vs", "shader/simple.fs");
    }

    [[nodiscard]] std::shared_ptr<SimpleShader> getConstColorShader() const { return mConstColorShader; }

private:
    std::shared_ptr<SimpleShader> mConstColorShader{};
};

#endif //OPENGL_EXAMPLES_SHADER_RESOURCES_H
