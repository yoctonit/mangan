#ifndef DGF_GRAPHICS_CORE_RENDER_TARGET_H
#define DGF_GRAPHICS_CORE_RENDER_TARGET_H

#include <memory>
#include "Texture.h"

class RenderTarget {
public:
    RenderTarget(int w, int h);

    int width{};
    int height{};
    GLuint framebufferRef{};
    std::shared_ptr<Texture> texture{};
};

#endif //DGF_GRAPHICS_CORE_RENDER_TARGET_H
