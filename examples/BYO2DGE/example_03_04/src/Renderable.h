#ifndef BYO2DGE_RENDERABLE_H
#define BYO2DGE_RENDERABLE_H

#include "graphics/Vao.h"
#include "graphics/ShaderInfo.h"
#include "Transform.h"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Renderable {
public:
    Renderable();

    Renderable(const Mn::Vao &vao, const Mn::ShaderInfo &shader);

    void draw(glm::mat4 cameraMatrix);

    void setColor(glm::vec4 color);

    [[nodiscard]] glm::vec4 getColor() const;

    [[nodiscard]] Transform &getXform();

private:
    Mn::Vao mVao{};
    Mn::ShaderInfo mShader{};
    glm::vec4 mColor{};
    Transform mXform{};
};

#endif //BYO2DGE_RENDERABLE_H
