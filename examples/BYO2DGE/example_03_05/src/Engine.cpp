#include "Engine.h"
#include "Square.h"


Engine::Engine() = default;

void Engine::Initialize() {
    mConstColorShader.Create();
    mSquareBuffer.Create(Square::SquareVertices());
    mConstColorSquareVao.Create();
    mConstColorSquareVao.Connect(SquareBuffer(), ConstColorShader().Shader(), "aVertexPosition", 3, 3, nullptr);
}

void Engine::Release() {
    mConstColorSquareVao.Release();
    mSquareBuffer.Release();
    mConstColorShader.Release();
}

[[nodiscard]] SimpleShader Engine::ConstColorShader() const {
    return mConstColorShader;
}

[[nodiscard]] Mn::Buffer Engine::SquareBuffer() const {
    return mSquareBuffer;
}

[[nodiscard]] Mn::Vao Engine::ConstColorSquareVao() const {
    return mConstColorSquareVao;
}

void Engine::BackgroundColor(glm::vec4 color) {
    mBackgroundColor = color;
}

void Engine::ClearCanvas() const {
    glClearColor(mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
