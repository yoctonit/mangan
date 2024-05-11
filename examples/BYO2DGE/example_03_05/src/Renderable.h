#ifndef BYO2DGE_RENDERABLE_H
#define BYO2DGE_RENDERABLE_H

/*
 * Encapsulate the Shader and vertexBuffer into the same object
 * (and will include other attributes later)
 * to represent a Renderable object on the game screen.
 */
#include "core/Vao.h"
#include "SimpleShader.h"
#include "Transform.h"
#include "Camera.h"
#include <glm/glm.hpp>

class Renderable {
public:
    Renderable();

    Renderable(Mn::Vao vao, SimpleShader shader);

    void Create(Mn::Vao vao, SimpleShader shader);

    void Draw(const Camera &camera) const;

    void Color(glm::vec4 color);

    [[nodiscard]] glm::vec4 Color() const;

    Transform &Xform();

private:
    Mn::Vao mVao{};
    SimpleShader mSimpleShader{};
    glm::vec4 mColor{};
    Transform mXform;
};

#endif //BYO2DGE_RENDERABLE_H
