#ifndef OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H
#define OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H

#include "Renderable.h"
#include "Texture.h"

class TextureRenderable : public Renderable {
public:
    TextureRenderable(
            const std::shared_ptr<ShaderInterface> &ss,
            const std::shared_ptr<SquareGeometryBuffer> &sq,
            const std::shared_ptr<Mn::Texture> &tex)
            : Renderable(ss, sq) {
        mTexture = tex;
    }

    void draw(const Camera &camera) override {
        mTexture->activate();
        mShader->activate(
                mSquareGeometryBuffer,
                mColor,
                mXform->getTRSMatrix(),
                camera.getCameraMatrix());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    std::shared_ptr<Mn::Texture> getTexture() { return mTexture; }
    void setTexture(const std::shared_ptr<Mn::Texture>& newTexture) { mTexture = newTexture; }
protected:
    std::shared_ptr<Mn::Texture> mTexture{};
};

#endif //OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H
