#ifndef BYO2DGE_CORE_H
#define BYO2DGE_CORE_H

#include "graphics/ShaderInfo.h"
#include "core/Vbo.h"
#include "core/Vao.h"
#include "Renderable.h"


class Core {
public:
    void init();

    static void clearCanvas(float r, float g, float b, float a = 1.0f);

    // Mn::ShaderInfo &getConstColorShader();

    Renderable createRenderable() const;

private:
    Mn::ShaderInfo mConstColorShader{};
    Mn::Vbo mVertexBuffer{};
    Mn::Vao mVao{};
};

#endif //BYO2DGE_CORE_H
