#ifndef INCLUDED_PLANET_H
#define INCLUDED_PLANET_H

#include "core/Vbo.h"
#include "core/Vao.h"
#include "graphics/ShaderLoader.h"

#include "Camera.h"
#include "point_light.h"

class Planet {
public:
    explicit Planet(float radius = 1.0f);

    void Draw(const Camera &camera, const point_light &light) const;

private:
    // for rendering
    Mn::ShaderLoader mShaderLoader;
    Mn::Vao mVao;
    Mn::Vbo mBuffer;
    int mVertexCount{};
};

#endif //INCLUDED_PLANET_H
