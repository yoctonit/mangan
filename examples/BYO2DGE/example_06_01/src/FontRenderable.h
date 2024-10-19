#ifndef BYO2DGE_FONT_RENDERABLE_H
#define BYO2DGE_FONT_RENDERABLE_H

#include "core/Vao.h"
#include "core/Vbo.h"
#include "graphics/ShaderInfo.h"
#include "core/Texture.h"
#include "Camera.h"
#include "Transform.h"
#include "SpriteRenderable.h"
#include "Font.h"
#include <glm/vec4.hpp>

class FontRenderable {
public:
    FontRenderable();

    FontRenderable(
            const Font *font,
            SpriteRenderable &spriteRenderable,
            const std::string &text
    );

    void draw(const Camera &camera);

    void setColor(glm::vec4 color);

    [[nodiscard]] glm::vec4 getColor() const;

    [[nodiscard]] Transform &getXform();

    void setTextHeight(float h);

    void setText(const std::string &fontName);

    std::string getText() const;

private:
    const Font *mFont{};
    SpriteRenderable mOneChar{};
    Transform mXform{};
    std::string mText{};
};

#endif //BYO2DGE_FONT_RENDERABLE_H
