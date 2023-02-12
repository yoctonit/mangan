#ifndef OPENGL_EXAMPLES_ENGINE_H
#define OPENGL_EXAMPLES_ENGINE_H

#include <memory>
#include "SquareGeometryBuffer.h"
#include "SimpleShader.h"
#include "TextureShader.h"

class Engine {
public:
    Engine() {
        mSquareGeometryBuffer = std::make_shared<SquareGeometryBuffer>();

        mConstColorShader = std::make_shared<SimpleShader>(
                "shader/simple.vs",
                "shader/simple.fs");
        mTextureShader = std::make_shared<TextureShader>(
                "shader/texture.vs",
                "shader/texture.fs");
    }

    static void clearCanvas(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        // Allows transparency with textures.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    [[nodiscard]] std::shared_ptr<SquareGeometryBuffer> getSquareGeometryBuffer() const { return mSquareGeometryBuffer; }

    [[nodiscard]] std::shared_ptr<SimpleShader> getConstColorShader() const { return mConstColorShader; }

    [[nodiscard]] std::shared_ptr<TextureShader> getTextureShader() const { return mTextureShader; }

private:
    std::shared_ptr<SquareGeometryBuffer> mSquareGeometryBuffer;
    std::shared_ptr<SimpleShader> mConstColorShader{};
    std::shared_ptr<TextureShader> mTextureShader{};
};

#endif //OPENGL_EXAMPLES_ENGINE_H
