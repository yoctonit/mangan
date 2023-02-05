//
// Created by Ivan on 30-Jan-23.
//

#ifndef OPENGL_EXAMPLES_INDEX_H
#define OPENGL_EXAMPLES_INDEX_H

/*
 * serves as central export of the entire engine
 * client programs can simply import this file
 * for all symbols defined in the engine
 */
#include <memory>
// general utilities
#include "Renderable.h"
#include "Square.h"
#include "ShaderResources.h"

class Engine {
public:
    Engine() {
        mVertexBuffer = std::make_shared<Square>();
        mShaderResources = std::make_shared<ShaderResources>();
    }

    static void clearCanvas(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    [[nodiscard]] std::shared_ptr<ShaderResources> shaderResources() const { return mShaderResources; }

    [[nodiscard]] std::shared_ptr<Square> vertexBuffer() const { return mVertexBuffer; }

private:
    std::shared_ptr<Square> mVertexBuffer;
    std::shared_ptr<ShaderResources> mShaderResources;
};

#endif //OPENGL_EXAMPLES_INDEX_H
