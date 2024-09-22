#ifndef BYO2DGE_RENDERABLE_H
#define BYO2DGE_RENDERABLE_H

#include "graphics/Vao.h"
#include "graphics/ShaderInfo.h"
#include <glm/vec4.hpp>

class Renderable {
public:
    Renderable();

    Renderable(const Mn::Vao &vao, const Mn::ShaderInfo &shader);

    void draw();

    void setColor(glm::vec4 color);

    [[nodiscard]] glm::vec4 getColor() const;

private:
    Mn::Vao mVao{};
    Mn::ShaderInfo mShader{};
    glm::vec4 mColor{};
};

#endif //BYO2DGE_RENDERABLE_H
