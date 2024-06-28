#ifndef DGF_GRAPHICS_CORE_TEXTURE_H
#define DGF_GRAPHICS_CORE_TEXTURE_H

#include <string>
#include "glad/glad.h"


class Texture {
public:
    explicit Texture(const std::string &fileName);

    Texture(int width, int height);

    // ~Texture();

    // void activate(int texture_unit = 0) const;

    // static void deactivate();

    [[nodiscard]] GLuint textureRef() const;

    [[nodiscard]] int width() const;

    [[nodiscard]] int height() const;

private:
    GLuint m_textureRef{};

    GLint m_magFilter{};
    GLint m_minFilter{};
    GLint m_wrap{};

    int m_width{};
    int m_height{};
};

#endif //DGF_GRAPHICS_CORE_TEXTURE_H
