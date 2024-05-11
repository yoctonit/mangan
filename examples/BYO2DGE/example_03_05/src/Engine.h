#ifndef BYO2DGE_ENGINE_H
#define BYO2DGE_ENGINE_H

#include "core/Buffer.h"
#include "core/Vao.h"
#include "SimpleShader.h"


/*
 * Serves as central export of the entire engine.
 * Client programs can simply import this file
 * for all symbols defined in the engine
 */
class Engine {
public:
    Engine();

    void Initialize();

    void Release();

    [[nodiscard]] SimpleShader ConstColorShader() const;

    [[nodiscard]] Mn::Buffer SquareBuffer() const;

    [[nodiscard]] Mn::Vao ConstColorSquareVao() const;

    void BackgroundColor(glm::vec4 c);

    void ClearCanvas() const;

private:
    SimpleShader mConstColorShader{};
    Mn::Buffer mSquareBuffer{};
    Mn::Vao mConstColorSquareVao{};

    glm::vec4 mBackgroundColor{};
};

#endif //BYO2DGE_ENGINE_H
