#ifndef OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H
#define OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H

//#include <memory>
//#include <glm/glm.hpp>
//#include "SquareGeometryBuffer.h"
//#include "ShaderInterface.h"
//#include "Transform.h"
//#include "Camera.h"
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

//    getTexture() { return this.mTexture; }
//    setTexture(newTexture) { this.mTexture = newTexture; }
private:
    std::shared_ptr<Mn::Texture> mTexture{};
};

#endif //OPENGL_EXAMPLES_TEXTURE_RENDERABLE_H
