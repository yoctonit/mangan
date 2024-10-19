#ifndef BYO2DGE_SPRITE_RENDERABLE_H
#define BYO2DGE_SPRITE_RENDERABLE_H

#include "core/Vao.h"
#include "core/Vbo.h"
#include "graphics/ShaderInfo.h"
#include "core/Texture.h"
#include "Camera.h"
#include "Transform.h"
#include <glm/vec4.hpp>

class SpriteRenderable {
public:
    SpriteRenderable();

    SpriteRenderable(
            const Mn::Vao &vao,
            const Mn::ShaderInfo &shader,
            const Mn::Texture& texture,
            const Mn::Vbo &vbo);

    void draw(const Camera &camera);

    void setColor(glm::vec4 color);

    [[nodiscard]] glm::vec4 getColor() const;

    [[nodiscard]] Transform &getXform();

    void setTexture(const Mn::Texture& texture);

    [[nodiscard]] Mn::Texture getTexture() const;

    void setElementUVCoordinate(float left, float right, float bottom, float top);

    void setElementPixelPositions(float left, float right, float bottom, float top);

    std::vector<float> getElementUVCoordinateArray() const;

private:
    Mn::Vao mVao{};
    Mn::Vbo mVbo{};
    Mn::ShaderInfo mShader{};
    Mn::Texture mTexture{};
    glm::vec4 mColor{};
    Transform mXform{};

    float mElmLeft{0.0f};   // bounds of texture coordinate (0 is left, 1 is right)
    float mElmRight{1.0f};
    float mElmTop{1.0f};    //   1 is top and 0 is bottom of image
    float mElmBottom{0.0f};
};

#endif //BYO2DGE_SPRITE_RENDERABLE_H
