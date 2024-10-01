#ifndef BYO2DGE_TEXTURE_RENDERABLE_H
#define BYO2DGE_TEXTURE_RENDERABLE_H

#include "graphics/Vao.h"
#include "graphics/ShaderInfo.h"
#include "graphics/Texture.h"
#include "Camera.h"
#include "Transform.h"
#include <glm/vec4.hpp>

class TextureRenderable {
public:
    TextureRenderable();

    TextureRenderable(const Mn::Vao &vao, const Mn::ShaderInfo &shader, const Mn::Texture& texture);

    void draw(const Camera &camera);

    void setColor(glm::vec4 color);

    [[nodiscard]] glm::vec4 getColor() const;

    [[nodiscard]] Transform &getXform();

    void setTexture(const Mn::Texture& texture);

    [[nodiscard]] Mn::Texture getTexture() const;

private:
    Mn::Vao mVao{};
    Mn::ShaderInfo mShader{};
    Mn::Texture mTexture{};
    glm::vec4 mColor{};
    Transform mXform{};
};

#endif //BYO2DGE_TEXTURE_RENDERABLE_H
