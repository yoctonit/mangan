#ifndef BYO2DGE_EXAMPLES_02_06_H
#define BYO2DGE_EXAMPLES_02_06_H

#include "graphics/ShaderInfo.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"


class Core {
public:
    void init();

    static void clearCanvas(float r, float g, float b, float a = 1.0f) ;

    void drawSquare(float r, float g, float b, float a = 1.0f);

private:
    Mn::ShaderInfo mSimpleShader{};
    Mn::Vbo mVertexBuffer{};
    Mn::Vao mVao{};
};

#endif //BYO2DGE_EXAMPLES_02_06_H
