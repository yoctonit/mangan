#ifndef INCLUDED_AXES_H
#define INCLUDED_AXES_H

//#include "glad/glad.h"
#include "core/Vbo.h"
#include "core/Vao.h"
#include "graphics/ShaderLoader.h"

#include "Camera.h"


class Axes {
public:
    Axes();

    void Draw(const Camera &camera) const;

private:
    // for rendering
    Mn::ShaderLoader mShaderLoader;
    Mn::Vao mVao;
    Mn::Vbo mBuffer;
};

#endif //INCLUDED_AXES_H
